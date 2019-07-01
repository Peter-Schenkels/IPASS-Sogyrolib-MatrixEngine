//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)



#ifndef OBJECT_H
#define OBJECT_H

/// @file

#include "pos.h"



/// \brief
/// A void object with a position
/// \details
/// A void object with a position, an object on its own is invisable inside a frame because it's a void.
class object{
	
protected:
    /// \brief 
    /// position of object
    /// \details
    /// x and y position of an object
		xy posXY;
    
		
public:
	
	object(const int & start_x, const int & start_y):
	
	posXY(start_x, start_y)
  
	{
		
		
	}
	
	
  /// \brief
  /// returns x 
  /// \details
  /// returns x position of the object
  virtual int get_x() {return posXY.get_x();}

  /// \brief
  /// returns y
  /// \details
  /// returns y position of the object
  virtual int get_y() {return posXY.get_y();}
  
  /// \brief
  /// sets x 
  /// \details
  /// sets x position of the object
  virtual void set_x(int u_x) {posXY.set_x(u_x);}

  /// \brief
  /// sets y 
  /// \details
  /// sets y position of the objects
  virtual void set_y(int u_y) {posXY.set_y(u_y);}


  /// \brief
  /// Set position to given coordinates
  /// \details
  /// This function sets the position of the object to the given x, y coordinates
  void set_pos(int x, int y) {set_x(x); set_y(y);}
  
  /// \brief
  /// Subtracts one from x
  /// \details
  /// Moves the object up by one unit subtracting one to the x position
	void move_up();

    /// \brief
    /// Adds Sone from x
    /// \details
    /// Moves the object down by one unit adding one to the x position
	void move_down();

    /// \brief
    /// Subtracts one from y
    /// \details
    /// Moves the object left by one unit subtracting one to the y position
	void move_left();

    /// \brief
    /// Adds one from y
    /// \details
    /// Moves the object right by one unit by adding one to the y position
	void move_right();
	
	
	
};


/// \brief
/// A visable entity
/// \details
/// An entity that has an icon, a speed and optionally gravity and other physics.
class entity : public object{
protected:
     
  char icon;
  float speed_x;
  float speed_y;
  bool gravity;
  bool bounce;
  bool stand = 0;
  int health = 100;
  float strength = 1;
  float weight = 1;
  bool solid;
  
    
public:

/// \brief
/// Constructs a entity
/// \details
/// This constructor construct an entity
  entity(const int & start_x, const int & start_y, char p_icon, const float & speed_x,  const float & speed_y, const bool & gravity, const bool & bounce, const bool & solid):
  object(start_x, start_y),
  speed_x(speed_x),
  speed_y(speed_y),
  gravity(gravity),
  bounce(bounce),
  solid(solid)
  {
  icon = p_icon;    
  }
  
  unsigned int score = 0;

  bool get_stand(){return stand;}

  void set_stand(bool new_stand){stand = new_stand;}

/// \brief
/// returns solid
/// \details
/// returns if the object is solid
  bool get_solid(){return solid;}

  /// \brief
  /// returns icon
  /// \details
  /// returns entity's char variabel named icon.
   char get_icon(){return icon;}

  /// \brief
  /// returns x speed
  /// \details
  /// returns entity's float variabel named speed_x.
   float get_speed_x(){return speed_x;}

  /// \brief
  /// sets x speed
  /// \details
  /// replaces entity's x speed to givin float.
   void set_speed_x(float new_speed){speed_x = new_speed;}

  /// \brief
  /// returns yspeed
  /// \details
  /// returns entity's float variabel named speed_y.
   float get_speed_y(){return speed_y;}

  /// \brief
  /// sets y speed
  /// \details
  /// replaces entity's y speed to givin float.
   void set_speed_y(float new_speed){speed_y = new_speed;}

  /// \brief
  /// returns gravity
  /// \details
  /// returns if entity has gravity.
   bool get_gravity(){return gravity;}

  /// \brief
  /// returns bounce
  /// \details
  /// returns if entity is able to bounce.
   bool get_bounce(){return bounce;}



};


/// \brief
/// Solid Object with a start end point
/// \details
/// This class of an solid object with a start and end position. this object is able to draw lines.
class obstacle : public object{
    
private:

  int end_x, end_y;
  bool passable = false;
	char icon = '#';
	
	
public:
/// \brief
/// Constructor of obstacle with only 1 position
/// \details
/// This constructor constructs obstacle with only 1 position
  obstacle(int start_x, int start_y):
	object(start_x, start_y),
	end_x(start_x),
	end_y(start_y)
  {}
/// \brief
/// Constructor of obstacle with only 1 position and if it's solid
/// \details
/// This constructor constructs obstacle with only 1 position and if it's solid	
  obstacle(int start_x, int start_y, bool passable):
  object(start_x, start_y),
  end_x(start_x),
  end_y(start_y),
  passable(passable)
  {}
/// \brief
/// Constructor of obstacle with 2 positions
/// \details
/// This constructor constructs obstacle with 2 positions
  obstacle(int start_x, int  start_y, int  end_x, int end_y):
  object(start_x, start_y),
  end_x(end_x),
  end_y(end_y)

  {}
/// \brief
/// Constructor of obstacle with 2 positions and if it's solid
/// \details
/// This constructor constructs obstacle with 2 position  and if it's solid
  obstacle(int start_x, int start_y, int end_x, int end_y, bool passable):
  object(start_x, start_y),
  end_x(end_x),
  end_y(end_y),
  passable(passable)
  
  {
  if (passable == 1){icon = 'o';}
  }

/// \brief
/// sets position of obstacle
/// \details
/// This function sets the 2 postions of an obstacle
  void set_pos(int p_start_x, int p_start_y, int p_end_x, int p_end_y){

    posXY.x = p_start_x;
    posXY.y = p_start_y;
    end_x = p_end_x;
    end_y = p_end_y;

  }
/// \brief
/// Returns start x
/// details
/// This function returns the start x value
  int get_start_x(){return posXY.get_x();}

/// \brief
/// Returns start x
/// details
/// This function returns the start x value
  int get_start_y(){return posXY.get_y();}

/// \brief
/// Returns end x
/// details
/// This function returns the end x value
  int get_end_x(){return end_x;}

/// \brief
/// Returns end x
/// details
/// This function returns the end x value
  int get_end_y(){return end_y;}

/// \brief
/// Returns icon
/// details
/// This function returns the icon
  char get_icon(){return icon;}
	
	
	
};

class player : public entity {


public:

  player(const int & start_x, const int & start_y, char p_icon, const float & speed_x, const float & speed_y, const bool & gravity, const bool & bounce, const bool & solid):
  entity(start_x, start_y, p_icon, speed_x, speed_y, gravity, bounce, solid)
  {}


  int zone = 1;
  bool set = false;
  bool start = true;

};

#endif //OBJECT_H
