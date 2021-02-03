/*
 * Config.h
 *
 * Created: 29/01/2021 09.37.53
 *  Author: hejmi
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

#ifdef USE_TIMER_0
	#define TCCRA TCCR0A
	#define TCCRB TCCR0B
	#define PWM_PIN_B 5
	#define PWM_PORT_B PORTG
	#define PWM_PIN_A 7
	#define PWM_PORT_A PORTB
	
	#define DIRECTION_PORT DDRB
	
#endif

#ifdef USE_TIMER_1
	#define TCCRA TCCR1A
	#define TCCRB TCCR1B
#endif

#ifdef USE_TIMER_2
	#define TCCRA TCCR2A
	#define TCCRB TCCR2B
#endif


#endif /* CONFIG_H_ */