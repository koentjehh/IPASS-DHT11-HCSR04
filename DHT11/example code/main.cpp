#include "DHT11.hpp"

int main( void )
{
	auto data_pin = hwlib::target::pin_in_out( hwlib::target::pins::d7 );

	auto DHT11_sensor = DHT11( data_pin );
	
	hwlib::wait_ms( 1000 ); // a one-second wait to reach stable state
	
	while(true){
		
		DHT11_sensor.start_and_read(); // the sensor is started and the data will be collected
		
		int temperature = DHT11_sensor.temperature(); // obtain the collected temperature data (in degrees Celsius)
		int humidity 	= DHT11_sensor.humidity();    // obtain the collected humidity data
		
		hwlib::cout << "Temperature: " << temperature << "*C\n"
			    << "humidity   : " << humidity    << "%\n";
		
		hwlib::wait_ms( 5000 ); // a sensor interval of no less than 5 seconds is required to obtain accurate data
	}
}
