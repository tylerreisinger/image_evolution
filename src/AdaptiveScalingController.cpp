#include "AdaptiveScalingController.h"

#include "EvolutionStatistics.h"
#include "ImageEvolver.h"

AdaptiveScalingController::AdaptiveScalingController()
{
 

}
 
AdaptiveScalingController::~AdaptiveScalingController()
{
 
}
 
 
bool AdaptiveScalingController::should_enlarge(const EvolutionStatistics& stats,
        const ImageEvolver& evolver, int cur_mipmap) const
{
    if(cur_mipmap > m_final_mipmap_level && stats.is_backlog_full()) {

        auto score_delta = stats.compute_score_delta();
        auto rel_score_delta = score_delta / evolver.best_score();

        double exponent = (cur_mipmap - m_final_mipmap_level - 1); 
        double threshold = m_enlarge_threshold_base * 
            std::pow(m_enlarge_threshold_multiplier, exponent);

        if(rel_score_delta < threshold) {
            return true;
        }
    }

    return false;
}
 
AdaptiveScalingController& AdaptiveScalingController::set_enlarge_threshold_base(
        double value)
{
    m_enlarge_threshold_base = value;
    return *this; 
}
 
AdaptiveScalingController& AdaptiveScalingController::set_enlarge_threshold_multiplier(
        double value)
{
    m_enlarge_threshold_multiplier = value;
    return *this; 
}
 
AdaptiveScalingController& AdaptiveScalingController::set_initial_mipmap_level(
        double value)
{
    m_initial_mipmap_level = value;
    return *this; 
}
 
AdaptiveScalingController& AdaptiveScalingController::set_final_mipmap_level(
        double value)
{
    m_final_mipmap_level = value;
    return *this; 
}
 
