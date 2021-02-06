/*
 * Mode.h
 *
 * Created: 29/01/2021 13.03.25
 *  Author: hejmi
 */ 


#ifndef MODE_H_
#define MODE_H_

#include "Register.hpp"
#include "Prescale.hpp"

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
	
	template<typename TimerType,uint Frequency>
	struct ModeImpl {
		static void Setup(TimerType& Timer){
			
			Timer.TCCRAReg.ActivateBits(Timer.TCCRAReg.COMA0, Timer.TCCRAReg.COMB1, Timer.TCCRAReg.WGM0);
			Timer.TCCRBReg.ActivateBits(Timer.TCCRBReg.WGM2);
			
			PrescaleSetup<TimerType, PRESCALE_VALUE>::Setup(Timer);
			
			Timer.OCRAReg.Set(FindOCRA(Frequency));

		}
		
		static void TurnOn(TimerType& Timer){
			Timer.TCCRAReg.ActivateBits(Timer.TCCRAReg.COMA0);
		}
		
		static void TurnOff(TimerType& Timer){
			Timer.TCCRAReg.DeactivateBits(Timer.TCCRAReg.COMA0);
		}
	};

	template<typename TimerType, uint Frequency>
	struct Mode {
		
		inline static void TurnOn(TimerType& Timer)
		{
			return ModeImpl<TimerType, Frequency>::TurnOn(Timer);
		}
		
		inline static void TurnOff(TimerType& Timer)
		{
			return ModeImpl<TimerType, Frequency>::TurnOff(Timer);
		}
		
		static void Setup(TimerType& Timer){
			return ModeImpl<TimerType, Frequency>::Setup(Timer);
		}
	
	};
		
}
}




#endif /* MODE_H_ */