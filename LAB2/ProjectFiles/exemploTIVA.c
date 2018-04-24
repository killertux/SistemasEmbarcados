/*============================================================================
 *                    Exemplos de utilização do Kit
 *              EK-TM4C1294XL + Educational BooterPack MKII 
 *---------------------------------------------------------------------------*
 *                    Prof. André Schneider de Oliveira
 *            Universidade Tecnológica Federal do Paraná (UTFPR)
 *===========================================================================
 * Autores das bibliotecas:
 * 		Allan Patrick de Souza - <allansouza@alunos.utfpr.edu.br>
 * 		Guilherme Jacichen     - <jacichen@alunos.utfpr.edu.br>
 * 		Jessica Isoton Sampaio - <jessicasampaio@alunos.utfpr.edu.br>
 * 		Mariana Carrião        - <mcarriao@alunos.utfpr.edu.br>
 *===========================================================================*/
#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include <stdio.h>


/*----------------------------------------------------------------------------
 * include libraries from drivers
 *----------------------------------------------------------------------------*/

#include "Display.h"
#include "buttons.h"
#include "joy.h"

#include "horizon.h"
#include "Car.h"
#include "Road.h"

#define COLOR_THRESHOLD 100

Display display;

/*----------------------------------------------------------------------------
 *    Initializations
 *---------------------------------------------------------------------------*/

void init_all(){
	display_init(&display);
	joy_init(); 
	button_init();
}

/*----------------------------------------------------------------------------
 *      Main
 *---------------------------------------------------------------------------*/
int main (void) {
	int x, h_move;
	Car my_car, enemy_car;
	Road road;
	
	init_all();

	road_init(&road);
	car_init(&my_car);
	car_init(&enemy_car);
	my_car.x = 58;
	enemy_car.x = 70;
	my_car.color = 0xc4bdc4;
	enemy_car.color = 0x6546c5;
	
  while(1){
			h_move = 0;	
			display_clear_back_buffer(&display);
			x = joy_read_x();
			if(x > 3000) {
				h_move = 1;
				if(my_car.x < 128-23)
					my_car.x+=2;
			} else if (x < 1000) {
				h_move = -1;
				if(my_car.x > 0)
					my_car.x-=2;
			}
			if(enemy_car.y < 47)
				enemy_car.y++;
			else 
				enemy_car.y = 0;
			road.state = 1;
			horizon_draw(&display, h_move);
			road_draw(&display, &road, h_move);
			car_draw(&display, &enemy_car);
			car_draw(&display, &my_car);
			display_update(&display);
	}
	return 0;
}
