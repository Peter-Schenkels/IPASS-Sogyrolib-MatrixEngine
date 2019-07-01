//          Copyright Peter Schenkels 2019 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "matrix_engine.hpp"
#include "l3g4_master.hpp"
#include "controller.hpp"


//#############################################//
//					       //
//	                 scripts               //
//					       //
//#############################################//

void jump(entity & object, field & scene){

	if(scene.get_touch(object).down == '#' && object.get_speed_y() < 0){
		object.set_speed_y(4);
	}
	
}

void out_of_bound(entity & object){

	if(object.get_x() <= 1 && object.get_speed_x() < 0){
		object.set_x(9);
	}
	else if(object.get_x() >= 8 && object.get_speed_x() > 0){
		object.set_x(0);
	}

}

void display_score(int score, led_matrix display){

	if (score >= 100){

		display.number((score - ((score % 100) + (score % 10)))/100);
		hwlib::wait_ms(500);
		display.clear();
		hwlib::wait_ms(50);
		display.number((score % 100 - (score % 10))/10);
		hwlib::wait_ms(500);
		display.clear();
		hwlib::wait_ms(50);
		display.number(score % 10);
		hwlib::wait_ms(500);
		display.clear();
		hwlib::wait_ms(50);

	}
	else if( score >= 10){

		display.number((score - (score % 10))/10);
		hwlib::wait_ms(500);
		display.clear();
		hwlib::wait_ms(50);
		display.number(score % 10);
		hwlib::wait_ms(500);
		display.clear();
		hwlib::wait_ms(50);

	}
	else{

		display.number(score);
		hwlib::wait_ms(1000);

	}

}

unsigned int seed()
      {
         static unsigned int seed = 5323;
         seed = 8253729 * seed + 2396403;
		 if (((seed  % 32768) / 1000 % 4 * 2 - 1 )>10){
			 return 3;
		 }
		 
         return (seed  % 32768) / 1000 % 4 * 2 ;
		 
      };  


void death(player & obj, obstacle & start, window & camera, sogyro & gyro){
	
	start.set_pos(1, 23, 9, 23);
	obj.set_x(4);
	obj.set_y(22);
	camera.follow_y(obj);
	camera.set_y(camera.get_y() - 4);
	obj.start = true;
	obj.score = 0;
	gyro.reset();

}

void zone_check( player & obj, led_matrix & matrix, window & camera, obstacle & start, obstacle & obst1,  obstacle & obst2,  obstacle & obst3,  obstacle & obst4,  obstacle & obst5,  obstacle & obst6, sogyro & gyro ){
	

	if ( (camera.get_y() - obj.get_y() < -8 && !obj.start) || (obj.get_y() >= 25) ){

		display_score(obj.score, matrix);
		death(obj, start, camera, gyro);
		

	}

	if(obj.get_y() < 16){

		obj.start = false;
	}


	if(obj.get_y() < 24 && obj.get_y() > 16 && obj.zone == 3 ){
		
		unsigned int random1 = seed();
		unsigned int random2 = seed();
		unsigned int random3 = seed();
		unsigned int random4 = seed();

		if(random1 > 8){
			random1 = 3;
		}	
		if(random2 > 8){
			random2 = 4;
		}	
		if(random3 > 8){
			random3 = 5;
		}	
		if(random4 > 8){
			random4 = 6;
		}	

		obst3.set_pos(random1, 15, random1 + 3, 15);
		obst4.set_pos(random2, 11, random2 + 3, 11);
		obst5.set_pos(random3, 7, random3 + 3, 7);
		obst6.set_pos(random4, 3, random4 + 3, 3);
		obj.score++;
		obj.zone = 1;

	}
	if(obj.get_y() < 16 && obj.get_y() > 8 && obj.zone == 1){

		obst1.set_pos(obst5.get_start_x(), obst5.get_start_y() +16, obst5.get_end_x(), obst5.get_end_y() +16 );
		obst2.set_pos(obst6.get_start_x(), obst6.get_start_y() + 16, obst6.get_end_x(), obst6.get_end_y() +16 );
		obj.score++;
		obj.zone = 2;
		

	}
	if(obj.get_y() < 5 && obj.zone == 2){

		start.set_pos(0,0,0,0);
		obj.score++;
		obj.set_y(obj.get_y() + 16);
		camera.follow_y(obj);
		camera.set_y(camera.get_y() - 4);
		obj.zone = 3;

	}


}







//#############################################//
//											   //
//			    All objects here		   	   //
//											   //
//#############################################//

int main(){
	
	//Scene creation.
	//Adjust scene size in window_conf.h.
	field scene(X_SIZE, Y_SIZE);
	scene.create();
	

	//Window creation.
	//Adjust window size in window_conf.h.

	window screen(1,24, WINDOW_SIZE_X, WINDOW_SIZE_Y, scene);
	

	//Objects in game.


	player ball(4,22, 'X',0, 1, true, false, false);


	//obstacles
	
	
	obstacle start(1, 23, 9, 23);
	obstacle platform1(1, 23, 9, 23);
	obstacle platform2(2, 19, 5, 19);
	obstacle platform3(2, 15, 5, 15);
	obstacle platform4(2, 11, 5, 11);
	obstacle platform5(2, 7, 5, 7);
	obstacle platform6(2, 3, 5, 3);
	

	

	physbox physics;

	int counter = 0;    

	auto clk2  = hwlib::target::pin_out( hwlib::target::pins::d44); 
	auto mosi  = hwlib::target::pin_out( hwlib::target::pins::d45); 
	auto miso  = hwlib::target::pin_in( hwlib::target::pins::d46); 
	auto cs  = hwlib::target::pin_out( hwlib::target::pins::d47);

	auto spi2 = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk2, mosi, miso, 1000);

	sogyro gyro(spi2, cs);
	controller control(gyro);


	auto din = hwlib::target::pin_out( hwlib::target::pins::d52 );
    auto cs1   = hwlib::target::pin_out( hwlib::target::pins::d49 );
    auto clk = hwlib::target::pin_out( hwlib::target::pins::d51 );
    auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( 
        clk, din, hwlib::pin_in_dummy 
    );

    led_matrix matrix(spi, cs1);

	matrix.wake();
	gyro.reset();


//#############################################//
//											   //
//			        Frame            		   //
//											   //
//#############################################//

//Add your own code here.
//Draw_objects and draw_obstacles are mandatory and need to be filled with objects and obstacles.
//After declaring those arrays the fucntion draw_instance get initiated and renders the objects in the scene.
//Screen.draw() is mandatory to draw the frame.
	
    for(;;){

		
		ball.set_speed_x(control.get_dir_z(10));

	
		counter++;


		//Scene initialiser.
		//All objects that are being rendered inside the frame.
		entity draw_entities[OBJCT_SIZE] {

		///Add your objects here.
		///Adjust number of visiable objects in window_conf.h

			ball
			
		};
	
		obstacle draw_obstacles[OBSTCLES_SIZE] {
		///Add your obstacles here.
		///Adjust number of visiable obstacles in window_conf.h.
	
			start,
			platform1,
			platform2,
			platform3,
			platform4,
			platform5,
			platform6
			
		};
			draw_instance(draw_obstacles, scene);
			draw_instance(draw_entities, scene);
			out_of_bound(ball);
			jump(ball, scene);			
			screen.follow_y(ball, 4);		
			physics.calculate_gravity(ball, scene);
			
			//Frame gets drawn.
			screen.draw(matrix);
			scene.clear_buffer();

			zone_check(ball, matrix, screen, start, platform1, platform2, platform3, platform4, platform5, platform6, gyro );
			
			hwlib::wait_ms(100);
			
				
			
	}
		

}
    



