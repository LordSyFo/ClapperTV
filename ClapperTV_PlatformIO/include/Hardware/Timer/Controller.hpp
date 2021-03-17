#pragma once

#include <type_traits.h>
#include <Hardware/Modules.hpp>
#include <Hardware/PWM/Prescale.hpp>

#include <avr/interrupt.h>

namespace Hardware {
namespace Timer {

volatile uint16_t gOverflowCounter = 0;

template<typename TimerType>
class Controller {
public:
    Controller(){
        static_assert(!std::is_same<TimerType,Module::TIMER0>(), "Timer0 is currently not supported.");
        Init();
    }

    void Init(){

        // Setup prescaler
        PWM::PrescaleSetup<TimerType, kPrescale>::Setup(timer_);

        // Set normal mode
        timer_.TCCRAReg.DeactivateBits(timer_.TCCRAReg.WGM0, timer_.TCCRAReg.WGM1);
        timer_.TCCRBReg.DeactivateBits(timer_.TCCRBReg.WGM2, timer_.TCCRBReg.WGM3);

        // Enable timer overflow interrupt
        EnableInterrupt();

        sei();  // Enable global interrupts

    }

    void Reset(){
        timer_.TCNTH.Set(0);
        timer_.TCNTL.Set(0);
    }

    void Start() {
        DisableInterrupt();

        gOverflowCounter = 0;   // Reset counter
        Reset();

        EnableInterrupt();
    }

    inline uint64_t GetMs(){
        return gOverflowCounter * kMsPrTick;
    } 

    uint64_t Stop(){
        DisableInterrupt();
        return GetMs();  // return in ms
    }

    inline void EnableInterrupt(){timer_.TimskReg.ActivateBits(timer_.TimskReg.TOIE);}

    inline void DisableInterrupt(){timer_.TimskReg.DeactivateBits(timer_.TimskReg.TOIE);}


    uint64_t GetOverflowCount(){return gOverflowCounter;}

private:
    TimerType timer_;   //TODO: CHANGE BACK TO TIMERTYPE

    static constexpr unsigned int kPrescale = 1;
    static constexpr unsigned int kMsPrTick = 65365.f / (F_CPU / kPrescale) * 1000.f;

};


}
}

ISR (TIMER1_OVF_vect)
{
    Hardware::Timer::gOverflowCounter++;
}