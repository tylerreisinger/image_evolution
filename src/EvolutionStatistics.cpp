#include "EvolutionStatistics.h"

#include <cmath>

#include "ImageEvolver.h"

EvolutionStatistics::EvolutionStatistics()
{
 
}
 
EvolutionStatistics::~EvolutionStatistics()
{
 
}
 
void EvolutionStatistics::new_generation(const ImageEvolver& evolver)
{
    if(m_prev_max_scores.size() > 0) {
        m_score_deltas.push_front(m_prev_max_scores.front() - evolver.best_score());
    }

    m_prev_max_scores.push_front(evolver.best_score()); 

    if(m_prev_max_scores.size() > m_score_backlog_size) {
        m_prev_max_scores.pop_back();
    }
    if(m_score_deltas.size() > m_score_backlog_size) {
        m_score_deltas.pop_back();
    }
}
 
double EvolutionStatistics::compute_score_delta() const
{
    double total = 0.0;
    double total_weight = 0.0;

    int max_idx = m_score_deltas.size();

    for(int i = 0; i < max_idx; ++i) {
        double weight = static_cast<double>(max_idx - i) / max_idx;
        total += m_score_deltas[i]*weight; 
        total_weight += weight;
    }

    return total / total_weight;
}
 
void EvolutionStatistics::clear_scores()
{
    m_prev_max_scores.clear(); 
}
 
