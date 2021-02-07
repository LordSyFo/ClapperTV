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
namespace Register {
	
/* Register class */
template<uint8_t Address>
struct Register {
	
	inline void Set(uint8_t value){
		_SFR_IO8(Address) = value;
	}
	
	inline uint8_t Get(){
		return _SFR_IO8(Address);
	}
	
	template<typename TFirst, typename... Targs>
	inline void ActivateBits(TFirst first, Targs... args){
		_SFR_IO8(Address) |= (1<<first);
		ActivateBits(args...);
	}
	
	template<typename TFirst>
	inline void ActivateBits(TFirst first){
		_SFR_IO8(Address) |= (1<<first);
	}
	
	template<typename TFirst, typename... Targs>
	inline void DeactivateBits(TFirst first, Targs... args){
		_SFR_IO8(Address) &= ~(1<<first);
		DeactivateBits(args...);
	}
	
	template<typename TFirst>
	inline void DeactivateBits(TFirst first){
		_SFR_IO8(Address) &= ~(1<<first);
	}
	
};

/* Constant registers */
struct TCCRA0 : public Register<0x24> {
	static constexpr uint8_t COMA1 = 7;
	static constexpr uint8_t COMA0 = 6;
	static constexpr uint8_t COMB1 = 5;
	static constexpr uint8_t COMB0 = 4;
	static constexpr uint8_t WGM1	= 1;
	static constexpr uint8_t WGM0	= 0;
};

struct TCCRB0 : public Register<0x25> {
	static constexpr uint8_t FOCA	= 7;
	static constexpr uint8_t FOCB	= 6;
	static constexpr uint8_t WGM2	= 3;
	static constexpr uint8_t CS2	= 2;
	static constexpr uint8_t CS1	= 1;
	static constexpr uint8_t CS0	= 0;
};

struct OCRA0 : public Register<0x27> {};

}

}

#endif /* REGISTER_H_ */