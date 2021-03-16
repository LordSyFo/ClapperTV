/*
 * Controller.h
 *
 * Created: 10/02/2021 17.12.48
 *  Author: hejmi
 */ 


#ifndef ADCSelector_H_
#define ADCSelector_H_

#include <stdint.h>

namespace Hardware{
namespace AnalogToDigital{

    template<uint8_t Identifier>
    struct ADCSelector;

    template<uint8_t Identifier>
    struct ADCSelector {
        static_assert(Identifier < 8, "Invalid ADC number!");
        static constexpr uint8_t value = Identifier;
    };

    template<>
    struct ADCSelector<8>
    {
        static constexpr uint8_t value = 0b100000;
    };
    
    template<>
    struct ADCSelector<9>
    {
        static constexpr uint8_t value = 0b100001;
    };
    
    template<>
    struct ADCSelector<10>
    {
        static constexpr uint8_t value = 0b100010;
    };

    template<>
    struct ADCSelector<11>
    {
        static constexpr uint8_t value = 0b100011;
    };

    template<>
    struct ADCSelector<12>
    {
        static constexpr uint8_t value = 0b100100;
    };

    template<>
    struct ADCSelector<13>
    {
        static constexpr uint8_t value = 0b100101;
    };

    template<>
    struct ADCSelector<14>
    {
        static constexpr uint8_t value = 0b100110;
    };

    template<>
    struct ADCSelector<15>
    {
        static constexpr uint8_t value = 0b100111;
    };

}
}
#endif /* ADCSelector_H_ */