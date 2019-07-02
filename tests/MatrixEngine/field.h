//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)s

#ifndef FIELD_H
#define FIELD_H
/// @file
#include "pos.h"

#include "object.h"
#include "window_conf.h"




/// \brief
/// Entire playground of the scene.
/// \details
/// A class that contains a 2d array of characters with a x and an y size.
class field {
    
private:
     
     int x_size;
     int y_size; 
     
          
public:

    char playground[Y_SIZE][X_SIZE] = {{'.'}};
    
	
/// \brief
/// Constructor of field class.
/// \details
/// Constructor of field class, takes in a x size and y size and initialises a 2d array with those sizes.
	field(
    const int & x_size, 
    const int & y_size
	):
    
    x_size(x_size),
    y_size(y_size)
    {}
/// \brief
/// Returns x
/// \details
/// This function returns x
    int get_x(){return x_size;}

/// \brief
/// Returns y
/// \details
/// This function returns y
    int get_y(){return y_size;}
    
/// \brief
/// Initialises all the empty spaces in the Playground Array.
/// \details
/// \This function initialises all the empty spaces in the Playground Array.
    void create();
    
/// \brief
/// Writes character to 2d Array.
/// \details
/// This function writes a givin character to the Playground Array.
    void draw(entity & obj);

/// \brief
/// Writes character to 2d Array.
/// \details
/// This function writes a givin character to the Playground Array.
    void draw(obstacle & obst);

/// \brief
/// Clears screen buffer
/// \details
/// This function clears the Playground array buffer.
    void clear_buffer(){

        for(int i = 0; i < y_size; i++){
            for(int j = 0; j < x_size; j++){
                playground[i][j] = '.';
            }
        }

    }

/// \brief
/// Returns posTouch of entity in the Playground Array.
/// \details
/// This function returns posTouch of a givin entity in the the Playground Array.
	
    posTouch get_touch(entity & obj);
	
	void get(char new_scene[Y_SIZE][X_SIZE]);
	void set(char new_scene[Y_SIZE][X_SIZE]);
    
};



#endif //FIELD_H
