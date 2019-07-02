//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#include "object.h"
#include "field.h"
#include "window.h"
#include "window_conf.h"
#include "movement.h"



void make_move(const char & move, entity & obj, field & veld){
    

    if(obj.get_solid()){
        if(move == 'd' && veld.get_touch(obj).down == '.'){
            obj.move_down();
        }
        else if(move == 'u' && veld.get_touch(obj).up == '.'){
            obj.move_up();
        }
        else if(move == 'l' && veld.get_touch(obj).left == '.'){
            obj.move_left();
        }
        else if(move == 'r' && veld.get_touch(obj).right == '.'){
            obj.move_right();
        }
    }

    else{
        if(move == 'd' && veld.get_touch(obj).down == '.'){
            obj.move_down();
        }
        else if(move == 'u' && (veld.get_touch(obj).up == '.' || veld.get_touch(obj).up == '#')){
            obj.move_up();
        }
        else if(move == 'l' && veld.get_touch(obj).left == '.'){
            obj.move_left();
        }
        else if(move == 'r' && veld.get_touch(obj).right == '.'){
            obj.move_right();
        }
    }
    

}


void make_move(const char & move, window & camera, field & veld){
    
    if(move == 'd'){
        camera.move_down();
    }
    else if(move == 'u'){
        camera.move_up();
    }
    else if(move == 'l'){
        camera.move_left();
    }
    else if(move == 'r'){
        camera.move_right();
    }

}
