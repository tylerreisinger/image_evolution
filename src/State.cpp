#include "State.h"

State::State(const State& other):
    m_state_vector(other.m_state_vector),
    m_score(other.m_score)
{
}

State::State(StateVec points):
    m_state_vector(std::move(points))
{
}


State::State(State&& other) noexcept:
    m_state_vector(std::move(other.m_state_vector)), m_score(other.m_score)
{
}
 
State& State::operator=(State&& other) noexcept
{
    m_state_vector = std::move(other.m_state_vector);
    m_score = other.m_score;
    return *this; 
}
 
State State::clone() const
{
    return State(*this); 
}
 
State two_parent_crossover(const State& left, const State& right, int partition) {
    assert(partition < right.size());
    int offspring_len = right.size();

    State::StateVec offspring(offspring_len);
    std::copy_n(left.points().begin(), partition, offspring.begin());
    std::copy(right.points().begin()+partition, right.points().end(),
            offspring.begin()+partition);

    return State(std::move(offspring));
}
