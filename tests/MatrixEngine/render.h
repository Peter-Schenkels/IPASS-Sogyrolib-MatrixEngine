//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)




#include "object.h"
#include "field.h"
#include "window_conf.h"


#ifndef RENDER_H
#define RENDER_H




void draw_instance(entity draw_objects[OBJCT_SIZE], field & veld);
void draw_instance(obstacle draw_objects[OBSTCLES_SIZE], field & veld);
void update();
#endif //RENDER_H
