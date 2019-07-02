//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)




#ifndef LED_MATRIX_HPP
#define LED_MATRIX_HPP
/// @file
#include "hwlib.hpp"  

/// \brief 
/// Interface for the MH7219 led matrix chip
/// \details
/// Interface for one MH7219 led matrix chip to turn selected pixels on and off using a function. This class is designed to be used with the MH7219 Led Matrix
class led_matrix : public hwlib::window{

private:


    uint8_t display_buffer[8] = {0,0,0,0,0,0,0,0};
    hwlib::spi_bus_bit_banged_sclk_mosi_miso & spi;
    hwlib::target::pin_out & cs;

    /// \brief 
    /// Writes pixel to the display buffer
    /// \details
    /// This function a writes pixel to the display buffer
    void write_implementation(hwlib::xy pos, hwlib::color col) override{
        bool write;
        if(col == hwlib::black){
            write = false;
        }
        else{
            write = true;
        }
        display_buffer[pos.y] ^= (-write^ display_buffer[pos.y]) & (1UL << pos.x);
    }


public:

/// \brief 
/// Constructor of MH7219 interface.
/// \details
/// This is the constructor of the MH7219 interface. 
    led_matrix(hwlib::spi_bus_bit_banged_sclk_mosi_miso & spi, hwlib::target::pin_out & cs ):
    window(hwlib::xy{8,8}),
    spi(spi),
    cs(cs)
    {}

/// \brief
/// Wakes up the Led Matrix.
/// \details
/// \ Wakes up the MH7219 Led Matrix Chip by sending data to different registers.
    void wake(){
        uint8_t data1[] = {0x0B, 0x07};
        uint8_t data2[] = {0x09, 0x00};
        uint8_t data3[] = {0x0C, 0x01};
        uint8_t data4[] = {0x0F, 0x00};
        uint8_t data5[] = {0x0A, 0x0F};
        
        
        spi.transaction(cs).write(2, data1);
        hwlib::wait_ms(3);
        spi.transaction(cs).write(2, data2);
        hwlib::wait_ms(3);
        spi.transaction(cs).write(2, data3);
        hwlib::wait_ms(3);
        spi.transaction(cs).write(2, data4);
        hwlib::wait_ms(3);
        spi.transaction(cs).write(2, data5);
        clear();
    }
/// \brief 
/// Tugs in the Led Matrix.
/// \details
/// Sends a sleep bit to the Sleep Register for the MH7219 Led Matrix to turn it .

    void sleep(){
        uint8_t data[2] = {0xC, 0x0};
        spi.transaction(cs).write(2, data);

    }


/// \brief
/// \Writes the buffer to the Led Matrix.
/// \details
/// \this function writes the screen buffer array to the Led Matrix
    void flush() override{
        for(int i = 1; i < 9; i++){
            uint8_t data[2] = {uint8_t(i), display_buffer[i-1]};
            spi.transaction(cs).write(2, data);
        }
    }

/// \brief
/// \Writes givin buffer to the Led Matrix
/// \details
/// \This function is for writing a givin screen buffer to the Led Matrix
    void flush_buffer(uint8_t buffer[8]){
        for(int i = 1; i < 9; i++){
            uint8_t data[2] = {uint8_t(i), buffer[i-1]};
            spi.transaction(cs).write(2, data);
        }
    }

/// \brief
/// \Clears buffer
/// \details
/// \This function clears the current screen buffer   
    void clear_buffer(){
        for(int i = 0; i < 8; i++){
        display_buffer[i] = 0;
        }
    }

/// \brief
/// \Clears Led Matrix Screen
/// \details
/// \This function clears the current displayed pixels on the Led Matrix
    void clear(){
        uint8_t clear[8] = {0,0,0,0,0,0,0,0};
        for(int i = 1; i < 9; i++){
            uint8_t data[2] = {uint8_t(i), clear[i-1]};
            spi.transaction(cs).write(2, data);
        }  
    }

/// \brief
/// \Displays a number on Led Matrix
/// \details
/// \This Function displays a givin number on the Led Matrix
    void number(int number){
        
        uint8_t zero[] = { 0x3E, 0x7F, 0x71, 0x59, 0x4D, 0x7F, 0x3E, 0x00 }; // '0'
        uint8_t one[] = { 0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00, 0x00 }; // '1'
        uint8_t two[] = { 0x62, 0x73, 0x59, 0x49, 0x6F, 0x66, 0x00, 0x00 }; // '2'
        uint8_t three[] = { 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 }; // '3'
        uint8_t four[] = { 0x18, 0x1C, 0x16, 0x53, 0x7F, 0x7F, 0x50, 0x00 }; // '4'
        uint8_t five[] = { 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00, 0x00 }; // '5'
        uint8_t six[] = { 0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00, 0x00 }; // '6'
        uint8_t seven[] = { 0x03, 0x03, 0x71, 0x79, 0x0F, 0x07, 0x00, 0x00 }; // '7'
        uint8_t eight[] = { 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 }; // '8'
        uint8_t nine[] = { 0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00, 0x00 }; // '9'
        if(number == 0){
            flush_buffer(zero);
        }
        if(number == 1){
            flush_buffer(one);
        }
        if(number == 2){
            flush_buffer(two);
        }
        if(number == 3){
            flush_buffer(three);
        }
        if(number == 4){
            flush_buffer(four);
        }
        if(number == 5){
            flush_buffer(five);
        }
        if(number == 6){
            flush_buffer(six);
        }
        if(number == 7){
            flush_buffer(seven);
        }
        if(number == 8){
            flush_buffer(eight);
        }
        if(number == 9){
            flush_buffer(nine);
        }

    }
};
  
  
#endif   
  
  
