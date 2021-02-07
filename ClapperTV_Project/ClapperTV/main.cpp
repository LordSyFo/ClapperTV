/*
 * ClapperTV.cpp
 *
 * Created: 25/01/2021 11.30.45
 * Author : hejmi
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include <Hardware/PWM/Controller.hpp>
#include <Hardware/Modules.hpp>

extern "C"{
	#include <Hardware/uart.h>
}

int main(void)
{
	
	using namespace Hardware;
	SendString("ON\r\n");
	
	// 36 kHz
	PWM::Controller<Module::TIMER0,36000> PWMCtrl;

	
    /* Replace with your application code */
    while (1) 
    {
		PWMCtrl.TurnOn();
		_delay_ms(1000);
		PWMCtrl.TurnOff();
		_delay_ms(1000);
    }
}

