//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "l3g4200.hpp"
/// @file
#ifndef SLAVE
#define SLAVE


/// \brief
/// Class to create a SPI slave for Arduino 
/// \details
/// This class is used to make a SPI bus slave to connect multiple Arduino's with each other.
class slave{

private:
	
    hwlib::target::pin_in clk = hwlib::target::pin_in(hwlib::target::pins::d4);
    hwlib::target::pin_in mosi = hwlib::target::pin_in(hwlib::target::pins::d5);
    hwlib::target::pin_out miso = hwlib::target::pin_out(hwlib::target::pins::d6);
    hwlib::target::pin_in cs = hwlib::target::pin_in(hwlib::target::pins::d7);
    l3g4200 & gyro;

public:

    slave(l3g4200 & gyro):
    gyro(gyro){};

    uint_fast8_t data_in = 0x0;
    uint_fast8_t data_out = 0x68;
    int position = 0;      

/// \brief
/// Sends byte to master
/// \details
/// This function writes a byte to the master Arduino
    void byte_send(){

        position = 7;
        
        if (!(cs.read())){


            while(position >= 0 && !(cs.read())){
              
                clk.refresh();
                if(!(clk.read())){

                    miso.write((data_out >> position) & 0x1);
                    miso.flush();
                    position--;
                    
                    while(!(clk.read())){
                        clk.refresh(); 
                    }

                }

            }

        }

    }


/// \brief
/// Reads byte from master
/// \details
/// This function reads the incomming byte from the master Arduino.
    void byte_read(){

        position = 0;
        cs.refresh();
        if(cs.read() && !(clk.read())){

            while(position != 8){
                
                clk.refresh();
                if(!(clk.read())){

                    if(mosi.read()){
                        data_in |= 1;
                    }
                    else{
                        data_in |= 0;
                    }
                    data_in = data_in << 1;
                    position++;
                    
                    while(!(clk.read())){
                        clk.refresh();
                    }
                    
                }  
            }
            data_in *= 0.5;
            check();
            byte_send();
        }
    }
/// \brief
/// Prints incomming byte
/// \details
/// This function prints the incomming byte buffer
    void print(){
        hwlib::cout << data_in << '\n';
    }

/// \brief
/// Checks incomming byte to execute gyroscope function
/// \details
/// This function checks the incomming byte and determines wich function of the gyroscope library it schould execute.
    void check(){

        //all gyro values

        if (data_in == 6){data_out = (gyro.get_x_gyro_h());}

        else if (data_in == 4){data_out = gyro.get_x_gyro_l();}
  
        else if (data_in == 8){data_out = gyro.get_y_gyro_h();}

        else if (data_in == 10){data_out = gyro.get_y_gyro_l();}

        else if (data_in == 12){data_out = gyro.get_z_gyro_h();}
  
        else if (data_in == 14){data_out = gyro.get_z_gyro_l();}

        //all dps values

        else if (data_in == 16){data_out = gyro.get_dps_x_h();}

        else if (data_in == 18){data_out = gyro.get_dps_x_l();}

        else if (data_in == 22){data_out = gyro.get_dps_y_h();}

        else if (data_in == 24){data_out = gyro.get_dps_y_l();}

        else if (data_in == 26){data_out = gyro.get_dps_z_h();}

        else if (data_in == 28){data_out = gyro.get_dps_z_l();}

        else if (data_in == 30){gyro.reset();}

        else if (data_in == 36){data_out = gyro.get_temperature();}

        else if (data_in == 40){gyro.set_scale(250);}

        else if (data_in == 42){gyro.set_scale(500);}

        else if (data_in == 44){gyro.set_scale(2000);}

        else if (data_in == 50){gyro.wake();}

        else if (data_in == 52){gyro.sleep();}

    }

};


#endif
