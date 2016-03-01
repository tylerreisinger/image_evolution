#ifndef EVOLUTIONDRIVER_H_
#define EVOLUTIONDRIVER_H_

#include <memory>

#include "ImageEvolver.h"

class EvolutionDriver {
public:
    using GeneratorType = ImageEvolver::GeneratorType;

    EvolutionDriver();
    ~EvolutionDriver() = default;

    EvolutionDriver(const EvolutionDriver& other) = delete;
    EvolutionDriver(EvolutionDriver&& other) noexcept = delete;
    EvolutionDriver& operator =(const EvolutionDriver& other) = delete;
    EvolutionDriver& operator =(EvolutionDriver&& other) noexcept = delete;

    void set_target_image(Image target_image);

    const Population& population() const {return m_evolver->population();}

    int generation_number() const {return m_evolver->generation_number();}

    void advance_generation();

    void set_population(Population pop) {m_evolver->set_population(std::move(pop));}

    GeneratorType& get_rng() {return m_evolver->get_rng();}

    ImageEvolver& evolver() {return *m_evolver;}
protected:
    std::unique_ptr<ImageEvolver> m_evolver;
};

#endif
