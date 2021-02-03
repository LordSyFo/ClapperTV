/*
 * Register.h
 *
 * Created: 03/02/2021 13.50.31
 *  Author: hejmi
 */ 


#ifndef REGISTER_H_
#define REGISTER_H_

#include <avr/io.h>

namespace Hardware {

struct Register {
	uint8_t Address;
	
	inline void Set(uint8_t value){
		_SFR_IO8(Address) = value;
	}
	
	inline uint8_t Get(){
		return _SFR_IO8(Address);
	}
};

struct TIMER0 {
	constexpr TIMER0 : TCCRAReg{0x24}, TCCRBReg{0x25}{
		
	}
	
	volatile Register TCCRAReg;
	volatile Register TCCRBReg;
};

}

#endif /* REGISTER_H_ */