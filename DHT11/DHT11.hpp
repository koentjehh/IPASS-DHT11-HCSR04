#ifndef DHT11_HPP
#define DHT11_HPP

#include "hwlib.hpp"

class DHT11{
private:
	hwlib::pin_in_out & data_pin;
	
	uint8_t bits[5] = {0}; 
	
public:
	DHT11(hwlib::pin_in_out & data_pin):
		data_pin(data_pin)
	{}

	void start_and_read();
	
	int humidity();
	
	int temperature();
};

#endif