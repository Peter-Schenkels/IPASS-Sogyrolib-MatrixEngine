//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)




#ifndef WINDOW_H
#define WINDOW_H

/// @file
#include "pos.h"
#include "field.h"
#include "object.h"
#include "led_matrix.hpp"
#include "hwlib.hpp"


/// \brief
/// Renders all data within the sizes and positions
/// \details
/// Window class is similair to a camera in the way that it only renders what it sees. The window class has it's own position inside the field and can follow objects.
class window : public object{
    
private:

     int x_size;
     int y_size;
     field & f;

public:

    window(
    int x,
    int y, 
    int x_size, 
    int y_size,
    field & f):
    object(x, y),
    x_size(x_size),
    y_size(y_size),
    f(f)
    {}

    /// \brief
    /// Renders data to terminal 
    /// \details 
    /// turns vector data from field into terminal outputs
    void draw();

    /// \brief
    /// Renders data to 8x8 matrix
    /// \details 
    /// turns array data from field into 8x8 matrix
    void draw(led_matrix & display);

    /// \brief
    /// Renders data to hwlib window
    /// \details 
    /// turns array data from field into a hwlib window
    void draw(hwlib::window & display);

    /// \brief
    /// Changes xy pos of frame
    /// \details
    /// Moves frame directly to a certain x and y position inside the scene
    void move(xy start);

    /// \brief
    /// Changes from begin xy to an end xy pos
    /// \details
    /// Animates a frame to a certain x and y position every tick 
    void move(xy start, xy end);


    /// \brief
    ///Frame follows object
    /// \details
    ///Frame follows given object for one frame
    void follow(object & obj);


    /// \brief
    ///Frame follows object
    /// \details
    ///Frame follows the y axis for a given object for one frame
    void follow_y(object & obj);
    
    /// \brief
    ///Frame follows object
    /// \details
    ///Frame follows the y axis for a given object for one frame with an offset
    void follow_y(object & obj, int offset);
    
};


#endif //WINDOW_H
