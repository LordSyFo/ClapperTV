/*
 * Prescale.h
 *
 * Created: 27/01/2021 15.07.25
 *  Author: hejmi
 */ 

#ifndef PRESCALE_H_
#define PRESCALE_H_

namespace Hardware {
namespace PWM {
	
template<typename TimerType, uint>
struct PrescaleSetupImpl;

template<typename TimerType>
struct PrescaleSetupImpl<TimerType,1> {
	inline static void Setup(TimerType& Timer){
		Timer.TCCRBReg.ActivateBits(Timer.TCCRBReg.CS0);
		//TCCRB |= (1<<CS00) & ~(1<<CS01) & ~(1<<CS02);
	}
};

template<typename TimerType>
struct PrescaleSetupImpl<TimerType,8> {
	inline static void Setup(TimerType& Timer){
		Timer.TCCRBReg.ActivateBits(Timer.TCCRBReg.CS1);
		//TCCRB |= (1<<CS01) & ~(1<<CS00) & ~(1<<CS02);
	}
};

template<typename TimerType>
struct PrescaleSetupImpl<TimerType,64> {
	inline static void Setup(TimerType& Timer){
		Timer.TCCRBReg.ActivateBits(Timer.TCCRBReg.CS0, Timer.TCCRBReg.CS1);
		//TCCRB |= (1<<CS00) | (1<<CS01) & ~(1<<CS02);
	}
};

template<typename TimerType>
struct PrescaleSetupImpl<TimerType,256> {
	inline static void Setup(TimerType& Timer){
		Timer.TCCRBReg.ActivateBits(Timer.TCCRBReg.CS2);
		//TCCRB |= (1<<CS02) & ~(1<<CS00) & ~(1<<CS01);
	}
};

template<typename TimerType>
struct PrescaleSetupImpl<TimerType,1024> {
	inline static void Setup(TimerType& Timer){
		Timer.TCCRBReg.ActivateBits(Timer.TCCRBReg.CS0, Timer.TCCRBReg.CS2);
		//TCCRB |= (1<<CS02) | (1<<CS00) & ~(1<<CS01);
	}
};

template<typename TimerType,uint Prescale>
struct PrescaleSetup {

	static void Setup(TimerType& Timer){
		static_assert(Prescale==1 || Prescale==8 || Prescale==64 || Prescale==256 || Prescale==1024, "Prescaler has an invalid value.");
		return PrescaleSetupImpl<TimerType,Prescale>::Setup(Timer);
	}
	
};

}
}

#endif /* PRESCALE_H_ */