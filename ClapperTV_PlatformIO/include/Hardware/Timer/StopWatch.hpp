#pragma once

#include <Hardware/Timer/Controller.hpp>

namespace Hardware {
namespace Timer {

class StopWatch {
public:
    StopWatch(){
        timerCtrl_.Init();
    }

    void Start() {
        timerCtrl_.DisableInterrupt();

        timerCtrl_.Reset();     // Reset overflow counter and internal timer counter

        timerCtrl_.EnableInterrupt();
    }

    inline uint64_t GetMs(){
        return gOverflowCounter * kMsPrTick;
    } 

    uint64_t Stop(){
        timerCtrl_.DisableInterrupt();
        return GetMs();  // return in ms
    }

private:
    static constexpr unsigned int kPrescale = 1;
    static constexpr unsigned int kMsPrTick = 65365.f / (F_CPU / kPrescale) * 1000.f;

    Controller<Module::TIMER1, kPrescale> timerCtrl_;  // TODO: Maybe the timer should be decided on runtime, to determine a free timer?
    
};

}
}