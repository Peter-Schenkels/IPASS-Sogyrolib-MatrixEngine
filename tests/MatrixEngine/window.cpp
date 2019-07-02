//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)




#include "window.h"
#include "field.h"
#include "window_conf.h"



using namespace std;



void window::move(xy start){


    set_x(start.get_x());
    set_y(start.get_y());


}

void window::move(xy start, xy end){
    



}

void window::draw(){
    
    
	
    
    int end_x = get_x() + x_size;
    int end_y = get_y() + y_size;
    
    
    
    //when frame is out of boundary
    if (end_x > f.get_x()){
        end_x = f.get_x();
    }
    
    if (end_y > f.get_y()){
        end_y = f.get_y();
    }
    
    //drawing window
    for( int y = get_y(); y < end_y; y++){
		
        hwlib::cout << "\n";
		
        for ( int x = get_x(); x <= end_x; x++){
            
            hwlib::cout << f.playground[y][x] << " ";
		
        }
    }
    hwlib::cout << "\n\n\n\n\n\n\n";
    
       
}
void window::draw(led_matrix & display){
    
    
   
    int end_x = get_x() + x_size;
    int end_y = get_y() + y_size;
    
    
    
    //when frame is out of boundary
    if (end_x > f.get_x()){
        end_x = f.get_x();
    }
    
    if (end_y > f.get_y()){
        end_y = f.get_y();
    }
    
    //drawing window
    for( int y = get_y(); y < end_y; y++){
		
       
		
        for ( int x = get_x(); x <= end_x; x++){
            
            if (f.playground[y][x] != '.'){
                display.write(hwlib::xy{(y - get_y()), (x - get_x())},  hwlib::white);
            }
            else{
                display.write(hwlib::xy{(y - get_y()), (x - get_x())},  hwlib::black);
            }
            
		
        }
        
    }
    display.flush();

    
       
    
}

void window::draw(hwlib::window & display){
    
    display.clear();
   
    int end_x = get_x() + x_size;
    int end_y = get_y() + y_size;
    
    
    
    //when frame is out of boundary
    if (end_x > f.get_x()){
        end_x = f.get_x();
    }
    
    if (end_y > f.get_y()){
        end_y = f.get_y();
    }
    
    //drawing window
    for( int y = get_y(); y < end_y; y++){
		 
        for ( int x = get_x(); x <= end_x; x++){
            
            if (f.playground[y][x] != '.'){
                display.write(hwlib::xy{(x - get_x()), (y - get_y())}, hwlib::white);
            }
            else{
                display.write(hwlib::xy{(x - get_x()), (y - get_y())},  hwlib::black);
            }
            
		
        }
       
    }

    display.flush();

    
       
    
}

void window::follow(object & obj){

    set_x(obj.get_x());
    set_y(obj.get_y());

}

void window::follow_y(object & obj){

    set_y(obj.get_y());
    

}

void window::follow_y(object & obj, int offset){

    
    if(obj.get_y() - offset < get_y()){set_y(obj.get_y() - offset );}
    

}


