//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#include "object.h"
#include "field.h"
#include "window_conf.h"
#include "physics.h"
#include "render.h"







//all objects that are visable in the scene
void draw_instance(entity draw_objects[OBJCT_SIZE], field & veld){
    
    

    for(unsigned int i = 0; i < OBJCT_SIZE; i++){




        veld.draw(draw_objects[i]);
    } 
}
//all obstacles that are visable in the scene
void draw_instance(obstacle draw_objects[OBSTCLES_SIZE], field & veld){
    
    for(unsigned int i = 0; i < OBSTCLES_SIZE; i++){
        veld.draw(draw_objects[i]);
    }
}
