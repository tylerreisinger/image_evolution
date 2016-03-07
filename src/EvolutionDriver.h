#ifndef EVOLUTIONDRIVER_H_
#define EVOLUTIONDRIVER_H_

#include <memory>

#include "ImageEvolver.h"

class MipmapCollection;
class State;

class EvolutionDriver {
public:
    using GeneratorType = ImageEvolver::GeneratorType;

    EvolutionDriver();
    ~EvolutionDriver();

    EvolutionDriver(const EvolutionDriver& other) = delete;
    EvolutionDriver(EvolutionDriver&& other) noexcept = delete;
    EvolutionDriver& operator =(const EvolutionDriver& other) = delete;
    EvolutionDriver& operator =(EvolutionDriver&& other) noexcept = delete;

    void set_target_image(std::unique_ptr<Image> target_image);

    std::unique_ptr<Image> render_state(const State& state);

    const Population& population() const {return m_evolver->population();}

    int generation_number() const {return m_evolver->generation_number();}

    void advance_generation();

    void set_population(Population pop) {m_evolver->set_population(std::move(pop));}

    const Image& current_mipmap_level() const;

    GeneratorType& get_rng() {return m_evolver->get_rng();}

    ImageEvolver& evolver() {return *m_evolver;}
protected:
    void change_active_mipmap_level(int new_level);

    int m_cur_mipmap_level = 2;
    std::unique_ptr<MipmapCollection> m_mipmap;
    std::unique_ptr<ImageEvolver> m_evolver;
    std::unique_ptr<Image> m_full_bg_image;
};

#endif
