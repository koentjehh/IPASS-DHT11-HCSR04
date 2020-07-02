#include "DHT11.hpp"

int main( void )
{
	auto data_pin = hwlib::target::pin_in_out( hwlib::target::pins::d7 );

	auto DHT11_sensor = DHT11(data_pin);
	
	hwlib::wait_ms(1000); // 1 second wait to enter stable state
	
	while(true){
		
		DHT11_sensor.start_and_read();
		
		int temperature = DHT11_sensor.temperature();
		int humidity 	= DHT11_sensor.humidity();
		
		hwlib::cout << "T: " << temperature << "*C\n"
					<< "H: " << humidity	<< "%\n";
		
		hwlib::wait_ms(5000); // to get accurate results check every 5 seconds max.
	}
}
