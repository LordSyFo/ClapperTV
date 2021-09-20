/*
 * Controller.h
 *
 * Created: 10/02/2021 17.12.48
 *  Author: hejmi
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdint.h>
#include <Hardware/ADC/ADCSelector.hpp>
#include <Hardware/Modules.hpp>

namespace Hardware{
namespace AnalogToDigital{

template<typename ADCType>
class Controller {

public:

	Controller(){
		Init();
		Enable();
	}

	//TODO: When reading from the ADC, you should read from ADCL first to stop the conversion before reading the ADCH
	//TODO: You should clear ADEN bit in ADMUX when going into powersave mode!

	inline void Init(){
		// Set GPIO Direction
		adc_.ADCGPIO.SetDirection(GPIO::Direction::Input);

		// Select the channel
		SelectChannel(0);
		
		// Internal 5V reference
		adc_.ADMUXReg.ActivateBits(adc_.ADMUXReg.REFS0_);
		
		// Set prescaler = 128 -> 8MHz / 128 = 62.5kHz
		adc_.ADCSRAReg.ActivateBits(adc_.ADCSRAReg.ADPS0_,
					    adc_.ADCSRAReg.ADPS1_,
					    adc_.ADCSRAReg.ADPS0_,
					    adc_.ADCSRAReg.ADEN_);
	}

	inline void SelectChannel(uint8_t channel)
	{
		uint8_t tmp = adc_.ADMUXReg.Get();
		adc_.ADMUXReg.Set(tmp & (0xF0 + channel));
	}

	inline void Enable(){
		adc_.ADCSRAReg.ActivateBits(adc_.ADCSRAReg.ADEN_);
	}

	inline void Disable(){
		adc_.ADCSRAReg.DeactivateBits(adc_.ADCSRAReg.ADEN_);
	}

	inline void StartConversion(){
		adc_.ADCSRAReg.ActivateBits(adc_.ADCSRAReg.ADSC_);
	}

	inline void WaitConversion(){
		while(ADCSRA & (1<<ADSC));
		//while(adc_.ADCSRAReg.Get() & adc_.ADCSRAReg.ADSC_);	TODO: Find out why the hell this doesnt work? I added specialization for MEM8 adresses
	}

	// Should probably never be used
	inline float ReadVoltage(){
		uint16_t raw = Read();
		return (float)raw / 1024 * 5;
	}

	inline uint16_t Read(){
		//select ADC channel with safety mask
		SelectChannel(0);

		//single conversion mode
		//ADCSRA |= (1<<ADSC);

		// wait until ADC conversion is complete
		//while( ADCSRA & (1<<ADSC) );
		//return ADC;

		StartConversion();
		WaitConversion();
		return ADC;

		uint16_t low = adc_.ADCLReg.Get();
		return low | ((uint16_t)adc_.ADCHReg.Get() << 8);
	}

private:
	ADCType adc_;

};
	
	
}
}



#endif /* CONTROLLER_H_ */