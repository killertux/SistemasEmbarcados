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
#include "grlib/grlib.h"

/*----------------------------------------------------------------------------
 * include libraries from drivers
 *----------------------------------------------------------------------------*/

#include "cfaf128x128x16.h"
#include "buttons.h"
#include "joy.h"

#include "car.h"
#include "airplane.h"

#define COLOR_THRESHOLD 100

extern void f_asm(void);

//To print on the screen
tContext sContext;
unsigned char graphicMemory[128*128];
uint8_t velocity, direction; //DIRECTION 0 -> RIGTH, 1 -> LEFT, 2 -> UP, 3 -> DOWN
/*----------------------------------------------------------------------------
 *    Initializations
 *---------------------------------------------------------------------------*/

void init_all(){
	cfaf128x128x16Init();
	joy_init(); 
	button_init();
	GrContextInit(&sContext, &g_sCfaf128x128x16);
	GrFlush(&sContext);
}

void memcopy(char *to, char *from, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		to[i] = from[i];
	}
}

void assembly()
{
	int i;
	int j;
	int v;
	char tmp;
	char line[128];
	for(i = 0, j = 0; i < 128 ; i++)
	{
		for(v = 0; v < velocity; v++) {
			if(direction == 0){
				tmp = graphicMemory[i*128 + 127];
				for(j = 0; j < 128; j++) 
				{
					graphicMemory[i*128 +j] ^= tmp;
					tmp ^= graphicMemory[i*128 +j];
					graphicMemory[i*128 +j] ^= tmp;
				}
			} else if (direction == 1){
				tmp = graphicMemory[i*128];
				for(j = 127; j >=0; j--) 
				{
					graphicMemory[i*128 +j] ^= tmp;
					tmp ^= graphicMemory[i*128 +j];
					graphicMemory[i*128 +j] ^= tmp;
				}
			} else if (direction == 2){
				tmp = graphicMemory[i];
				for(j = 127; j >=0; j--) 
				{
					graphicMemory[j*128 +i] ^= tmp;
					tmp ^= graphicMemory[j*128 +i];
					graphicMemory[j*128 +i] ^= tmp;
				}
			} else if (direction == 3){
				tmp = graphicMemory[i+127*128];
				for(j = 0; j <128; j++) 
				{
					graphicMemory[j*128 +i] ^= tmp;
					tmp ^= graphicMemory[j*128 +i];
					graphicMemory[j*128 +i] ^= tmp;
				}
			}
		}
	}
}

void img_to_memory(unsigned char *img)
{
	int i;
	int j = 0;
	
	for(i = 0; i < 128*128; i++) {
		if(i % 128 < 96 && i / 128 < 64) {
			graphicMemory[i] = img[j];
			j++;
		} else {
			graphicMemory[i] = 255;
		}
	}
}

/*----------------------------------------------------------------------------
 *      Main
 *---------------------------------------------------------------------------*/
int main (void) {
	int i,x_img,y_img;
	float temp,lux;
	float mic;
	bool s1_press, s2_press;
	volatile uint16_t x, y;
	uint32_t fore_ground, back_ground;
	int img_type = 0;		//O -> CAR, 1 -> AIRPLANE
	
	velocity = 2;
	direction = 2;
	fore_ground = ClrBlack;
	back_ground = ClrWhite;
	
	//Initializing all peripherals
	init_all();
	img_to_memory(airplane_bin);

  while(1){
		f_asm();
		//assembly();
		GrContextBackgroundSet(&sContext, back_ground);
		GrContextForegroundSet(&sContext, fore_ground);
		for(i = 0; i < 128*128; i++) {
				x_img = i % 128;
				y_img = i /128;
				if(graphicMemory[i] > COLOR_THRESHOLD) {
						GrContextForegroundSet(&sContext, fore_ground);
				} else {
						GrContextForegroundSet(&sContext, back_ground);
				}
				GrPixelDraw(&sContext, x_img, y_img);
			}
	
/*  Joystick		*/		
			x = joy_read_x();
			y = joy_read_y();
			
			if(x > 3000 && velocity < 254) {
				velocity++;
				//while((x = joy_read_x() > 50));
			} else if (x < 1000 && velocity > 1) {
				velocity--;
			}
			
			if(y > 3000) {
				if(direction == 1)
					direction = 0;
				else if(direction == 3)
					direction = 2;
			} else if(y < 1000) {
				if(direction == 0)
					direction = 1;
				else if(direction == 2)
					direction = 3;
			}
	

/*	Botoes 	*/			
			s1_press = button_read_s1();
			s2_press = button_read_s2();
			if(s1_press) {
				fore_ground ^= back_ground;
				back_ground ^= fore_ground;
				fore_ground ^= back_ground;
				while((s1_press = button_read_s1()));
			}
			
			if(s2_press) {
				if(img_type == 0 ){
					img_type = 1;
					if(direction == 2)
						direction = 0;
					else 
						direction = 1;
					img_to_memory(car_bin);
				} else {
					img_type = 0;
					if(direction == 0)
						direction = 2;
					else 
						direction = 3;
					img_to_memory(airplane_bin);
				}
				while((s2_press = button_read_s2()));
			}
	}	
}
