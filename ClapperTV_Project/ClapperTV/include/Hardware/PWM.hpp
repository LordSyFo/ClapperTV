/*
 * PWM.h
 *
 * Created: 25/01/2021 11.31.25
 *  Author: hejmi
 */ 


#ifndef PWM_H_
#define PWM_H_

typedef unsigned long int uint;

#include "RegisterOperations/Mode.hpp"

namespace Hardware {
namespace PWM {

// TODO: Should just be templatized from timer number and frequency!
/* Static PWM class - cannot be changed after frequency is set */
template<typename TimerType, uint Frequency>
class Controller {
public:
	constexpr Controller(){
		SetupPins();
		Setup();
	}
	
	inline void SetupPins()
	{
		//DIRECTION_PORT |= (1<<PWM_PIN_A); 
		// TODO: Should be delegated to policy
		timer_.Output0.SetDirection(true);
		timer_.Output0.Deactivate();
		
	}
	
	void TurnOn(){
		return Mode<TimerType, Frequency>::TurnOn(timer_);
	}
	
	void TurnOff(){
		return Mode<TimerType, Frequency>::TurnOff(timer_);
	}
	
	inline void Setup() {
		Mode<TimerType, Frequency>::Setup(timer_);
	}
	
private:
	TimerType timer_;
};

}
}


#endif /* PWM_H_ */