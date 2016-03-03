#include "EvolutionDriver.h"


EvolutionDriver::EvolutionDriver()
{ 
    m_evolver = std::make_unique<ImageEvolver>();
}
 
void EvolutionDriver::set_target_image(std::unique_ptr<Image> target_image)
{
    m_evolver->set_target_image(std::move(target_image)); 
}
 
void EvolutionDriver::advance_generation()
{
    m_evolver->advance_generation(); 
}
 
