#include "EvolutionDriver.h"

#include <iostream>
#include <numeric>

EvolutionDriver::EvolutionDriver()
{
}
 
EvolutionDriver::EvolutionDriver(Population initial_population):
    m_population(std::move(initial_population)) {
     
}
 
State::ScoreType EvolutionDriver::score_state(const State& state) const
{
    auto img_copy = m_bg_image->clone();
    apply_state(state, img_copy);
    return image_difference(*m_target_image, img_copy);
}
 
void EvolutionDriver::apply_state(const State& state, Image& image) const
{
    auto& points = state.points();

    auto geom_count = state.size() / POINTS_PER_ELEM; 

    for(std::size_t i = 0; i < geom_count; ++i) {
        auto idx = i*POINTS_PER_ELEM; 
        auto color_idx = idx + POINTS_PER_GEOM;

        float x1 = points[idx];
        float y1 = points[idx+1];
        float x2 = points[idx+2];
        float y2 = points[idx+3];

        float x_min, y_min;
        float x_max, y_max;
        std::tie(x_min, x_max) = std::minmax(x1, x2);
        std::tie(y_min, y_max) = std::minmax(y1, y2);

        auto color = Colorf(points[color_idx], points[color_idx+1], points[color_idx+2],
                points[color_idx+3]);

        image.draw_rectangle(x_min, y_min, x_max, y_max, color);
    }
}
 
State EvolutionDriver::random_state(int num_elems, GeneratorType& rng)
{
    std::uniform_real_distribution<float> pt_distribution(0.0, 1.0);

    State::StateVec pts(num_elems);

    std::generate_n(pts.begin(), num_elems, 
        [&pt_distribution, &rng](){return pt_distribution(rng);});

    return State(std::move(pts));
}

State& EvolutionDriver::mutate_state(State& state, double elem_mutate_probability)
{
    std::uniform_real_distribution<float> prob_dist(0.0, 1.0);
    std::uniform_real_distribution<float> value_dist(0.0, 1.0);

    for(int i = 0; i < state.size(); ++i) {
        if(prob_dist(m_rng) < elem_mutate_probability) {
            state.points()[i] = value_dist(m_rng);
        }
    }

    return state;
}
 
void EvolutionDriver::set_population(std::vector<State> new_population)
{
    m_population = std::move(new_population);
    m_gen_number = 0;
}
 
void EvolutionDriver::initialize_random_population(int num_states, int state_size)
{
    m_population.clear();
    m_gen_number = 0;

    for(int n = 0; n < num_states; ++n) {
        auto& state = m_population.add_state(random_state(state_size, m_rng));
        auto score = score_state(state);
        state.set_score(score);
    } 
}
 
 
void EvolutionDriver::print_state(std::ostream& stream, const State& state)
{
    if(state.has_score()) {
        stream << state.score() << " -- ";
    }
    stream << "[";
    for(auto it = state.points().begin(); it != state.points().end(); ++it) {
        stream << *it;
        if((it+1) != state.points().end()) {
            stream << ", ";
        }
    } 
    stream << "]";
}
 
State& EvolutionDriver::select_parent(const std::vector<ScoreType>& rel_scores, 
        ScoreType select_pos)
{
    ScoreType sum = 0.0;
    for(int i = 0; i < rel_scores.size(); ++i) {
        sum += rel_scores[i];
        if(select_pos < sum) {
            return m_population[i];
        }
    }

    return m_population.back();
}
 
void EvolutionDriver::advance_generation()
{
    int offspring_count = population_size();

    update_scores(m_population);
    auto total_score = compute_total_score();
    auto rel_scores = compute_rel_scores(total_score);

    std::cout << "Total Score: " << total_score << std::endl;

    for(int i = 0; i < rel_scores.size(); ++i) {
        std::cout << i << ": " << rel_scores[i] << std::endl;
    }

    std::uniform_real_distribution<ScoreType> parent_pos_dist(0.0, 1.0);
    std::uniform_int_distribution<int> partition_dist(0, m_population[0].size()-1);

    auto total_pop = m_population.clone();

    for(int i = 0; i < offspring_count; ++i) {
        auto pos = parent_pos_dist(m_rng);
        auto parent1 = select_parent(rel_scores, pos);
        pos = parent_pos_dist(m_rng);
        auto parent2 = select_parent(rel_scores, pos);

        auto partition = partition_dist(m_rng);

        auto offspring = two_parent_crossover(parent1, parent2, partition);
        mutate_state(offspring, 0.02);
        total_pop.add_state(std::move(offspring));
    }

    update_scores(total_pop);

    Population new_pop = select_survivors(total_pop, 2);

    m_population = std::move(new_pop);
    m_gen_number += 1;
}
 
void EvolutionDriver::set_target_image(Image target_image)
{
    m_target_image = std::make_unique<Image>(std::move(target_image)); 
    set_bg_image();
}
 
State::ScoreType EvolutionDriver::compute_total_score()
{
    auto total_score = std::accumulate(m_population.begin(), m_population.end(), 0.0,
        [](double& sum, const State& state) {
            return sum + state.score();
        }); 

    return total_score;
}
 
 
std::vector<State::ScoreType> EvolutionDriver::compute_rel_scores(
        State::ScoreType total_score)
{
    std::vector<State::ScoreType> rel_scores(population_size());

    //Since scores need minimized, we need to take 1/score and then renormalize to 1.
    std::transform(m_population.begin(), m_population.end(), rel_scores.begin(),
        [total_score](const State& state) {
            return 1 / (state.score() / total_score);
        });

    auto mag = std::accumulate(rel_scores.begin(), rel_scores.end(), 0.0);
    
    for(auto& score : rel_scores) {
        score = score / mag;
    }

    return std::move(rel_scores);
}
 
void EvolutionDriver::update_scores(Population& pop)
{
    for(auto& state : pop) {
        if(!state.has_score()) {
            state.set_score(score_state(state));
        }
    }
}
 
void EvolutionDriver::set_bg_image()
{
    auto image = std::make_unique<Image>(m_target_image->width(), m_target_image->height(),
            m_bg_color);
    m_bg_image = std::move(image);
}
 
Population EvolutionDriver::select_survivors(Population& total_pop, int n_way)
{
    Population new_pop;
    std::shuffle(total_pop.begin(), total_pop.end(), m_rng);

    int i = 0;

    auto it = total_pop.begin();

    auto compare_fn = [](const State& left, const State& right) {
            return left.score() < right.score();
        };

    for(int i = 0; i < total_pop.size(); i += n_way, it += n_way) {
        auto winner = std::min_element(it, it+n_way, compare_fn);
        new_pop.add_state(std::move(*winner));
    }

    if(it != total_pop.end()) {
        auto winner = std::min_element(it, total_pop.end(), compare_fn);
        new_pop.add_state(std::move(*winner));
    }

    return new_pop;
}
 
