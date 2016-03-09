#include "EvolutionDriver.h"

#include "MipmapCollection.h"
#include "State.h"
#include "EvolutionStatistics.h"
#include "AdaptiveScalingController.h"

EvolutionDriver::EvolutionDriver():
    m_stats(new EvolutionStatistics())
{ 
    m_evolver = std::make_unique<ImageEvolver>();
    change_active_mipmap_level(m_initial_mipmap_level);    
}
 
void EvolutionDriver::set_target_image(std::unique_ptr<Image> target_image)
{
    m_mipmap = std::make_unique<MipmapCollection>(std::move(target_image));
    m_evolver->set_target_image(m_mipmap->get_image_level(m_cur_mipmap_level).clone()); 

    const auto& full_img = m_mipmap->full_image();

    m_full_bg_image = std::make_unique<Image>(full_img.width(), 
            full_img.height(), m_evolver->bg_color());
}
 
EvolutionDriver::~EvolutionDriver()
{
     
}
 
std::unique_ptr<Image> EvolutionDriver::render_state(const State& state)
{
    auto image_copy = m_full_bg_image->clone();
    m_evolver->apply_state(state, *image_copy);
    return image_copy;
}
 
void EvolutionDriver::advance_generation()
{
    m_evolver->advance_generation(); 

    /*double score_delta = m_stats->compute_score_delta();
    double rel_score_delta = score_delta / m_evolver->best_score();

    if(m_evolver->generation_number() % 10 == 0 && m_stats->is_backlog_full()) {
        std::cout << m_evolver->generation_number() << "\t" <<
            score_delta << "\t" <<
            rel_score_delta << std::endl;


        double threshold = m_change_threshold_base 
            * (std::pow(m_change_threshold_multiplier, (m_cur_mipmap_level - 1)));
        
        if(m_cur_mipmap_level > m_final_mipmap_level && rel_score_delta < threshold) {
            change_active_mipmap_level(m_cur_mipmap_level-1);
        }
    }*/

    if(m_scaling_controller != nullptr) {
        if(m_scaling_controller->should_enlarge(*m_stats, *m_evolver,
                m_cur_mipmap_level)) {
            std::cout << "===== Setting mipmap level " << m_cur_mipmap_level-1 << " =====" 
                << std::endl;
            change_active_mipmap_level(m_cur_mipmap_level-1); 
        }
    }

    m_stats->new_generation(*m_evolver);
}
 
void EvolutionDriver::set_population(Population pop)
{
    m_evolver->set_population(std::move(pop)); 
    change_active_mipmap_level(m_initial_mipmap_level);
    m_stats->clear_scores();
}
 
const Image& EvolutionDriver::current_mipmap_level() const
{
    return m_mipmap->get_image_level(m_cur_mipmap_level); 
}
 
void EvolutionDriver::set_scaling_controller(
        std::unique_ptr<AdaptiveScalingController> controller)
{
    m_scaling_controller = std::move(controller);
}
 
void EvolutionDriver::change_active_mipmap_level(int new_level)
{
    if(m_cur_mipmap_level != new_level) {
        m_cur_mipmap_level = new_level; 
        if(m_mipmap != nullptr) {
            m_evolver->set_target_image(
                    m_mipmap->get_image_level(m_cur_mipmap_level).clone()); 
        }
        m_stats->clear_scores();
    }
}
 
