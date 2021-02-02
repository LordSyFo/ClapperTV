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
	#include <Hardware/uart.h>
};

#define F_CPU 16000000
#define PRESCALE_VALUE 1

namespace Hardware {
namespace PWM{

	long my_abs(long value) {
		long s = value >> 31;
		return (value ^ s) - s;
	}

	// Mode types
	struct FastMode {};
	struct PhaseCorrectMode {};

	template<typename T, uint Frequency>
	struct ModeImpl;

	//TODO: Use dutycycle parameter!

	static uint FindOCRA(uint Frequency){
		long diff = F_CPU;
		long i = 1;
		
		for (i = 1; i < 256; i++){
			long tmp_freq = F_CPU / PRESCALE_VALUE / 2 / i / 2;
			
			long tmp_diff = my_abs(tmp_freq - Frequency);
			
			if (diff > tmp_diff)
				diff = tmp_diff;
			else
				break;
			
		}
		
		return i - 1;
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