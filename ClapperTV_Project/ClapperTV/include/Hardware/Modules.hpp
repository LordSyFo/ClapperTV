/*
 * Modules.h
 *
 * Created: 07/02/2021 17.14.19
 *  Author: hejmi
 */ 


#ifndef MODULES_H_
#define MODULES_H_

#include <Hardware/Register.hpp>
#include <Hardware/GPIO.hpp>

namespace Hardware {
namespace Module {

/* Constant modules (like timers, adc, etc.. ) */
struct TIMER0 {
	constexpr TIMER0() {
		
	}
	
	Register::TCCRA0	TCCRAReg;
	Register::TCCRB0	TCCRBReg;
	Register::OCRA0		OCRAReg;
	GPIO::OC0A			Output0;
	GPIO::OC1A			Output1;
	
};

}
}



#endif /* MODULES_H_ */