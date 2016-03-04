#ifndef MUTATOR_H_
#define MUTATOR_H_

#include <random>
#include <ostream>

#include "State.h"

class Mutator {
public:
    enum class MutateMode {
        Replace,
        Perturb,
        Swap
    };

    constexpr Mutator();
    ~Mutator() = default;

    Mutator(const Mutator& other) = default;
    Mutator(Mutator&& other) noexcept = default;
    Mutator& operator =(const Mutator& other) = default;
    Mutator& operator =(Mutator&& other) noexcept = default;

    static constexpr Mutator default_mutator();

    template<typename Rng>
    void mutate_state(State& state, Rng& rng);

    float mutation_rate() const {return m_mutation_rate;}
    float component_mutation_rate() const {return m_component_mutate_rate;}
    float element_mutation_rate() const {return m_element_mutate_rate;}

    float perturbation_chance() const {return m_perturbation_chance;}
    float swap_chance() const {return m_swap_chance;}
    float perturbation_width() const {return m_perturbation_width;}

    float component_mutate_chance() const {return m_mutation_rate*m_component_mutate_rate;}
    float element_mutate_chance() const {return m_mutation_rate*m_element_mutate_rate;}

    //Replace chance is the remaining value needed to get a total
    //chance of 1.
    float replace_chance() const {return 1.0-perturbation_chance()-swap_chance();}

    Mutator& set_mutation_rate(float value);
    Mutator& set_component_mutation_rate(float value);
    Mutator& set_element_mutation_rate(float value);
    Mutator& set_perturbation_chance(float value);
    Mutator& set_swap_chance(float value);
    Mutator& set_perturbation_width(float value);

protected:
    template<typename Rng>
    void mutate_element(State& state, int idx, Rng& rng);    

    template<typename Rng>
    void mutate_component(State& state, int idx, Rng& rng);

    template<typename Rng>
    void replace_component(State& state, int idx, Rng& rng);

    template<typename Rng>
    void perturb_component(State& state, int idx, Rng& rng);

    template<typename Rng>
    void swap_component(State& state, int idx, Rng& rng);

    template<typename Rng>
    void swap_element(State& state, int idx, Rng& rng);

    MutateMode select_mutation_mode(float selector) const;


    //Overall mutation rate
    float m_mutation_rate = 0.02;

    //Weight towards single component mutations. This is
    //multiplied by `m_mutation_rate` to get the total
    //mutation chance for each component. Element mutations
    //take precedence.
    float m_component_mutate_rate = 1.00;

    //Weight towards full geometric element mutations.
    //This is multiplied by `m_mutation_rate` to get the
    //total mutation chance for each geometric element.
    float m_element_mutate_rate = 0.50;

    //Relative chance to perturb values.
    float m_perturbation_chance = 0.20;
    //Width of the Gaussian of the perturbation offset
    float m_perturbation_width = 0.05;
    
    //Relative chance to swap values
    float m_swap_chance = 0.10;
};

inline constexpr Mutator::Mutator() {
 
}
 
inline constexpr Mutator Mutator::default_mutator() {
    return Mutator(); 
}

template<typename Rng>
inline void Mutator::mutate_state(State& state, Rng& rng) {
    std::uniform_real_distribution<float> prob_dist(0.0, 1.0);

    for(int i = 0; i < state.size(); ++i) {
        //Are we at the start of an element? 
        if(i % state.element_size() == 0) {
            //Should we mutate the element?
            if(prob_dist(rng) < element_mutate_chance()) {
                mutate_element(state, i, rng);
                //If we do mutate the element, skip consideration of the
                //rest of the element's points.
                i += state.element_size() - 1;
            }
        } else {
            //Should we mutate the component?
            if(prob_dist(rng) < component_mutate_chance()) {
                mutate_component(state, i, rng);
            }
        } 
    }  
}

template<typename Rng>
inline void Mutator::mutate_element(State& state, int idx, Rng& rng) {
    std::uniform_real_distribution<float> prob_dist(0.0, 1.0); 

    auto mutate_mode_selector = prob_dist(rng);

    switch(select_mutation_mode(mutate_mode_selector)) {
        case MutateMode::Perturb:
            for(int i = 0; i < state.element_size(); ++i) {
                auto component_idx = idx+i;

                if(component_idx < state.size()) {
                    perturb_component(state, component_idx, rng);
                }
            }
            break;
        case MutateMode::Swap:
            swap_element(state, idx, rng);
            break;
        case MutateMode::Replace:
            for(int i = 0; i < state.element_size(); ++i) {
                auto component_idx = idx+i;

                if(component_idx < state.size()) {
                    replace_component(state, component_idx, rng);
                }
            }
            break;
    }
}
 
template<typename Rng>
inline void Mutator::mutate_component(State& state, int idx, Rng& rng) {
    std::uniform_real_distribution<float> prob_dist(0.0, 1.0); 

    auto mutate_mode_selector = prob_dist(rng);

    switch(select_mutation_mode(mutate_mode_selector)) {
        case MutateMode::Perturb:
            perturb_component(state, idx, rng);
            break;
        case MutateMode::Swap:
            swap_component(state, idx, rng);
            break;
        case MutateMode::Replace:
            replace_component(state, idx, rng);
            break;
    }
}
 
 
template<typename Rng>
inline void Mutator::replace_component(State& state, int idx, Rng& rng) {
    std::uniform_real_distribution<float> value_dist(0.0, 1.0);

    state[idx] = value_dist(rng);
}

template<typename Rng>
inline void Mutator::perturb_component(State& state, int idx, Rng& rng) {
    std::normal_distribution<float> offset_dist(0.0, m_perturbation_width);

    state[idx] += offset_dist(rng);

    //Make sure the component remains in bounds
    state[idx] = std::min(state[idx], 1.0f);
    state[idx] = std::max(state[idx], 0.0f);
}
 
template<typename Rng>
inline void Mutator::swap_component(State& state, int idx, Rng& rng) {
    std::uniform_int_distribution<int> swap_target_dist(0, state.size()-1);

    auto swap_partner_idx = swap_target_dist(rng);

    std::swap(state[idx], state[swap_partner_idx]);
}
 
template<typename Rng>
inline void Mutator::swap_element(State& state, int idx, Rng& rng) {
    std::uniform_int_distribution<int> swap_target_dist(0, state.element_count()-1);

    auto swap_partner = swap_target_dist(rng);
    auto partner_element_idx = swap_partner*state.element_size();

    for(int i = 0; i < state.element_size(); ++i) {
        std::swap(state[idx+i], state[partner_element_idx+i]);
    } 

}

std::ostream& operator <<(std::ostream& stream, const Mutator& mutator);
 
#endif
