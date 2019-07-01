//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)s


#ifndef I2C_FAST_HPP
#define I2C_FAST_HPP
/// @file
#include "hwlib.hpp"

/// \brief
/// hwlib::i2c_bus_bit_banged_scl_sda Decorator
/// \details
/// This class is hwlib::i2c_bus_bit_banged_scl_sda Decorator used to write shorter lines of codes to write and read bytes with a givin address.
class i2c_fast : hwlib::i2c_bus_bit_banged_scl_sda {

    uint8_t & address;

public:

/// \brief
/// Constructor of hwlib::i2c_bus_bit_banged_scl_sda Decorator 
/// \details
/// This is the constructor of the hwlib::i2c_bus_bit_banged_scl_sda Decorator, this constructor initialises the i2c_bus and givin address.
    i2c_fast(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t & address): 
    i2c_bus_bit_banged_scl_sda(bus),
    address(address){}

/// \brief
/// Writes data from givin byte to read data into givin byte
/// \details
/// This function writes data from givin byte to read data into givin byte
    uint8_t read(uint8_t & data){

        i2c_bus::write(address).write(data);
        i2c_bus::read(address).read(data);

        return data;

    }

/// \brief
/// Writes data from register byte byte to read data into givin storage byte.
/// \details
/// This function writes data from register address byte to read data into givin storage byte.
    uint8_t read(uint8_t & register_address, uint8_t & storage){

        i2c_bus::write(address).write(register_address);
        i2c_bus::read(address).read(storage);
        
        return storage;
    }
    
};


#endif //I2C_FAST_HPP
