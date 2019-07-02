//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

/// @file
#include "l3g4_master.hpp"





/// \brief
/// Gyroscope decorator
/// \details
/// This class a decorator for the gryoscope and can be used in games. It can return values based on the tilt of the gyroscope.
class controller : public sogyro{


public: 

/// \brief
/// Constructor for gyroscope decorator.
/// \details
/// thsi contructor interfaces the controller decorator for the gyroscope.
    controller(sogyro & gyro):
    sogyro(gyro)
    {}

    ///\brief
    /// Returns direction as an int
    ///\details
    /// Returns direction as an int
    /// 0 is middle 1 is right -1 left

    int dir(int gyro, int scale){
        hwlib::cout <<  gyro << '\n';
         if (gyro > scale && gyro < 100 ){
            return -1;
        }

        //right
        

        else if(gyro  < 360 - scale && gyro > 260 ){
            return 1;
        }

        //middle
        else{
            return 0;
        }

    }
 
    ///\brief
    /// Returns direction x as an int
    ///\details
    /// Returns direction x as an int
    /// 0 is middle 1 is right -1 left
    int get_dir_x(int scale){

        return dir(get_gyro_x(), scale);
  
    }

    ///\brief
    /// Returns direction y as an int
    ///\details
    /// Returns direction y as an int
    /// 0 is middle 1 is right -1 left
    int get_dir_y(int scale){

        return dir(get_gyro_y(), scale);
  
    }

    ///\brief
    /// Returns direction z as an int
    ///\details
    /// Returns direction z as an int
    /// 0 is middle 1 is right -1 left
   int get_dir_z(int scale){

        return dir(get_gyro_z(), scale);
  
    }
    
};

#endif
