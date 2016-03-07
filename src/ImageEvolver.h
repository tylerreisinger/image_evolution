#ifndef IMAGEEVOLVER_H_
#define IMAGEEVOLVER_H_

#include <vector>
#include <memory>
#include <random>

#include "State.h"
#include "Image.h"
#include "Population.h"
#include "Color.h"
#include "Mutator.h"

class ImageEvolver {
public:
    using GeneratorType = std::default_random_engine;
    using ScoreType = State::ScoreType;

    static constexpr int POINTS_PER_GEOM = 4;
    static constexpr int POINTS_PER_COLOR = 4;
    static constexpr int POINTS_PER_ELEM = POINTS_PER_GEOM + POINTS_PER_COLOR;

    static std::unique_ptr<Mutator> default_mutator() {
        return std::make_unique<Mutator>(Mutator::default_mutator());
    }

    ImageEvolver(std::unique_ptr<Mutator> mutator = default_mutator());

    ImageEvolver(Population initial_population, std::unique_ptr<Mutator> mutator = 
            default_mutator());
    ~ImageEvolver() = default;

    ImageEvolver(const ImageEvolver& other) = delete;
    ImageEvolver(ImageEvolver&& other) noexcept = delete;
    ImageEvolver& operator =(const ImageEvolver& other) = delete;
    ImageEvolver& operator =(ImageEvolver&& other) noexcept = delete;

    Population& population() {return m_population;}
    const Population& population() const {return m_population;}

    double best_score() const;

    std::size_t population_size() const {return m_population.size();}

    int generation_number() const {return m_gen_number;}

    State::ScoreType score_state(const State& state) const;

    State& mutate_state(State& state);

    void set_population(Population new_population);

    std::unique_ptr<Image> render_state(const State& state);

    void print_state(std::ostream& stream, const State& state);

    void advance_generation();

    void set_target_image(std::unique_ptr<Image> target_image);
    const Image& target_image() const {return *m_target_image;}
    const Image& bg_image() const {return *m_bg_image;}

    State::ScoreType compute_total_score();

    Mutator& mutator() {return *m_mutator;}
    void set_mutator(std::unique_ptr<Mutator> mutator);

    GeneratorType& get_rng() {return m_rng;}

    void apply_state(const State& state, Image& image) const;

    const Colorf& bg_color() const {return m_bg_color;}

protected:
    std::vector<ScoreType> compute_rel_scores(ScoreType total_score);
    void update_scores(Population& pop, bool force=false);
    void set_bg_image();
    State& select_parent(const std::vector<ScoreType>& rel_scores,
            ScoreType select_pos);
    Population select_survivors(Population& total_pop, int n_way);

    std::unique_ptr<Mutator> m_mutator;

    Population m_population;
    int m_gen_number = 0;
    Colorf m_bg_color = Colorf(1.0,1.0,1.0,1.0);

    std::unique_ptr<Image> m_target_image;
    std::unique_ptr<Image> m_bg_image;
    mutable GeneratorType m_rng;
};

#endif
