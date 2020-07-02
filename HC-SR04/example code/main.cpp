#include "HCSR04.hpp"

namespace target = hwlib::target;

int main()
{	
	auto trig_pin = target::pin_out( target::pins::d8 );
        auto echo_pin = target::pin_in ( target::pins::d9 );
	
	HCSR04 HCSR04_sensor( trig, echo );
	
	int distance;

	while(true){
		
		distance = HCSR04_sensor.distance_in_cm();

		hwlib::cout << "Distance: " << distance << "CM\n";
		
		hwlib::wait_ms(600);	
	}
}
