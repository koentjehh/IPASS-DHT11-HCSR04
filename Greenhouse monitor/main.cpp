#include "HCSR04.hpp"
#include "DHT11.hpp"

namespace target = hwlib::target;

bool is_window_open( int window_distance_cm, int measured_distance )
{
	if( measured_distance > 0 && measured_distance < window_distance_cm )
	{
		return 0; // window closed
	}
	else
	{
		return 1; // window open
	}
}

void oled( int temp, int hum, bool w_status, int distance )
{
	hwlib::wait_ms( 500 );   
   
	auto scl     = target::pin_oc( target::pins::scl );
	auto sda     = target::pin_oc( target::pins::sda );
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
	auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 
   
	auto font    = hwlib::font_default_16x16();
	auto display = hwlib::terminal_from( oled, font );
   
	for(;;)
	{
		display 
			<< "greenhouse\n\n"
			<< "\f" << "T: " << temp << "*C"
			<< "\n" << "H: " << hum  << "%" 
			<< "\n" << "W: " << w_status
			<< "\n" << "D:"  << distance << "CM" 
			<< hwlib::flush; 
			break;
	}         

}

int main()
{	
	hwlib::wait_ms( 1000 ); // 1 second wait to enter stable state (DHT11)
	
	auto trig_pin = target::pin_out( target::pins::d8 );
        auto echo_pin = target::pin_in ( target::pins::d9 );
	auto data_pin = target::pin_in_out( target::pins::d7 );

	DHT11 DHT11_sensor( data_pin );
	
	HCSR04 HCSR04_sensor( trig_pin, echo_pin );
	
	int distance;

	while( true )
	{
		DHT11_sensor.start_and_read();
		
		int temp  = DHT11_sensor.temperature();
		int humid = DHT11_sensor.humidity();
		
		distance = HCSR04_sensor.distance_in_cm();
		
		bool window_status = is_window_open( 10, distance );
		
		// demo view for terminal:
		hwlib::cout << " =========================\n"
					<< "  | Temperature: " << temp  << "*C\t|\n"
					<< "  | Humidity   : " << humid << "% \t|\n"
					<< "  | Window open: " << window_status << "\t|\n"  
					<< "  | Distance   : " << distance << "CM\t|\n"
					<< " =========================\n\n";
		
		oled( temp, humid, window_status, distance );

		hwlib::wait_ms( 5000 ); // 5 second wait for DHT11 to get accurate measures
	}
}
