/*
 * ClapperTV.cpp
 *
 * Created: 25/01/2021 11.30.45
 * Author : hejmi
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include <Hardware/PWM/Controller.hpp>
#include <Hardware/Modules.hpp>

#include <TVController/SamsungCtrl.hpp>

#include <Hardware/ADC/Controller.hpp>

#include <Hardware/Timer/StopWatch.hpp>

extern "C"{
	#include <Hardware/Serial/UART/uart.h>
}

int main(void)
{
	sei();  // Enable global interrupts

	using namespace Hardware;

	InitUART(9600, 8, 'N');
	SendString("ON\r\n");
	
	// 36 kHz
	using PWMType = PWM::Controller<Module::TIMER0,36000>;
	PWMType PWMCtrl;
	
	// TODO: Consider creating PWMCtrl in-class, this could however hinder the user from changing the specific timer module.
	TVController::SamsungController<PWMType> TVRemote(PWMCtrl);

	AnalogToDigital::Controller<Module::ADC0_> adcController;

	Timer::StopWatch stopWatch;

    /* Replace with your application code */
    while (1)
    {

		SendString("Count:\r\n");
		stopWatch.Start();
		_delay_ms(1000);
		SendInteger(stopWatch.Stop());
		
		//_delay_ms(100);

		/*uint16_t value = adcController.Read();

		SendString("\r\n");
		SendInteger(value);

		SendString("ADCSRB\r\n");
		SendInteger(ADCSRB);
		SendString("ADCSRA\r\n");
		SendInteger(ADCSRA);
		SendString("ADMUX\r\n");
		SendInteger(ADMUX);
		
		TVRemote.SendPowerCode();
		_delay_ms(100);*/
    }
}