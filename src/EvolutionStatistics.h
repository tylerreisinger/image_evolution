#ifndef EVOLUTIONSTATISTICS_H_
#define EVOLUTIONSTATISTICS_H_

#include <deque>

class ImageEvolver;

class EvolutionStatistics {
public:
    static constexpr int SCORE_BACKLOG_SIZE = 100;

    EvolutionStatistics();
    ~EvolutionStatistics();

    EvolutionStatistics(const EvolutionStatistics& other) = delete;
    EvolutionStatistics(EvolutionStatistics&& other) noexcept = delete;
    EvolutionStatistics& operator =(const EvolutionStatistics& other) = delete;
    EvolutionStatistics& operator =(EvolutionStatistics&& other) noexcept = delete;

    void new_generation(const ImageEvolver& evolver);

protected:
    double compute_score_delta();

    std::deque<double> m_prev_max_scores;
};

#endif
