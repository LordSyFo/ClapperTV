/*
 * PWM.h
 *
 * Created: 25/01/2021 11.31.25
 *  Author: hejmi
 */ 


#ifndef PWM_H_
#define PWM_H_

typedef unsigned long int uint;

#include <Hardware/Modules.hpp>
#include "Hardware/GPIO.hpp"
#include <Hardware/PWM/Prescale.hpp>
#include <type_traits.h>

namespace Hardware {
namespace PWM {

/* Static PWM class - cannot be changed after frequency is set */
template<typename TimerType, uint Frequency>
class Controller {
public:
	constexpr Controller(){
		static_assert(std::is_same<TimerType, Module::TIMER0>(), "Only TIMER0 is supported, at this time.");
		SetupPins();
		Setup();
	}
	
	inline void SetupPins()
	{
		//DIRECTION_PORT |= (1<<PWM_PIN_A); 
		// TODO: Should be delegated to policy
		timer_.Output0.SetDirection(GPIO::Direction::Output);
		timer_.Output0.Deactivate();
		
	}
	
	void TurnOn(){
		timer_.TCCRAReg.ActivateBits(timer_.TCCRAReg.COMA0);
	}
	
	void TurnOff(){
		timer_.TCCRAReg.DeactivateBits(timer_.TCCRAReg.COMA0);
	}
	
	inline void Setup() {

		timer_.TCCRAReg.ActivateBits(timer_.TCCRAReg.COMA0, timer_.TCCRAReg.COMB1, timer_.TCCRAReg.WGM0);
		timer_.TCCRBReg.ActivateBits(timer_.TCCRBReg.WGM2);

		PrescaleSetup<TimerType, kPrescale>::Setup(timer_);
		
		timer_.OCRAReg.Set(FindOCRA(Frequency));
	}
	
private:
	TimerType timer_;
	static constexpr uint kPrescale = 1;	// We use a constant prescale of 1 to keep stuff simple and to get a more precise frequency

private:
	long my_abs(long value) {
			long s = value >> 31;
			return (value ^ s) - s;
	}

	uint FindOCRA(uint freq){
		long diff = F_CPU;
		long i = 1;
		
		for (i = 1; i < 256; i++){
			long tmp_freq = F_CPU / kPrescale / 2 / i / 2;
			
			long tmp_diff = my_abs(tmp_freq - freq);
			
			if (diff > tmp_diff)
				diff = tmp_diff;
			else
				break;
			
		}
		
		return i - 1;
	}
};

}
}


#endif /* PWM_H_ */