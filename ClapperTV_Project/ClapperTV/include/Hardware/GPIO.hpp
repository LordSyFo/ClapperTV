/*
 * GPIO.h
 *
 * Created: 07/02/2021 17.10.54
 *  Author: hejmi
 */ 


#ifndef GPIO_H_
#define GPIO_H_

namespace Hardware {
namespace GPIO {
	
//TODO: Maybe make lookup table for Direction addresses!
/* GPIO Class */
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

/* Constant GPIO's */
struct OC1A : public GPIO<0x14, 0x13, 5> {};
struct OC0A : public GPIO<0x05, 0x04, 7> {};

}
}



#endif /* GPIO_H_ */