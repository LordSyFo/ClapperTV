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

//TODO: Maybe make lookup table for Direction addresses!
template<uint8_t Address, uint8_t DirectionAddress, uint8_t BitField>
struct GPIO {
	inline void SetDirection(bool Output)
	{
		if (Output)
			_SFR_IO8(DirectionAddress) |= (1<<BitField);
		else
			_SFR_IO8(DirectionAddress) &= ~(1<<BitField);
	}
	
	inline void Activate(){
		_SFR_IO8(Address) |= (1<<BitField);
	}
	
	inline void Deactivate(){
		_SFR_IO8(Address) &= ~(1<<BitField);
	}
	
	inline uint8_t Get(){
		return (_SFR_IO8(Address) >> BitField) & 1;
	}
};

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

// TODO: Implement this idea
struct RegisterTCCRA0 : public Register<0x24> {
	static constexpr uint8_t COMA1 = 7;
	static constexpr uint8_t COMA0 = 6;
	static constexpr uint8_t COMB1 = 5;
	static constexpr uint8_t COMB0 = 4;
	static constexpr uint8_t WGM1	= 1;
	static constexpr uint8_t WGM0	= 0;
};

struct RegisterTCCRB0 : public Register<0x25> {
	static constexpr uint8_t FOCA	= 7;
	static constexpr uint8_t FOCB	= 6;
	static constexpr uint8_t WGM2	= 3;
	static constexpr uint8_t CS2	= 2;
	static constexpr uint8_t CS1	= 1;
	static constexpr uint8_t CS0	= 0;
};

struct OC1AGPIO : public GPIO<0x14, 0x13, 5> {};
struct OC0AGPIO : public GPIO<0x05, 0x04, 7> {};

struct RegisterOCR0A : public Register<0x27> {

};

struct TIMER0 {
	constexpr TIMER0() {
		
	}
	
	RegisterTCCRA0	TCCRAReg;
	RegisterTCCRB0	TCCRBReg;
	RegisterOCR0A	OCRAReg;
	OC0AGPIO		Output0;
	OC1AGPIO		Output1;
	
};

}

#endif /* REGISTER_H_ */