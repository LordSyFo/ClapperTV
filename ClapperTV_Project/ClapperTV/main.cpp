/*
 * ClapperTV.cpp
 *
 * Created: 25/01/2021 11.30.45
 * Author : hejmi
 */ 

#include <avr/io.h>
#include <Hardware/PWM.hpp>
#include <Hardware/RegisterOperations/Mode.hpp>
#include <Hardware/RegisterOperations/Prescale.hpp>

int main(void)
{
	
	{
		using namespace Hardware::PWM;
		
		// 36 kHz
		Controller<Mode<PhaseCorrectMode, 36000>,PrescaleSetup<1>> PWMCtrl;	
		
	}
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

