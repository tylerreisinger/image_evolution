#include "Population.h"

Population::Population(std::vector<State> states):
    m_states(std::move(states)) {

}
Population::Population(Population&& other) noexcept:
    m_states(std::move(other.m_states))
{
 
}
 
Population& Population::operator=(Population&& other) noexcept
{
    m_states = std::move(other.m_states);

    return *this; 
}
 
State& Population::add_state(State state)
{
    m_states.emplace_back(std::move(state));
    return m_states.back();
}
 
