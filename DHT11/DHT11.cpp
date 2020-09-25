#include "DHT11.hpp"

void DHT11::start_and_read()
{
	int bit_counter = 0;
	
	data_pin.direction_set_output();
	data_pin.direction_flush();
	
	data_pin.write(0);
	data_pin.flush();
	hwlib::wait_ms(18);
	
	data_pin.write(1);
	data_pin.flush();
	
	data_pin.direction_set_input();
	data_pin.direction_flush();
	
	hwlib::wait_us(40); 
		
	while( data_pin.read() == 0 ) {};
	while( data_pin.read() == 1 ) {};
	while( data_pin.read() == 0 ) {};

	for( int byte_index = 0; byte_index < 5; byte_index++ )
	{
		for( int byte= 0; byte < 7; byte++ ) 
		{
			hwlib::wait_us(50); 
			
			if( data_pin.read() == 0 )
			{
				bit_counter <<= 1;
			}
			else
			{
				bit_counter ++;
				bit_counter <<= 1;
				while( data_pin.read() == 1 ) {};
			}
			
			while( data_pin.read() == 0 ) {};
		}
		
		hwlib::wait_us(50);
		
		if( data_pin.read() == 1 )
		{
			bit_counter += 1;
			while( data_pin.read() == 1 ) {};
		}
		while( data_pin.read() == 0 ) {};
		
		bits[byte_index] = bit_counter;
	}
		
}

int DHT11::humidity()
{	
	int humidity_percent = bits[0];
	
	return humidity_percent;
}

int DHT11::temperature()
{
	int temperature_celsius = bits[2];
	
	return temperature_celsius;
}
