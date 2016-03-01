#include "Population.h"

#include <algorithm>

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
 
void Population::sort_by_score()
{
    std::sort(m_states.begin(), m_states.end(), [](const State& s1, const State& s2) {
            return s1.score() < s2.score(); 
        });
}
 
