//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)




#include "hwlib.hpp"
#include "l3g4_master.hpp"

using namespace hwlib;

int main() {

	auto clk  = hwlib::target::pin_out( hwlib::target::pins::d44); 
	auto mosi  = hwlib::target::pin_out( hwlib::target::pins::d45); 
	auto miso  = hwlib::target::pin_in( hwlib::target::pins::d46); 
	auto cs  = hwlib::target::pin_out( hwlib::target::pins::d47);
	auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, mosi, miso, 100);
	sogyro gyro(spi, cs);
	hwlib::wait_ms(100);


	gyro.sleep();
	hwlib::wait_ms(100);

	//Hoort niet de huidige waardes door te geven
	hwlib::cout << gyro.get_gyro_x();
	hwlib::wait_ms(100);
	
	gyro.wake();
	hwlib::wait_ms(100);

	for (unsigned int i = 0; i < 3; i++){

		int num = 250 * (1 << i);
		gyro.set_scale(num);
		hwlib::wait_ms(100);
		hwlib::cout << gyro.get_gyro_x() << "\n";	
		hwlib::wait_ms(100);
		hwlib::cout << gyro.get_gyro_y() << "\n";
		hwlib::wait_ms(100);	
		hwlib::cout << gyro.get_gyro_z() << "\n";
		hwlib::wait_ms(100);	
		hwlib::cout << gyro.get_dps_x() << "\n";	
		hwlib::wait_ms(100);
		hwlib::cout << gyro.get_dps_y() << "\n";
		hwlib::wait_ms(100);
		hwlib::cout << gyro.get_dps_z() << "\n";
		hwlib::wait_ms(100);
		hwlib::cout << gyro.get_temp() << "\n";
		hwlib::wait_ms(100);
		gyro.reset();
	}

}
    



