//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef POS_H
#define POS_H

/// @file


/// \brief
/// 3D postion ADT
/// \details
/// This class is a three dimensional ADT
class xyz{
  
public:
    float x;
    float y;
    float z;

/// \brief 
/// Constructor of xyz 
/// \details
/// This is the constructor of the three dimensional ADT
    xyz(float x, float y, float z):
    x(x), y(y), z(z){}

    xyz operator *(const int  & rhs){
        return xyz(x * rhs, y * rhs, z * rhs);
    }
    xyz operator  *=(const int & rhs){
        x = x * rhs; 
        y = y * rhs; 
        z = z * rhs;
        return(*this);
    }
    
};

/// \brief
/// 2D postion ADT
/// \details
/// This class is a two dimensional ADT
class xy{
     
public:

    int x;
    int y;

/// \brief 
/// Constructor of xy
/// \details
/// This is the constructor of the two dimensional ADT
    xy(int p_x, int p_y) {
        x = p_x; 
        y = p_y;
    }
    
    
/// \brief 
/// Returns x
/// \details
/// This function return the x value
    
    int get_x(){
        
        return x;
        
    }

/// \brief 
/// Returns y
/// \details
/// This function return the y value   
    int get_y(){
        
        return y;
        
    }

/// \brief 
/// Sets x
/// \details
/// This function sets the x value
    void set_x(int u_x){
        
        x = u_x;
        
    }

/// \brief 
/// Sets y
/// \details
/// This function sets the y value
    void set_y(int u_y){
        
        y = u_y;
        
    }
};


/// \brief
/// Collision ADT
/// \details
/// This class contains the upper character down character left character and right character of a givin object in a field.
class posTouch{
 

    
public:
    	char up;
	char down;
	char left;
	char right;
	
	posTouch(char p_up, char p_down, char p_left, char p_right){
        
        up = p_up;
        down = p_down;
        left = p_left;
        right = p_right;
        
        
        
        }
	
	
	
	
};

#endif //POS_H
