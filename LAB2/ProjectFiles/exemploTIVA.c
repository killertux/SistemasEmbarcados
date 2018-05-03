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
#include "Information.h"
#include "Interaction.h"
#include "TrackManager.h"

#define COLOR_THRESHOLD 100


/*----------------------------------------------------------------------------
 *    Initializations
 *---------------------------------------------------------------------------*/

void init_all(){
	joy_init(); 
	button_init();
}

/*----------------------------------------------------------------------------
 *      Main
 *---------------------------------------------------------------------------*/
int main (void) {
	Car player_car;
	Display display;
	Information info;
	
	init_all();
	display_init(&display);
	car_init(&player_car);
	information_init(&info, &display, &player_car);
	osKernelInitialize();
	
	init_interaction(&info);
	init_track_manager(&info);

	osKernelStart();
	
	osSignalSet(tid_interaction, 0x01);
	osDelay(osWaitForever);
	return 0;
}
