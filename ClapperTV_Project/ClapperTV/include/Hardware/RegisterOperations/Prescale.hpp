/*
 * Prescale.h
 *
 * Created: 27/01/2021 15.07.25
 *  Author: hejmi
 */ 

#ifndef PRESCALE_H_
#define PRESCALE_H_

#include "Config.hpp"

namespace Hardware {
namespace PWM {

template<uint>
struct PrescaleSetupImpl;

template<>
struct PrescaleSetupImpl<1> {
	inline static void Set(){
		TCCRB |= (1<<CS00) & ~(1<<CS01) & ~(1<<CS02);
	}
};

template<>
struct PrescaleSetupImpl<8> {
	inline static void Set(){
		TCCRB |= (1<<CS01) & ~(1<<CS00) & ~(1<<CS02);
	}
};

template<>
struct PrescaleSetupImpl<64> {
	inline static void Set(){
		TCCRB |= (1<<CS00) | (1<<CS01) & ~(1<<CS02);
	}
};

template<>
struct PrescaleSetupImpl<256> {
	inline static void Set(){
		TCCRB |= (1<<CS02) & ~(1<<CS00) & ~(1<<CS01);
	}
};

template<>
struct PrescaleSetupImpl<1024> {
	inline static void Set(){
		TCCRB |= (1<<CS02) | (1<<CS00) & ~(1<<CS01);
	}
};

template<uint Prescale>
struct PrescaleSetup {

	static void Set(){
		static_assert(Prescale==1 || Prescale==8 || Prescale==64 || Prescale==256 || Prescale==1024, "Prescaler has an invalid value.");
		return PrescaleSetupImpl<Prescale>::Set();
	}
	
};

}
}

#endif /* PRESCALE_H_ */