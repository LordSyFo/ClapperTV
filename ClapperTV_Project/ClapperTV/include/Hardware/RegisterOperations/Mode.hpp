/*
 * Mode.h
 *
 * Created: 29/01/2021 13.03.25
 *  Author: hejmi
 */ 


#ifndef MODE_H_
#define MODE_H_

#include "Config.hpp"

extern "C"{
	#include <stdlib.h>
};

#define F_CPU 16000000
#define PRESCALE_VALUE 1

namespace Hardware {
namespace PWM{

	// Mode types
	struct FastMode {};
	struct PhaseCorrectMode {};

	template<typename T, uint Frequency>
	struct ModeImpl;

	//TODO: Use dutycycle parameter!

	static uint FindOCRA(uint Frequency){
		unsigned long diff = F_CPU;
		unsigned long i = 1;
		
		for (i = 1; i < 256; i++){
			unsigned long tmp_freq = F_CPU * (1 / (PRESCALE_VALUE*2*i*2));
			
			/*
				diff1 = 3964000;
				diff2 = 1964000;
			*/
			
			if (diff > abs(tmp_freq-Frequency))
				diff = abs(tmp_freq-Frequency);
			else
				break;
			
		}
		return i;
	}

	template<uint Frequency>
	struct ModeImpl<FastMode, Frequency>{
		static void Set(){
			// TODO: Implement
			// Fastmode WGM(1 1 1) update on TOP = OCR0A
			//TCCRB |= (1<<WGM02);
			TCCRA |= (1<<WGM00) | (1<<WGM01) | (1<<COM0A1) & ~(1<<COM0A0);
			
			OCR0A = 126;
			
			
		}
	};
	
	template<uint Frequency>
	struct ModeImpl<PhaseCorrectMode, Frequency>{
		static void Set(){

			TCCRA |= (1<<COM0A0) | (1<<COM0B1) | (1<<WGM00);
			TCCRB |= (1<<WGM02);
			
			OCR0A = FindOCRA(Frequency);
			//OCR0B = 22;

		}
	};

	template<typename T, uint Frequency>
	struct Mode {
	
		static void Set(){
			return ModeImpl<T, Frequency>::Set();
		}
	
	};
		
}
}




#endif /* MODE_H_ */