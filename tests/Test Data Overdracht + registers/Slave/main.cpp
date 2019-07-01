//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "l3g4200.hpp"
#include "slave.hpp"
using namespace hwlib;


    
int main(){
   
   auto scl = hwlib::target::pin_oc( hwlib::target::pins::d2 );
   auto sda     = hwlib::target::pin_oc( hwlib::target::pins::d3);
   auto bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto reset_button = target::pin_in( target::pins::d8);

   l3g4200 gyro(bus);
   slave spi(gyro);

   gyro.wake();
   gyro.set_scale(500);

   //for callibration
   bool callibrate = true; 
   unsigned int time = 24;
   int old = now_us() * 0.001; 
   int new_time = now_us() * 0.001; 
  

   for(;;){

      if (callibrate == true){
         spi.byte_read();
         old = (now_us() * 0.001);
         gyro.update(time);
         new_time = (now_us() * 0.001);
         time = ((new_time - old));
         callibrate = false;



      }
      else{

         reset_button.refresh();
	      spi.byte_read();
         if(reset_button.read()){
            gyro.reset();
         }
         gyro.update(time);
         spi.print();

      }    
   }
}
