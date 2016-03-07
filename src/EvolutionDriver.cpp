#include "EvolutionDriver.h"

#include "MipmapCollection.h"
#include "State.h"

EvolutionDriver::EvolutionDriver()
{ 
    m_evolver = std::make_unique<ImageEvolver>();
}
 
void EvolutionDriver::set_target_image(std::unique_ptr<Image> target_image)
{
    m_mipmap = std::make_unique<MipmapCollection>(std::move(target_image));
    std::cout << m_mipmap->num_levels() << std::endl;
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
    if(m_evolver->generation_number() == 1000) {
        change_active_mipmap_level(1);
    } else if(m_evolver->generation_number() == 2000) {
        change_active_mipmap_level(0);
    }
}
 
const Image& EvolutionDriver::current_mipmap_level() const
{
    return m_mipmap->get_image_level(m_cur_mipmap_level); 
}
 
void EvolutionDriver::change_active_mipmap_level(int new_level)
{
    m_cur_mipmap_level = new_level; 
    m_evolver->set_target_image(m_mipmap->get_image_level(m_cur_mipmap_level).clone()); 
}
 
