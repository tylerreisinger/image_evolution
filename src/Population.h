#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>

#include "State.h"

class Population {
public:
    using iterator = std::vector<State>::iterator;
    using const_iterator = std::vector<State>::const_iterator;

    Population() = default;
    Population(std::vector<State> states);
    ~Population() = default;

    Population(const Population& other) = default;
    Population(Population&& other) noexcept;
    Population& operator =(const Population& other) = default;
    Population& operator =(Population&& other) noexcept;

    State& operator [](std::size_t idx) {return m_states[idx];}
    const State& operator [](std::size_t idx) const {return m_states[idx];}

    Population clone() const {
        return Population(m_states);
    }

    void clear() {
        return m_states.clear();
    }

    State& add_state(State state);

    std::size_t size() const {
        return m_states.size();
    }

    void sort_by_score();

    State::ScoreType total_score() const;

    State* data() {return m_states.data();}
    const State* data() const {return m_states.data();}

    State& front() {return m_states.front();}
    State& back() {return m_states.back();}

    iterator begin() {return m_states.begin();}
    iterator end() {return m_states.end();}

    const_iterator begin() const {return m_states.begin();}
    const_iterator end() const {return m_states.end();}

protected:
    std::vector<State> m_states;
};

template<typename Rng>
inline Population make_random_fixed_size_population(int pop_size, int state_size, Rng& rng) {
    Population pop;
    for(int n = 0; n < pop_size; ++n) {
        auto& state = pop.add_state(random_state(state_size, rng));
    }

    return pop;
}

#endif
