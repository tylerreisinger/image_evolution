#include "EvolutionStatistics.h"

#include "ImageEvolver.h"

EvolutionStatistics::EvolutionStatistics()
{
 
}
 
EvolutionStatistics::~EvolutionStatistics()
{
 
}
 
void EvolutionStatistics::new_generation(const ImageEvolver& evolver)
{
    m_prev_max_scores.push_front(evolver.best_score()); 

    if(m_prev_max_scores.size() > SCORE_BACKLOG_SIZE) {
        m_prev_max_scores.pop_back();
    }
}
 
double EvolutionStatistics::compute_score_delta()
{
    double total = 0.0;

    for(int i = 0; i < SCORE_BACKLOG_SIZE; ++i) {
        double weight = (SCORE_BACKLOG_SIZE - i) / SCORE_BACKLOG_SIZE;
        total = m_prev_max_scores[i]*weight;
    }
}
 
