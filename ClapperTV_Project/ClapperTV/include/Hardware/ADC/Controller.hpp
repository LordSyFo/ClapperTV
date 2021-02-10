/*
 * Controller.h
 *
 * Created: 10/02/2021 17.12.48
 *  Author: hejmi
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace Hardware{
namespace AnalogToDigital{

class Controller {

public:
	constexpr Controller(){
		
	}

	//TODO: When reading from the ADC, you should read from ADCL first to stop the conversion before reading the ADCH
	//TODO: You should clear ADEN bit in ADMUX when going into powersave mode!


}
	
	
}
}



#endif /* CONTROLLER_H_ */