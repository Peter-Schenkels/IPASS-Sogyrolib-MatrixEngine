//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)



#include "field.h"
#include "pos.h"



//object movement 


void object::move_up(){
	
	posXY.y -= 1;
    
}

void object::move_down(){
    
    posXY.y += 1;

}

void object::move_left(){
    
    posXY.x -= 1;

}

void object::move_right(){
    
    posXY.x += 1;
        
}


