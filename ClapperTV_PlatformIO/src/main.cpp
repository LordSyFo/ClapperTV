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

#include <TVController/SamsungCtrl.hpp>

extern "C"{
	#include <Hardware/Serial/UART/uart.h>
}

int main(void)
{
	
	// Send dumb string
	using namespace Hardware;
	SendString("ON\r\n");
	
	// 36 kHz
	using PWMType = PWM::Controller<Module::TIMER0,36000>;
	PWMType PWMCtrl;
	
	// TODO: Consider creating PWMCtrl in-class, this could however hinder the user from changing the specific timer module.
	TVController::SamsungController<PWMType> TVRemote(PWMCtrl);
	
    /* Replace with your application code */
    while (1) 
    {
		TVRemote.SendPowerCode();
		_delay_ms(100);
    }
}

