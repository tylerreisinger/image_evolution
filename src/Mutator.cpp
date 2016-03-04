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
 
std::ostream& operator <<(std::ostream& stream, const Mutator& mutator) {
    stream << "Mutation Rate: " << mutator.mutation_rate() << std::endl; 
    stream << "Element Mutation Rate: " << mutator.element_mutation_rate() << std::endl; 
    stream << "Component Mutation Rate: " << mutator.component_mutation_rate() << std::endl; 
    stream << "Perturbation Width: " << mutator.perturbation_width() << std::endl; 
    stream << "Perturbation Chance: " << mutator.perturbation_chance() << std::endl; 
    stream << "Swap Chance: " << mutator.swap_chance() << std::endl; 
    return stream;
}
