/*============================================================================
 *                    Exemplos de utiliza??o do Kit
 *              EK-TM4C1294XL + Educational BooterPack MKII 
 *---------------------------------------------------------------------------*
 *                    Prof. Andr? Schneider de Oliveira
 *            Universidade Tecnol?gica Federal do Paran? (UTFPR)
 *===========================================================================
 * Autores das bibliotecas:
 * 		Allan Patrick de Souza - <allansouza@alunos.utfpr.edu.br>
 * 		Guilherme Jacichen     - <jacichen@alunos.utfpr.edu.br>
 * 		Jessica Isoton Sampaio - <jessicasampaio@alunos.utfpr.edu.br>
 * 		Mariana Carri?o        - <mcarriao@alunos.utfpr.edu.br>
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
#include "Information.h"

#include "Interaction.h"
#include "TrackManager.h"
#include "Adversaries.h"
#include "PlayerVehicle.h"
#include "Instruments.h"
#include "EndCondition.h"
#include "panel.h"

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
	int s1_press, s2_press;
	Car my_car, enemy_car;
	Road road;
	Information info;

	init_all();

	car_init(&my_car);
	display_init(&display);
	road_init(&road);
	my_car.x = 58;
	my_car.color = 0xb6b6b6;

	information_init(&info, &display, &my_car, &road);
	osKernelInitialize();
  
	info.tid_interaction = init_interaction(&info);
  info.tid_trackmanager = init_track_manager(&info);
	info.tid_player_vehicle = init_player_vehicle(&info);
	info.tid_adversaries = init_adversaries(&info);
	info.tid_instruments = init_instruments(&info);
	info.tid_end_condition = init_end_condition(&info);
		
	osSignalSet(info.tid_interaction, 0x01);
	osDelay(osWaitForever);
	return 0;


}