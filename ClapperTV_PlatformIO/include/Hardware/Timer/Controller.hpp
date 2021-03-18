#pragma once

#include <type_traits.h>
#include <Hardware/Modules.hpp>
#include <Hardware/PWM/Prescale.hpp>

#include <avr/interrupt.h>

namespace Hardware {
namespace Timer {

volatile uint16_t gOverflowCounter = 0;

template<typename TimerType, uint16_t Prescale>
class Controller {
public:
    Controller(){
        static_assert(!std::is_same<TimerType,Module::TIMER0>(), "Timer0 is currently not supported.");
        Init();
    }

    void Init(){

        // Setup prescaler
        PWM::PrescaleSetup<TimerType, Prescale>::Setup(timer_);

        // Set normal mode
        timer_.TCCRAReg.DeactivateBits(timer_.TCCRAReg.WGM0, timer_.TCCRAReg.WGM1);
        timer_.TCCRBReg.DeactivateBits(timer_.TCCRBReg.WGM2, timer_.TCCRBReg.WGM3);

    }

    void Reset(){
        timer_.TCNTH.Set(0);
        timer_.TCNTL.Set(0);
        SetOverflowCount(0);
    }

    inline void EnableInterrupt(){timer_.TimskReg.ActivateBits(timer_.TimskReg.TOIE);}

    inline void DisableInterrupt(){timer_.TimskReg.DeactivateBits(timer_.TimskReg.TOIE);}


    inline uint64_t GetOverflowCount(){return gOverflowCounter;}
    inline void SetOverflowCount(uint64_t val){gOverflowCounter = val;}

private:
    TimerType timer_;

};


}
}

ISR (TIMER1_OVF_vect)
{
    Hardware::Timer::gOverflowCounter++;
}