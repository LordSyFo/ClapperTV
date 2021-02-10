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
	
	static_assert((Address > 0), "Memory address is a negative number.");
	
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

/* For absolute addresses we need to subtract __SFR_OFFSET this is the case of the macros: _SFR_MEM8 */
// TODO: Check that this approach actually works, otherwise we need to make a distinction between SFR_IO8 and SFR_MEM!
struct ADMUX_ : public Register<0x7C - __SFR_OFFSET> {
	static constexpr uint8_t REFS1_	= 7;
	static constexpr uint8_t REFS0_	= 6;
	static constexpr uint8_t ADLAR_	= 5;
	static constexpr uint8_t MUX4_	= 4;
	static constexpr uint8_t MUX3_	= 3;
	static constexpr uint8_t MUX2_	= 2;
	static constexpr uint8_t MUX1_	= 1;
	static constexpr uint8_t MUX0_	= 0;
};

struct ADCSRB_ : public Register<0x7B - __SFR_OFFSET> {
	static constexpr uint8_t ACME_	= 6;
	static constexpr uint8_t MUX5_	= 3;
	static constexpr uint8_t ADTS2_	= 2;
	static constexpr uint8_t ADTS1_	= 1;
	static constexpr uint8_t ADTS0_	= 0;
};

struct ADCSRA_ : public Register<0x7A - __SFR_OFFSET> {
	static constexpr uint8_t ADEN_	= 7;
	static constexpr uint8_t ADSC_	= 6;
	static constexpr uint8_t ADATE_	= 5;
	static constexpr uint8_t ADIF_	= 4;
	static constexpr uint8_t ADIE_	= 3;
	static constexpr uint8_t ADPS2_	= 2;
	static constexpr uint8_t ADPS1_	= 1;
	static constexpr uint8_t ADPS0_	= 0;
};

struct ADCH_ : public Register<0x79 - __SFR_OFFSET>{};
struct ADCL_ : public Register<0x78 - __SFR_OFFSET>{};



}
}

#endif /* REGISTER_H_ */