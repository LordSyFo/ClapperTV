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
		SetupChannel();
		
		// Internal 5V reference
		adc_.ADMUXReg.ActivateBits(adc_.ADMUXReg.REFS0_);
	}

	inline void SetupChannel(){
		constexpr uint8_t MUXValue = ADCSelector<ADCType::Id>::value;

		// Select the appropriate channel
		uint8_t tmp = adc_.ADMUXReg.Get();
		tmp |= ((MUXValue & 1) | (MUXValue & 2) | (MUXValue & 4) | (MUXValue & 8) | (MUXValue & 16));
		adc_.ADMUXReg.Set(tmp);

		tmp = adc_.ADCSRBReg.Get();
		tmp |= (MUXValue & 0b00010000) >> 2;
		adc_.ADCSRBReg.Set(tmp);

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
		while(adc_.ADCSRAReg.Get() & adc_.ADCSRAReg.ADSC_);
	}

	// Should probably never be used
	inline float ReadVoltage(){
		uint16_t raw = Read();
		return (float)raw / 1024 * 5;
	}

	inline uint16_t Read(){
		StartConversion();
		WaitConversion();
		uint16_t low = adc_.ADCLReg.Get();
		return low | ((uint16_t)adc_.ADCHReg.Get() << 8);
	}

private:
	ADCType adc_;

};
	
	
}
}



#endif /* CONTROLLER_H_ */