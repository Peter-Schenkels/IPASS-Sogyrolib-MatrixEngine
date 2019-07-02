//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)



#include "object.h"
#include "field.h"
#include "window.h"
#include "window_conf.h"

/// @file

#ifndef MOVEMENT_H
#define MOVEMENT_H


///\ brief
/// generates next position of entity
///\ details
/// Generate next position of an entity on input value d (down) u (up) l (left) r (right) 
/// Object only moves when his next position is equal to air.
void make_move(const char & move, entity & speler, field & veld);

///\ brief
/// generates next position of camera
///\ details
/// Generate next position of an entity on input value d (down) u (up) l (left) r (right) 
/// Object only moves when his next position is equal to air.
void make_move(const char & move, window & camera, field & veld);




#endif //MOVEMENT_H
