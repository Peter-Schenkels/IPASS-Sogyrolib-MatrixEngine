//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef PHYSICS_H
#define PHYSICS_H
/// @file
#include "field.h"
#include "object.h"
#include "window_conf.h"


/// \brief 
/// Physics engine
/// \details
/// physics engine that calculates basic stuff like gravity speed bouncing and other types of movement
class physbox {
    
    public:
/// \brief
/// Calculates the next movent of entity
/// \details
/// This function calculates the next movement of the given object in a given scene.
    void calculate_movement(entity & object, field & scene);

/// \brief
/// Calculates gravity on object
/// \details
/// This function calculates the gravity physics of the given object in given scene.
    void calculate_gravity(entity & object, field & scene );

/// \brief
/// Calculates bounce on object
/// \details
/// This function calculates if the given object should be bouncing in given scene
    void calculate_bounce(entity & object, field & scene);

};





#endif //PSYSICS_H
