#ifndef STATE_H_
#define STATE_H_

#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Point.h"

class State {
public:
    using StateVec = std::vector<float>;
    using ScoreType = double;

    State();
    ~State() = default;
    State(StateVec points);
    State(const State& other);

    State(State&& other) noexcept;
    State& operator =(State&& other) noexcept;
    State& operator =(const State& other) = delete;

    float& operator [](std::size_t idx) {return m_state_vector[idx];}
    float operator [](std::size_t idx) const {return m_state_vector[idx];}

    State clone() const;

    //Number of values per element.
    int element_size() const;

    void set_score(ScoreType score) {
        m_score = score;
    }

    ScoreType score() const { 
        return m_score;
    }

    bool has_score() const {
        return (m_score >= 0.0);
    }

    std::size_t size() const {
        return m_state_vector.size();
    }

    std::size_t element_count() const {
        return m_state_vector.size() / element_size();
    }

    const StateVec& points() const {
        return m_state_vector;
    }

    StateVec& points() {
        return m_state_vector;
    }

protected:
    StateVec m_state_vector;
    ScoreType m_score = -1;
};

State two_parent_crossover(const State& left, const State& right, int partition);

template<typename Rng>
State random_state(int size, Rng& rng) {
    std::uniform_real_distribution<float> pt_distribution(0.0, 1.0);

    State::StateVec pts(size);

    std::generate_n(pts.begin(), size, 
        [&pt_distribution, &rng](){return pt_distribution(rng);});

    return State(std::move(pts));
}

#endif
