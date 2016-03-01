#include "GuiBridge.h"

#include <iostream>

#include "EvolutionDriver.h"

GuiBridge::GuiBridge(std::unique_ptr<EvolutionDriver> driver):
    m_driver(std::move(driver))
{
    update_current_state();
}
 
GuiBridge::~GuiBridge()
{
    if(m_evolver_thread.joinable()) {
        stop();
        m_evolver_thread.join(); 
    }
}
 
void GuiBridge::start_evolution()
{
    m_evolver_thread = std::thread(&GuiBridge::thread_func, this);
}
 
std::tuple<Population, int> GuiBridge::get_current_evolution_state() const
{
    std::lock_guard<std::mutex> lock(m_cur_state_mutex); 

    return std::make_tuple(m_cur_population, m_cur_generation);
}
 
void GuiBridge::resume()
{
    std::unique_lock<std::mutex> lck(m_progress_mutex);
    m_step = true;
    m_run = true;
    m_proceed_cv.notify_one();
}

void GuiBridge::stop()
{
    std::unique_lock<std::mutex> lck(m_progress_mutex);
    m_step = true;
    m_run = false;
    m_quit = true;
    m_proceed_cv.notify_one();
}
 
void GuiBridge::pause()
{
    std::unique_lock<std::mutex> lck(m_progress_mutex);
    m_step = false;
    m_run = false;
}
 
void GuiBridge::step()
{ 
    std::cout << "Step" << std::endl;
    std::unique_lock<std::mutex> lock(m_progress_mutex);
    m_step = true;
    m_proceed_cv.notify_one();
}
 
int GuiBridge::cur_generation() const
{
    std::lock_guard<std::mutex> lock(m_cur_state_mutex); 
    return m_cur_generation;
}
 
void GuiBridge::thread_func()
{
    while(true) {
        {
            std::unique_lock<std::mutex> lck(m_progress_mutex);

            if(!m_step) {
                emit stopped();
            }
            while(!m_step) {
                m_proceed_cv.wait(lck);
            }

            m_step = false;
            if(m_quit) {
                break;
            }
            if(m_run) {
                m_step = true;
            }
        }
        
        next_generation();
    }
}
 
void GuiBridge::next_generation()
{
    m_driver->advance_generation();

    update_current_state();
    emit population_updated();

}
 
void GuiBridge::update_current_state()
{
    std::lock_guard<std::mutex> lock(m_cur_state_mutex);
    m_cur_population = m_driver->population().clone();
    m_cur_generation = m_driver->generation_number();
}
 
