//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)



#include "pos.h"
#include "field.h"
#include "object.h"
#include "window_conf.h"



//Creates new scene.
void field::create(){
	
    for(int y = 0; y < Y_SIZE; y++){
        for (int x = 0; x < X_SIZE; x++){
            field::playground[y][x]= '.';
        }
    }
}

//Draws object into the scene.
void field::draw(entity & obj){
	
    //Deleting last object position.
    for(int y = 0; y < field::get_y(); y++){
        for (int x = 0; x < field::get_x(); x++){
            if (field::playground[y][x] == obj.get_icon()){
               field::playground[y][x] ='.'; 
            }
        }
    }
    
    //Saving object in scene.
    if (obj.get_x() >= 0 and obj.get_x() <=  field::get_x() and obj.get_y() >= 0 and obj.get_y() <= field::get_y()){
        field::playground[obj.get_y()][obj.get_x()] = obj.get_icon();
    }
}

//Draws obstacle into the scene.
void field::draw(obstacle & obst){
    
    int end_y = obst.get_end_y();
    int end_x = obst.get_end_x();
    int start_x = obst.get_x();
    int start_y = obst.get_y();
    
    
    int y_length =  end_y - start_y;
    int x_length = end_x - start_x;
    
    int counter_y = 0; 
    int counter_x = 0;
    
    //Single dot.
    if (x_length == 0 and y_length == 0){
        
        if (start_x >= 0 and start_x <  field::get_x() and start_y >= 0 and start_y < field::get_y()){
                field::playground[obst.get_y()][obst.get_end_x()] = obst.get_icon();
        }
    }
	
	//Straight lines.
	else if (start_x == end_x){
		
		for(int i=start_y; i < end_y; i++){
			 if (start_x >= 0 and start_x <  field::get_x() and start_y >= 0 and start_y < field::get_y()){
                field::playground[i][start_x] = obst.get_icon();
			}	
		}
	}
	
	else if (start_y == end_y){
		
		for(int i=start_x; i < end_x; i++){
			if (start_x >= 0 and start_x <  field::get_x() and start_y >= 0 and start_y < field::get_y()){
				field::playground[start_y][i] = obst.get_icon();
			}
		}
	}
   
   

	//Diagnol lines.
    else if (x_length <= y_length){
      
        int division = y_length / x_length;
        
        
       while(counter_y <= y_length){
            
            int new_x = counter_x + obst.get_x();
			int new_y = counter_y + obst.get_y();
            
           
		   if (new_x >= 0 and new_x <  field::get_x() and new_y >= 0 and new_y < field::get_y()){
			   field::playground[new_y][new_x] = obst.get_icon();
			   }
           
           if (counter_y % division == 0){
             counter_x++;
               }
          counter_y++;
            }
      }
	  
    else if (x_length > y_length){
        
		int division = x_length / y_length;
		
		while(counter_x <= x_length){
			
			int new_x = counter_x + obst.get_x();
			int new_y = counter_y + obst.get_y();
            
			if (new_x >= 0 and new_x <  field::get_x() and new_y >= 0 and new_y < field::get_y()){
               field::playground[new_y][new_x] = obst.get_icon();
                }
				
			if (counter_x % division == 0){
               counter_y++;
                }
			counter_x++;
           }
       } 
}

//Get all chars near the object.
posTouch field::get_touch(entity & obj){
	
    posTouch new_aura('a','b', 'c', 'd');
    
    int y = obj.get_y();
    int x = obj.get_x();
    
    
    new_aura.up = field::playground[y-1][x];
    new_aura.down = field::playground[y+1][x];
    new_aura.left = field::playground[y][x-1];
    new_aura.right = field::playground[y][x+1];
    
    return new_aura;
}





