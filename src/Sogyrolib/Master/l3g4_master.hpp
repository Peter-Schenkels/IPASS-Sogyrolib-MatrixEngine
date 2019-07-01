//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef LG_MASTER_HPP
#define LG_MASTER_HPP

/// @file

#include "hwlib.hpp"



/// \brief
/// Class that interfaces the arduino connected to a gyro scope
/// \details
/// A class that interfaces the Slave Arduino Nano through a spi bus that is dedicated only to the Arduino Nano. The Arduino Nano is connected to a L3G4200 gyroscope.
/// The functions of this class send register adresses to the Arduino Nano and then Arduino Nano returns the correpsonding data.
class sogyro{

private:

    hwlib::spi_bus_bit_banged_sclk_mosi_miso & bus;
    hwlib::target::pin_out & cs;
    int mode = 500;

public:
    /// \brief
    /// Constructs an interface for the Slave Arduino Nano
    /// \details
    /// This constructor creates an interface for the Slave Arduino Nano using a spi bus and a enabler pin.
    sogyro(hwlib::spi_bus_bit_banged_sclk_mosi_miso & bus, hwlib::target::pin_out & cs):
    bus(bus),
    cs(cs)
    {}    

    /// \brief
    /// Constructs an interface for the Slave Arduino Nano
    /// \details
    /// This constructor creates an interface for the Slave Arduino Nano using a spi bus and a enabler pin and also sets the scale for the gyroscope.
    sogyro(hwlib::spi_bus_bit_banged_sclk_mosi_miso & bus, hwlib::target::pin_out & cs, int mode):  
    bus(bus), 
    cs(cs),
    mode(mode)
    {
        set_scale(mode);
    }

    /// \brief
    /// function to read and write data.
    /// \details
    /// A function used to write 1 byte of data to read 1 byte of data.
    int fast_read(uint8_t address){

        uint8_t storage[1];
        uint8_t addr[1] = {address};
       
        hwlib::wait_ms(30);

        // bus.transaction(cs).write_and_read(1, addr, storage);
        bus.transaction(cs).write_and_read(1,  addr, storage);
        
        

        return storage[0];

    }

    /// \brief
    /// function to read and write data.
    /// \details
    /// A function used to write 2 byte of data to read 2 bytes of data. The function merges the to bytes of data and then return them as an uint16_t value.
    int fast_read(uint8_t high, uint8_t low){
         
        uint8_t data_out_h[1];
        uint8_t data_out_l[1];
        uint8_t data_h[1] = {high};
        uint8_t data_l[1] = {low};

        bus.transaction(cs).write_and_read(1, data_h, data_out_h);
        bus.transaction(cs).write_and_read(1,  data_h, data_out_h);
        
        hwlib::wait_ms(30);

        bus.transaction(cs).write_and_read(1, data_l, data_out_l);
        bus.transaction(cs).write_and_read(1,  data_l, data_out_l);
        
  
        return ((data_out_h[0])* 256) + (data_out_l[0]);

    }
    /// \brief
    /// Returns gyro x axis data in degrees.
    /// \details
    /// This function is used to recieve the current gyro x axis from the slave Arduino Nano
    int get_gyro_x(){return fast_read(0x06, 0x04);}

    /// \brief
    /// Returns gyro y axis data in degrees.
    /// \details
    /// This function is used to recieve the current gyro y axis from the slave Arduino Nano
    int get_gyro_y(){return fast_read(0x8, 0x0A);}
    
    /// \brief
    /// Returns gyro z axis data in degrees.
    /// \details
    /// This function is used to recieve the current gyro z axis from the slave Arduino Nano
    int get_gyro_z(){return fast_read(0x0C, 0x0E);}

    /// \brief
    /// Returns gyro x dps data in degrees per second.
    /// \details
    /// This function is used to recieve the current degrees per second x value from the slave Arduino Nano.
    int get_dps_x(){return fast_read(0x10, 0x12);}

    /// \brief
    /// Returns gyro y dps data in degrees per second.
    /// \details
    /// This function is used to recieve the current degrees per second y value from the slave Arduino Nano.
    int get_dps_y(){return fast_read(0x16, 0x18);}

    /// \brief
    /// Returns gyro z dps data in degrees per second.
    /// \details
    /// This function is used to recieve the current degrees per second z value from the slave Arduino Nano.
    int get_dps_z(){return fast_read(0x1A, 0x1C);}

    /// \brief
    /// Returns temprature data in degrees.
    /// \details
    /// This function is used to recieve the current temprature from the slave Arduino Nano.
    int get_temp(){return fast_read(36);}

    /// \brief 
    /// Changes the scale of the gyroscope
    /// \Details
    /// This function is used to change the gyroscope scale to either 250, 500 or 2000. 
    int set_scale(int scale){

        if (scale == 250){ return fast_read(40);}

        else if(scale == 500){ return fast_read(42);}

        else if(scale == 2000){ return fast_read(44);}

    }
  
    /// \brief 
    /// Wakes up the gyroscope
    /// \Details
    /// This function is used to wakes up the gyroscope from sleep mode.
    int wake(){
       return fast_read(50);
    }

    /// \brief 
    /// Tugs in the gyroscope
    /// \Details
    /// This function is used to to set the gyroscope to sleep mode.
    int sleep(){
        return fast_read(52);
    }

    void reset(){
        fast_read(30);
    }

};


#endif
