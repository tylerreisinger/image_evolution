#ifndef GUIBRIDGE_H_
#define GUIBRIDGE_H_

#include <thread>
#include <mutex>
#include <memory>
#include <tuple>
#include <condition_variable>

#include <QObject>

#include "Population.h"


class EvolutionDriver;
class Image;

class GuiBridge: public QObject {
    Q_OBJECT
public:

    GuiBridge(std::unique_ptr<EvolutionDriver> driver);
    ~GuiBridge();

    GuiBridge(const GuiBridge& other) = delete;
    GuiBridge(GuiBridge&& other) noexcept = delete;
    GuiBridge& operator =(const GuiBridge& other) = delete;
    GuiBridge& operator =(GuiBridge&& other) noexcept = delete;

    EvolutionDriver& evolution_driver() {return *m_driver;}

    void start_evolution();

    void resume();
    void stop();
    void pause();
    void step();

    int cur_generation() const;
    std::tuple<Population, int> get_current_evolution_state() const;

signals:
    void population_updated();
    void stopped();

protected: 
    void thread_func();
    void next_generation();
    void update_current_state();

    std::unique_ptr<EvolutionDriver> m_driver; 

    std::thread m_evolver_thread;

    mutable std::mutex m_progress_mutex;
    std::condition_variable m_proceed_cv;
    bool m_step = false;
    bool m_run = false;
    bool m_quit = false;

    mutable std::mutex m_cur_state_mutex;
    Population m_cur_population;
    int m_cur_generation = 0;
};

#endif
