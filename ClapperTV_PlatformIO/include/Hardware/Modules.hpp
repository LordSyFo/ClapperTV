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
	
	/* Registers */
	Register::TCCR0A_	TCCRAReg;
	Register::TCCR0B_	TCCRBReg;
	Register::OCR0A_	OCRAReg;
	GPIO::OC0A			Output0;
	GPIO::OC1A			Output1;
	
};

struct TIMER1 {
	constexpr TIMER1() {
		
	}
	
	/* Registers */
	Register::TCCR1A_	TCCRAReg;
	Register::TCCR1B_	TCCRBReg;
	Register::TCCR1C_ 	TCCRCReg;

	Register::OCR1AL_	OCRAL;
	Register::OCR1AH_	OCRAH;

	Register::OCR1BL_	OCRBL;
	Register::OCR1BH_	OCRBH;

	Register::OCR1CL_	OCRCL;
	Register::OCR1CH_	OCRCH;

	Register::TIMSK1_ 	TimskReg;

	Register::TCNT1H_	TCNTH;
	Register::TCNT1L_	TCNTL;

};

// TODO: Add support for more Timers

struct ADC0_ {
	constexpr ADC0_() {}

	/* Registers */
	Register::ADMUX_ ADMUXReg;
	Register::ADCSRB_ ADCSRBReg;
	Register::ADCSRA_ ADCSRAReg;
	Register::ADCH_ ADCHReg;
	Register::ADCL_ ADCLReg;

	GPIO::ADC0_ ADCGPIO;
	static constexpr uint8_t Id = 0;

};

//TODO: Add support for more ADCs

}
}



#endif /* MODULES_H_ */