#include "Mutator.h"

#include "State.h"

Mutator& Mutator::set_mutation_rate(float value)
{
    m_mutation_rate = value; 
    return *this;
}
 
Mutator& Mutator::set_component_mutation_rate(float value)
{
    m_component_mutate_rate = value; 
    return *this;
}
 
Mutator& Mutator::set_element_mutation_rate(float value)
{
    m_element_mutate_rate = value; 
    return *this;
}
 
Mutator& Mutator::set_perturbation_chance(float value)
{
    m_perturbation_chance = value;
    assert(replace_chance() >= 0.0);
    return *this; 
}
 
Mutator& Mutator::set_swap_chance(float value)
{
    m_swap_chance = value;
    assert(replace_chance() >= 0.0);
    return *this; 
}

Mutator& Mutator::set_perturbation_width(float value)
{
    m_perturbation_width = value;
    return *this; 
}
 
Mutator::MutateMode Mutator::select_mutation_mode(float selector) const
{
    if(selector < perturbation_chance()) {
        return MutateMode::Perturb;
    } else if(selector < perturbation_chance()+swap_chance()) {
        return MutateMode::Swap;
    } else {
        return MutateMode::Replace;
    }
}
 
