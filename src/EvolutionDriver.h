#ifndef EVOLUTIONDRIVER_H_
#define EVOLUTIONDRIVER_H_

#include <vector>
#include <memory>
#include <random>

#include "State.h"
#include "Image.h"
#include "Population.h"
#include "Color.h"

class EvolutionDriver {
public:
    using GeneratorType = std::default_random_engine;
    using ScoreType = State::ScoreType;

    static constexpr int POINTS_PER_GEOM = 4;
    static constexpr int POINTS_PER_COLOR = 4;
    static constexpr int POINTS_PER_ELEM = POINTS_PER_GEOM + POINTS_PER_COLOR;

    EvolutionDriver();
    EvolutionDriver(Population initial_population);
    ~EvolutionDriver() = default;

    EvolutionDriver(const EvolutionDriver& other) = delete;
    EvolutionDriver(EvolutionDriver&& other) noexcept = delete;
    EvolutionDriver& operator =(const EvolutionDriver& other) = delete;
    EvolutionDriver& operator =(EvolutionDriver&& other) noexcept = delete;

    Population& population() {return m_population;}
    const Population& population() const {return m_population;}

    std::size_t population_size() const {return m_population.size();}

    State::ScoreType score_state(const State& state) const;
    void apply_state(const State& state, Image& image) const;

    State random_state(int num, GeneratorType& generator);

    State& mutate_state(State& state, double elem_mutate_probability);

    void set_population(std::vector<State> new_population);

    void initialize_random_population(int num_states, int state_size);

    void print_state(std::ostream& stream, const State& state);


    void advance_generation();

    void set_target_image(Image target_image);
    const Image& target_image() const {return *m_target_image;}
    const Image& bg_image() const {return *m_bg_image;}

    State::ScoreType compute_total_score();

protected:
    std::vector<ScoreType> compute_rel_scores(ScoreType total_score);
    void update_scores(Population& pop);
    void set_bg_image();
    State& select_parent(const std::vector<ScoreType>& rel_scores,
            ScoreType select_pos);
    Population select_survivors(Population& total_pop, int n_way);

    Population m_population;
    int m_gen_number = 0;
    Colorf m_bg_color = Colorf(1.0,1.0,1.0,1.0);

    std::unique_ptr<Image> m_target_image;
    std::unique_ptr<Image> m_bg_image;
    mutable std::default_random_engine m_rng;
};

#endif
