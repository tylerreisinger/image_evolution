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
    //TODO
}
 
