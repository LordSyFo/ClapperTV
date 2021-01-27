/*
 * PWM.h
 *
 * Created: 25/01/2021 11.31.25
 *  Author: hejmi
 */ 


#ifndef PWM_H_
#define PWM_H_

namespace Hardware {
namespace PWM {
	
using uint = unsigned int;

/* Static PWM class - cannot be changed after frequency is set */
template<typename PrescalerPolicy, typename CounterPolicy, typename ModePolicy>
class PWM {
	public:
	constexpr PWM(){
		
		Setup();
		
	}
	
	inline void Setup() {
		PrescalerPolicy::Set();
		CounterPolicy::Set();
		ModePolicy::Set();
	}
	
};

}
}


#endif /* PWM_H_ */