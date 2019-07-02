//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#include "physics.h"
#include "object.h"
#include "movement.h"



void physbox::calculate_movement(entity & object, field & scene){
    

    int speed_x = object.get_speed_x();
    int speed_y = object.get_speed_y();
    unsigned int amount = 0;
    
    //calculate y
    if (speed_y != 0){
        if (speed_y < 0){
            amount = speed_y * -1;
            for (unsigned int i = 0; i < amount; i++){
                make_move('d', object, scene);
            }
        }
        else{
            amount = speed_y;
            for (unsigned int i = 0; i < amount; i++){
                make_move('u', object, scene);
            }
        }
    }

    //calculate x
    if (speed_x != 0){
        if (speed_x < 0){
            amount = speed_x * -1;
            for (unsigned int i = 0; i < amount; i++){
                make_move('l', object, scene);
            }
        }
        else{
            amount = speed_x;
            for (unsigned int i = 0; i < amount; i++){
                make_move('r', object, scene);
            }
        }   
    } 
}


void physbox::calculate_bounce(entity & object, field & scene){

    if(object.get_bounce() == 1){
    
        if (scene.get_touch(object).down != '.' && object.get_speed_y() < 0){
            object.set_speed_y(object.get_speed_y() * -1);
            if (object.get_speed_y() >= 0){
                object.set_speed_y(object.get_speed_y() - 2);
            }
        }

        else if (scene.get_touch(object).up != '.' && object.get_speed_y() > 0){
            object.set_speed_y(object.get_speed_y() * -1);    
        }

        else if (scene.get_touch(object).left != '.' && object.get_speed_x() < 0){
            object.set_speed_x(object.get_speed_x() * -1);
        }

        else if (scene.get_touch(object).right != '.' && object.get_speed_x() > 0){
            object.set_speed_x(object.get_speed_x() * -1);    
        }
    }
 
    calculate_movement(object, scene);
    
    
}



void physbox::calculate_gravity(entity & object, field & scene){
     if(object.get_gravity() == 1){
            object.set_speed_y(object.get_speed_y()-1);
    
            calculate_bounce(object, scene);
        }
        else{
            calculate_movement(object, scene);
        }
}


