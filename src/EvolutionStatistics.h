#ifndef EVOLUTIONSTATISTICS_H_
#define EVOLUTIONSTATISTICS_H_

#include <deque>

class ImageEvolver;

class EvolutionStatistics {
public:
    EvolutionStatistics();
    ~EvolutionStatistics();

    EvolutionStatistics(const EvolutionStatistics& other) = delete;
    EvolutionStatistics(EvolutionStatistics&& other) noexcept = delete;
    EvolutionStatistics& operator =(const EvolutionStatistics& other) = delete;
    EvolutionStatistics& operator =(EvolutionStatistics&& other) noexcept = delete;

    void new_generation(const ImageEvolver& evolver);

    double compute_score_delta();
    void clear_scores();

    bool is_backlog_full() const {return m_prev_max_scores.size() == m_score_backlog_size;}

protected:

    std::deque<double> m_prev_max_scores;
    std::deque<double> m_score_deltas;
    int m_score_backlog_size = 100;
};

#endif
