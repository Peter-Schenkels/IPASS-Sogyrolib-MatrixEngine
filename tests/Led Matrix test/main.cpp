#include "hwlib.hpp"  
#include "matrix_engine.hpp"  

int main(void){

	
	auto din = hwlib::target::pin_out( hwlib::target::pins::d52 );
	auto cs1   = hwlib::target::pin_out( hwlib::target::pins::d49 );
	auto clk = hwlib::target::pin_out( hwlib::target::pins::d51 );
	auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( 
	clk, din, hwlib::pin_in_dummy 
	);

	led_matrix matrix(spi, cs1);
	matrix.wake();

	for(;;){
		
		uint8_t display_buffer[8] = {0,0,0,0,0,0,0,0};

		for(unsigned int i = 0; i < 8; i++){
			
			for(unsigned int j = 0; j < 8; j++){
			display_buffer[i] =	display_buffer[i] | (1 << j);
			matrix.flush_buffer(display_buffer);
			hwlib::wait_ms(50);
			}

		}

	}
	
}
