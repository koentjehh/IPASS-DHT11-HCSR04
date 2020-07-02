#include "HCSR04.hpp"

void HCSR04::trig_send() 
{
	trig_pin.write(0);
	trig_pin.flush();
	hwlib::wait_us(2);

    	trig_pin.write(1); 
	trig_pin.flush();
   	hwlib::wait_us(10);
	
   	trig_pin.write(0); 
	trig_pin.flush();
}

void HCSR04::echo_receive() 
{
	int start_time = 0;
	int end_time = 0;
	
	while ( echo_pin.read() == 0 ) {}
	start_time = hwlib::now_us();
	
	while ( echo_pin.read() == 1 ) {}
	end_time = hwlib::now_us();
	
	time_us = end_time - start_time;   
}

int HCSR04::distance_in_cm()
{
	trig_send();
	
	echo_receive();
	
	int distance_cm = time_us / 58;

	// limits of the sensor (CM)
	if (distance_cm < 0 || distance_cm > 400){ 
		return -1;
	}else{
		return distance_cm; 
	}
}
