//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef L3G4200_HPP
#define L3G4200_HPP
/// @file
#include "hwlib.hpp"
#include "i2c_fast.hpp"


/// \brief
/// turns data into 360 degrees data
/// \details
/// This function turns givin data and minus data into 360 values
/// for example -120 should become 240 and 450 should become 90.
void threesixty(double & in, double & out){

    if(!(in < 0.5 and in> -0.5)){
        
        out += in;

        int th_min = -1440;
        int th_plus = 1440;

        for(uint8_t i = 0; i < 2; i++){       
            if(out < th_min){
                out -= th_min;
            }
            th_min /= 2;              
        }

        if(out < 0){
            out += 360;
        }   

        for(uint8_t i = 0; i < 3; i++){
            if(out > th_plus){
                out -= th_plus;
            }
            th_plus /= 2;
        }

    }

}

/// \brief
/// interface for l3g4200
/// \details
/// this class interfaces the l3g4200 chip for the slave arudino and should not be used by the user unless you want to only use one Arudino.
class l3g4200{


private:

    //gyro values
    double gyro_x;
    double gyro_y;
    double gyro_z;

    //dps values
    int dps_x;
    int dps_y;
    int dps_z;

    int temperature;

    

    //i2c bus
    hwlib::i2c_bus_bit_banged_scl_sda & bus;
    
    
    //L3G4200 Data Registers
    uint8_t CTRL_REG1 = 0x20;
    uint8_t CTRL_REG2 = 0x21;
    uint8_t CTRL_REG3 = 0x22;
    uint8_t CTRL_REG4 = 0x23;
    uint8_t CTRL_REG5 = 0x24;

    uint8_t OUT_TEMP = 0x26;
    uint8_t STATUS_REG = 0X27;
    
    uint8_t OUT_X_L = 0X28;
    uint8_t OUT_X_H = 0X29;
    uint8_t OUT_Y_L = 0X2A;
    uint8_t OUT_Y_H = 0X2B;
    uint8_t OUT_Z_L = 0X2C;
    uint8_t OUT_Z_H = 0X2D;

    #define SCALE_2000 0x02
    #define SCALE_500 0x01
    #define SCALE_250 0x00

    uint8_t address = 0X69;
    uint8_t type_select = 35;
    

public:

/// \brief
/// Constructor of the l3g4200 interface 
/// \details
/// This contructor construct an interface for the l3g4200 chip.
    l3g4200(hwlib::i2c_bus_bit_banged_scl_sda & bus ):
    bus(bus)
    {}

/// \brief
/// Constructor of the l3g4200 interface with different address
/// \details
/// This contructor construct an interface for the l3g4200 chip with a diverging address.
    l3g4200(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t address ):
    bus(bus),
    address(address)
    {}

    i2c_fast fast = {bus, address};

/// \brief
/// Resets gyro values
/// \details
/// This function resets all gyro values to zero.
    void reset(){

        gyro_x = 0;
        gyro_y = 0;
        gyro_z = 0;


    }

/// \brief
/// Returns when gyroscope data changed
/// \details
/// This function is used as an stop. The function returns when the gyroscope has written a new value to it's registers. This function
/// made the read data more accurately.
    void check_status(){

        uint8_t reg_status[1] = {STATUS_REG};
        
        while(true){
            
            reg_status[0] = fast.read(reg_status[0]);

            if (((reg_status[0] >> 3) & 0x1) && ((reg_status[0]>> 7) & 0x1)){
                return;
            }

        }
       
    }

/// \brief
/// Changes the gyroscope scale
/// \Details
/// The gyroscope has different reading modes. With this function you can change these modes to your own liking. You can set the scale 
/// 2000, 500 and 250.

 
    void set_scale(int scale){

        if(scale == 2000){
            uint8_t scale_reg[2] = {CTRL_REG4, (SCALE_2000 << 4)};
            bus.i2c_bus::write(address).write(scale_reg, 2);
            type_select = 17.5 / 2 / 2;
        }

        if(scale == 500){
            uint8_t scale_reg[2] = {CTRL_REG4, (SCALE_500 << 4)};
            bus.i2c_bus::write(address).write(scale_reg, 2);
            type_select = 17.5;
        }

        if(scale == 250){
            uint8_t scale_reg[2] = {CTRL_REG4, (SCALE_250 << 4)};
            bus.i2c_bus::write(address).write(scale_reg, 2);
            type_select = 35;
        }


    }

/// \brief
/// calculates next gyro values
/// \details
/// This function updates all the gyro values and also generates the next value of the gyro based on the degree per second values read out of the l3g4200 registers.
    void update(int interval){

        check_status();

        uint8_t xyz_h[6] = {0,0,0, OUT_X_H, OUT_Y_H, OUT_Z_H};
        uint8_t xyz_l[6] = {0,0,0, OUT_X_L, OUT_Y_L, OUT_Z_L};

        dps_x = ((fast.read(xyz_h[3], xyz_h[0]) << 8) + fast.read(xyz_l[3], xyz_l[0])) / type_select;
        dps_y = ((fast.read(xyz_h[4], xyz_h[1]) << 8) + fast.read(xyz_l[4], xyz_l[1])) / type_select;
        dps_z = ((fast.read(xyz_h[5], xyz_h[2]) << 8) + fast.read(xyz_l[5], xyz_l[2])) / type_select;

        double temp_x = interval * 0.001  * dps_x;

        threesixty(temp_x, gyro_x);

        double temp_y = interval * 0.001 * dps_y;

        threesixty(temp_y, gyro_y);

        double temp_z = interval * 0.001 * dps_z;

        threesixty(temp_z, gyro_z);

        update_temp();

    }

/// \brief
/// Prints gyro values for demonstration 
/// \details
/// This function prints the gyro values for the demonstration and can be used for debugging.
    void print(){

        hwlib::cout<< "X: " << int(gyro_x) << "Y: "<< int(gyro_y) << "Z: "<< int(gyro_z) << " \n";

    }

/// \brief
/// Prints degrees per second values for demonstration 
/// \details
/// This function prints the degrees per second values for the demonstration and can be used for debugging.
    void print_dps(){
        
        hwlib::cout << "X: " << dps_x << " Y: " << dps_y << " Z: " << dps_z << " \n";
        
    }

/// \brief
/// Wakes up the gyroscope
    void wake(){

        gyro_x = 0;
        gyro_y = 0;
        gyro_z = 0;
        dps_x = 0;
        dps_y = 0;
        dps_z = 0;

        uint8_t wake[][2] = {

            {CTRL_REG1, 0x0F}, 
            {CTRL_REG2, 0X00 },  
            {CTRL_REG3, 0X08 },  
            {CTRL_REG4, 0X00 },  
            {CTRL_REG5,  0X00 }

        };
            for(int i = 0; i < 5; i++){bus.i2c_bus::write(address).write(wake[i], 2);}
            set_scale(500);

    }

/// \brief
/// Tugs in the gyroscope.
/// \details
/// This function sends a bit to the sleep register of the l3g4200 and turns it into sleepmode
    void sleep(){

        uint8_t sleep[] = {CTRL_REG1, 0};
        bus.i2c_bus::write(address).write(sleep, 2);

    }

/// \brief
/// Updates temperature variable
/// \details
/// This function updates the temperature variable by reading the temperature register on the l3g4200
    void update_temp(){

        uint8_t data_h[1] = {OUT_TEMP};
        temperature = fast.read(data_h[0]);

    }
/// \brief
/// Gets temperature variable
/// \details
/// This function returns the temperature value
    int get_temperature(){return temperature;}

/// \brief
/// Returns gyro x shifted 8 bits to the right.
/// \details
/// This function reads the gyro x variable and returns a the value shifted 8 bits to the right
    int get_x_gyro_h(){return (int(gyro_x) >> 8);}

/// \brief
/// Returns x gyro variable
/// \details
/// This function returs the x gyro variable
    int get_x_gyro_l(){return (int(gyro_x));}

/// \brief
/// Returns y gyro shifted 8 bits to the right.
/// \details
/// This function reads the gyro x variable and returns a the value shifted 8 bits to the right
    int get_y_gyro_h(){return (int(gyro_y) >> 8);}

/// \brief
/// Returns y gyro variable
/// \details
/// This function returs the y gyro variable
    int get_y_gyro_l(){return (int(gyro_y));}

/// \brief
/// Returns z gyro shifted 8 bits to the right.
/// \details
/// This function reads the gyro x variable and returns a the value shifted 8 bits to the right
    int get_z_gyro_h(){return (int(gyro_z) >> 8);}

/// \brief
/// Returns z gyro variable
/// \details
/// This function returs the z gyro variable
    int get_z_gyro_l(){return int(gyro_z);}

/// \brief
/// Returns x dps shifted 8 bits to the right.
/// \details
/// This function reads the gyro x variable and returns a the value shifted 8 bits to the right
    int get_dps_x_h(){return (dps_x >> 8);}

/// \brief
/// Returns x dps variable
/// \details
/// This function returs the x dps variable
    int get_dps_x_l(){return dps_x;}

/// \brief
/// Returns y dps shifted 8 bits to the right.
/// \details
/// This function reads the gyro x variable and returns a the value shifted 8 bits to the right
    int get_dps_y_h(){return (dps_y >> 8);}

/// \brief
/// Returns y dps variable
/// \details
/// This function returs the y dps variable
    int get_dps_y_l(){return dps_y;}

/// \brief
/// Returns z dps shifted 8 bits to the right.
/// \details
/// This function reads the gyro x variable and returns a the value shifted 8 bits to the right
    int get_dps_z_h(){return (dps_z >> 8);}

/// \brief
/// Returns z dps variable
/// \details
/// This function returs the z dps variable
    int get_dps_z_l(){return dps_z;}

   
};


#endif //MPU6050
