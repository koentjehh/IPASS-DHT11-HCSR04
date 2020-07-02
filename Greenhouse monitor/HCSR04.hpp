#ifndef HCSR04_HPP
#define HCSR04_HPP

#include "hwlib.hpp"

class HCSR04 {
private:
    hwlib::pin_out & trig_pin;
    hwlib::pin_in & echo_pin;
	
    int time_us;

public:
    HCSR04(hwlib::pin_out & trig_pin, hwlib::pin_in & echo_pin):
		trig_pin(trig_pin), echo_pin(echo_pin)
	{}
	
	void trig_send();
	
	void echo_receive();
	
	int distance_in_cm();
};

#endif 