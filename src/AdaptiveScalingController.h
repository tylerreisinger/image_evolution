#ifndef ADAPTIVESCALINGCONTROLLER_H_
#define ADAPTIVESCALINGCONTROLLER_H_

class EvolutionStatistics;
class ImageEvolver;

class AdaptiveScalingController {
public:
    AdaptiveScalingController();
    virtual ~AdaptiveScalingController();

    AdaptiveScalingController(const AdaptiveScalingController& other) = delete;
    AdaptiveScalingController(AdaptiveScalingController&& other) noexcept = delete;
    AdaptiveScalingController& operator =(const AdaptiveScalingController& other) = delete;
    AdaptiveScalingController& operator =(AdaptiveScalingController&& other) noexcept = delete;

    virtual bool should_enlarge(const EvolutionStatistics& stats, 
            const ImageEvolver& evolver, int cur_mipmap) const;

    double enlarge_threshold_base() const {return m_enlarge_threshold_base;}
    double enlarge_threshold_multiplier() const {return m_enlarge_threshold_multiplier;}
    int initial_mipmap_level() const {return m_initial_mipmap_level;}
    int final_mipmap_level() const {return m_final_mipmap_level;}

    AdaptiveScalingController& set_enlarge_threshold_base(double value);
    AdaptiveScalingController& set_enlarge_threshold_multiplier(double value);
    AdaptiveScalingController& set_initial_mipmap_level(double value);
    AdaptiveScalingController& set_final_mipmap_level(double value);

protected:
    double m_enlarge_threshold_base = 1e-7;
    double m_enlarge_threshold_multiplier = 2.0;
    int m_initial_mipmap_level = 3;
    int m_final_mipmap_level = 1;
};

#endif
