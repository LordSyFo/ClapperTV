/*
 * PWM.h
 *
 * Created: 25/01/2021 11.31.25
 *  Author: hejmi
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "RegisterOperations/Config.hpp"

namespace Hardware {
namespace PWM {
	
using uint = unsigned long int;

/* Static PWM class - cannot be changed after frequency is set */
template<typename PrescalerPolicy, typename ModePolicy>
class Controller {
	public:
	constexpr Controller(){
		
		SetupPins();
		Setup();
		
	}
	
	inline void SetupPins()
	{
		//DIRECTION_PORT |= (1<<PWM_PIN_A); 
		DIRECTION_PORT = 0xFF;
		PWM_PORT_A = 0;
		
	}
	
	inline void Setup() {
		PrescalerPolicy::Set();
		ModePolicy::Set();
	}
	
};

}
}


#endif /* PWM_H_ */