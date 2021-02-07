/*
 * SamsungCtrl.h
 *
 * Created: 07/02/2021 17.24.43
 *  Author: hejmi
 */ 


#ifndef SAMSUNGCTRL_H_
#define SAMSUNGCTRL_H_

namespace TVController {

// Used for start condition
static constexpr double kStartOnTime = 4500;	// us
static constexpr double kStartOffTime = 4500;	// us
	
// Used for transmitting bit "1"
static constexpr double kHighOnTime		= 590;	// us
static constexpr double kHighOffTime	= 1690;	// us
	
// Used for transmitting bit "0"
static constexpr double kLowOnTime		= 590;	// us
static constexpr double kLowOffTime		= 590;	// us
	
// Used for stop condition
static constexpr double kStopOnTime		= 590;	// us
static constexpr double kStopOffTime	= 590;	// us

/* Single bit transmitter */
template<typename TransmissionPolicy, uint8_t Bit>
struct BitTransmitter;

template<typename TransmissionPolicy>
struct BitTransmitter<TransmissionPolicy, 0> {
	inline static void Send(TransmissionPolicy& transmission){ transmission.TurnOn(); _delay_us(kLowOnTime); transmission.TurnOff(); _delay_us(kLowOffTime); }
};

template<typename TransmissionPolicy>
struct BitTransmitter<TransmissionPolicy, 1> {
	inline static void Send(TransmissionPolicy& transmission){ transmission.TurnOn(); _delay_us(kHighOnTime); transmission.TurnOff(); _delay_us(kHighOffTime); }
};

/* Full transmitter */
template<typename TransmissionPolicy, typename T, const T Bits, int BitIteration>
struct TransmitterImpl;

template<typename TransmissionPolicy, typename T, const T Bits, int BitIteration>	// Normal condition
struct TransmitterImpl {
	static void Send(TransmissionPolicy& transmission) {
		BitTransmitter<TransmissionPolicy, Bits & 0x01>::Send(transmission);
		TransmitterImpl<TransmissionPolicy, T, (Bits >> 1), BitIteration - 1>::Send(transmission);
	}
};

template<typename TransmissionPolicy, typename T, const T Bits>						// End condition
struct TransmitterImpl <TransmissionPolicy, T, Bits, 1> {
	static void Send(TransmissionPolicy& transmission) {
		BitTransmitter<TransmissionPolicy, Bits & 0x01>::Send(transmission);
	}
};

template<typename TransmissionPolicy, typename T, const T Bits>
struct Transmitter {
	
	static void SendMessage(TransmissionPolicy& transmission){
		
		transmission.TurnOn(); _delay_us(kStartOnTime); transmission.TurnOff(); _delay_us(kStartOffTime);	// Start condition
		TransmitterImpl<TransmissionPolicy, T, Bits, sizeof(T) * 8>::Send(transmission);					// Message
		transmission.TurnOn(); _delay_us(kStopOnTime); transmission.TurnOff(); _delay_us(kStopOffTime);		// End condition
		
	}
	
};

template<typename PWMCtrlType>
class SamsungController {
public:
	SamsungController(PWMCtrlType& PWMCtrl) : PWMCtrl_(PWMCtrl) {
		PWMCtrl_.TurnOff();		// The signal should be turned off unless we need to transmit data. 
	}
	
	constexpr void SendPowerCode(){
		Transmitter<PWMCtrlType, uint32_t, kPowerCode>::SendMessage(PWMCtrl_);
	}
		
private:
	PWMCtrlType PWMCtrl_;
	
	// Remote IR codes
	static constexpr uint32_t kPowerCode = 0b11111101000000100000011100000111;
	
};

	
}



#endif /* SAMSUNGCTRL_H_ */