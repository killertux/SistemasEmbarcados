#include "cmsis_os.h"
#include <stdbool.h>
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"
#include <string.h>
#include <stdio.h>
#include "Uart_send.h"
#include "Menu_controller.h"

Menu menu;
tContext sContext;

int blueColorsSize = 18;
unsigned int blueColorsCodes[] = {0x6a5acd, 0x483d8b, 0x191970, 0x000080, 0x00008b, 0x0000cd, 0x0000ff, 0x6495ed, 0x4169e1, 0x1e90ff, 0x00bfff, 0x87cefa, 0x87ceeb, 0xadd8e6, 0x4682b4, 0xb0c4de, 0x708090, 0x778899};
char blueColorsNames[][30] = {"Slate Blue", "Dark Slate Blue", "Midnight Blue", "Navy", "Dark Blue", "Medium Blue", "Blue", "Cornflower Blue", "Royal Blue", "Dodger Blue", "Deep Sky Blue", "Light Sky Blue", "Sky Blue", "Light Blue", "Steel Blue", "Light Steel Blue", "Slate Gray", "Light Slate Gray"};

int greenColorsSize = 20;
unsigned int greenColorsCodes[] = {0x2f4f4f, 0x00fa9a, 0x00ff7f, 0x98fb98, 0x90ee90, 0x8fbc8f, 0x3cb371, 0x2e8b57, 0x006400, 0x008000, 0x228b22, 0x32cd32, 0x00ff00, 0x7cfc00, 0x7fff00, 0xadff2f, 0x9acd32, 0x6b8e23, 0x556b2f, 0x808000};
char greenColorsNames[][30] = {"Dark Slate Gray", "Medium Spring Green", "Spring Green", "Pale Green", "Light Green", "Dark Sea Green", "Medium Sea Green", "Sea Green", "Dark Green", "Green", "Forest Green", "Lime Green", "Lime", "Lawn Green", "Chartreuse", "Green Yellow", "Yellow Green", "Olive Drab", "Dark Olive Green", "Olive"};

int brownColorsSize = 13;
unsigned int brownColorsCodes[] = {0xbdb76b, 0xdaa520, 0xb8860b, 0x8b4513, 0xa0522d, 0xbc8f8f, 0xcd853f, 0xd2691e, 0xf4a460, 0xffdead, 0xf5deb3, 0xdeb887, 0xd2b48c};
char brownColorsNames[][30] = {"Dark Khaki", "Goldenrod", "Dark Goldenrod", "Saddle Brown", "Sienna", "Rosy Brown", "Peru", "Chocolate", "Sandy Brown", "Navajo White", "Wheat", "Burly Wood", "Tan"};

int purpleColorsSize = 13;
unsigned int purpleColorsCodes[] = {0x7b68ee, 0x9370db, 0x8a2be2, 0x4b0082, 0x9400d3, 0x9932cc, 0xba55d3, 0x800080, 0x8b008b, 0xff00ff, 0xee82ee, 0xda70d6, 0xdda0dd};
char purpleColorsNames[][30] = {"Medium Slate Blue", "Medium Purple", "Blue Violet", "Indigo", "Dark Violet", "Dark Orchid", "Medium Orchid", "Purple", "Dark Magenta", "Fuchsia", "Violet", "Orchid", "Plum"};

int cyanColorsSize = 10;
unsigned int cyanColorsCodes[] = {0x00ffff, 0x00ced1, 0x40e0d0, 0x48d1cc, 0x20b2aa, 0x008b8b, 0x008080, 0x7fffd4, 0x66cdaa, 0x5f9ea0};
char cyanColorsNames[][30] = {"Cyan", "Dark Turquoise", "Turquoise", "Medium Turquoise", "Light Sea Green", "Dark Cyan", "Teal", "Aquamarine", "Medium Aquamarine", "Cadet Blue"};

int pinkColorsSize = 9;
unsigned int pinkColorsCodes[] = {0xc71585, 0xff1493, 0xff69b4, 0xdb7093, 0xffb6c1, 0xffc0cb, 0xf08080, 0xcd5c5c, 0xdc143c};
char pinkColorsNames[][30] = {"Medium Violet Red", "Deep Pink", "Hot Pink", "Pale Violet Red", "Light Pink", "Pink", "Light Coral", "Indian Red", "Crimson"};

int orangeColorsSize = 3;
unsigned int orangeColorsCodes[] = {0xff4500, 0xff8c00, 0xffbc00};
char orangeColorsNames[][30] = {"Orange Red", "Dark Orange", "Orange"};

int redColorsSize = 10;
unsigned int redColorsCodes[] = {0x800000, 0x8b0000, 0xb22222, 0xa52a2a, 0xfab072, 0xe9967a, 0xffa07a, 0xff7f50, 0xff6347, 0xff0000};
char redColorsNames[][30] = {"Maroon", "Dark Red", "Fire Brick", "Brown", "Salmon", "Dark Salmon", "Light Salmon", "Coral", "Tomato", "Red"};

int yellowColorsSize = 3;
unsigned int yellowColorsCodes[] = {0xffd700, 0xffff00, 0xf0e68c};
char yellowColorsNames[][30] = {"Gold", "Yellow", "Khaki"};

void menu_init(Menu *menu){
	int i;
	menu->colorGroupPosition = 0;
	menu->colorPosition = 0;
	
	cfaf128x128x16Init();
	GrContextInit(&sContext, &g_sCfaf128x128x16);
	GrContextFontSet(&sContext, g_psFontFixed6x8);

	//Blue Group
	strcpy(menu->groups[0].name, "Blue Colors");
	menu->groups[0].size = blueColorsSize;
	menu->groups[0].codes = blueColorsCodes;
	for(i = 0; i < blueColorsSize; i++)
		menu->groups[0].names[i] = blueColorsNames[i];

	//Green Group
	strcpy(menu->groups[1].name, "Green Colors");
	menu->groups[1].size = greenColorsSize;
	menu->groups[1].codes = greenColorsCodes;
	for(i = 0; i < greenColorsSize; i++)
		menu->groups[1].names[i] = greenColorsNames[i];

	//Brown Group
	strcpy(menu->groups[2].name, "Brown Colors");
	menu->groups[2].size = brownColorsSize;
	menu->groups[2].codes = brownColorsCodes;
	for(i = 0; i < brownColorsSize; i++)
		menu->groups[2].names[i] = brownColorsNames[i];

	//Purple Group
	strcpy(menu->groups[3].name, "Purple Colors");
	menu->groups[3].size = purpleColorsSize;
	menu->groups[3].codes = purpleColorsCodes;
	for(i = 0; i < purpleColorsSize; i++)
		menu->groups[3].names[i] = purpleColorsNames[i];

	//Cyan Group
	strcpy(menu->groups[4].name, "Cyan Colors");
	menu->groups[4].size = cyanColorsSize;
	menu->groups[4].codes = cyanColorsCodes;
	for(i = 0; i < cyanColorsSize; i++)
		menu->groups[4].names[i] = cyanColorsNames[i];

	//Pink Group
	strcpy(menu->groups[5].name, "Pink Colors");
	menu->groups[5].size = pinkColorsSize;
	menu->groups[5].codes = pinkColorsCodes;
	for(i = 0; i < pinkColorsSize; i++)
		menu->groups[5].names[i] = pinkColorsNames[i];

	//Orange Group
	strcpy(menu->groups[6].name, "Orange Colors");
	menu->groups[6].size = orangeColorsSize;
	menu->groups[6].codes = orangeColorsCodes;
	for(i = 0; i < orangeColorsSize; i++)
		menu->groups[6].names[i] = orangeColorsNames[i];

	//Red Group
	strcpy(menu->groups[7].name, "Red Colors");
	menu->groups[7].size = redColorsSize;
	menu->groups[7].codes = redColorsCodes;
	for(i = 0; i < redColorsSize; i++)
		menu->groups[7].names[i] = redColorsNames[i];

	//Yellow Group
	strcpy(menu->groups[8].name, "Yellow Colors");
	menu->groups[8].size = yellowColorsSize;
	menu->groups[8].codes = yellowColorsCodes;
	for(i = 0; i < yellowColorsSize; i++)
		menu->groups[8].names[i] = yellowColorsNames[i];
};


osThreadDef (menu_controller, osPriorityNormal, 1, 0);

MENU_CONTROLLER_IDS menu_ids;

osThreadId init_menu_controller(osMessageQId menu_controller_msg_queue_id,															
																osMessageQId red_led_msg_id,
																osMessageQId green_led_msg_id,
																osMessageQId blue_led_msg_id,
																osMailQId UART_send_id) {
		osThreadId tid_menu_controller; 

		menu_ids.blue_led_msg_id = blue_led_msg_id;
		menu_ids.green_led_msg_id = green_led_msg_id;
		menu_ids.red_led_msg_id = red_led_msg_id;
		menu_ids.menu_controller_msg_queue_id = menu_controller_msg_queue_id;
		menu_ids.UART_send_id = UART_send_id;
    menu_init(&menu);																	
																	
    tid_menu_controller = osThreadCreate(osThread(menu_controller), NULL);
    if (!tid_menu_controller) return (osThreadId) (-1);
    return tid_menu_controller;
}

void menu_controller() {
	osStatus status;
	osEvent evt;
	char msg;
	draw_menu();
	sendMessages();
  while (1) {
    ; // Insert thread code here...
    evt = osMessageGet (menu_ids.menu_controller_msg_queue_id, osWaitForever); 
    // wait for message
 
    if (evt.status == osEventMessage) {
      char r, g, b;
			msg = evt.value.v;
			
			if(msg == 'w') {
				menu.colorPosition--;
				if(menu.colorPosition < 0)
					menu.colorPosition = menu.groups[menu.colorGroupPosition].size - 1;
			} else if(msg == 's') {
				menu.colorPosition++;
				if(menu.colorPosition == menu.groups[menu.colorGroupPosition].size)
					menu.colorPosition = 0;
			} else if(msg == 'a') {
				menu.colorGroupPosition--;
				menu.colorPosition = 0;
				if(menu.colorGroupPosition < 0)
					menu.colorGroupPosition = 8;
			} else if(msg == 'd') {
				menu.colorGroupPosition++;
				menu.colorPosition = 0;
				if(menu.colorGroupPosition == 9)
					menu.colorGroupPosition = 0;
			}
			
			draw_menu();
			sendMessages();
			
			//TODO: Send back to serial
    }
  }
}

void draw_menu(){
	int i, position, c;
	int showSize = 6;
	char buffer[30];
	GrContextBackgroundSet(&sContext, 0x000000);
	GrContextForegroundSet(&sContext, 0xffffff);
	GrStringDraw(&sContext, menu.groups[menu.colorGroupPosition].name, -1, 0, 0, true);
	
	if(menu.groups[menu.colorGroupPosition].size < 13) {
		showSize = menu.groups[menu.colorGroupPosition].size /2;
		position = (showSize *2 + 1) + 1; 
		for(i = 0; i < 13 - (showSize *2 + 1); i++) {
			position++;
			GrStringDraw(&sContext, "                    ", -1, 0, position * 8, true);
		}
	}
	position = 1;
	for(i = menu.colorPosition-showSize; i <= menu.colorPosition + showSize; i++) {
		int j;
		if(i < 0)
			j = menu.groups[menu.colorGroupPosition].size + i;
		else if (i >= menu.groups[menu.colorGroupPosition].size)
			j = i - menu.groups[menu.colorGroupPosition].size;
		else
			j = i;
		position++;
		if(i == menu.colorPosition) {
				GrContextBackgroundSet(&sContext, menu.groups[menu.colorGroupPosition].codes[j]);
				GrContextForegroundSet(&sContext, 0x000000);
		} else {
				GrContextBackgroundSet(&sContext, 0x000000);
				GrContextForegroundSet(&sContext,  menu.groups[menu.colorGroupPosition].codes[j]);
		}
		strcpy(buffer, menu.groups[menu.colorGroupPosition].names[j]);
		for(c = strlen(buffer); c < 20; c++) {
			sprintf(buffer, "%s ", buffer);
		}
		GrStringDraw(&sContext, buffer, -1, 0, position * 8, true);
	}
}

void uart_send(osMailQId qid_MailQueue) {
		MAILQUEUE_OBJ_t *pMail = 0;
		int i;
	
    ; // Insert thread code here...
    pMail = osMailAlloc (qid_MailQueue, osWaitForever);         
    // Allocate memory
 
		strcpy(pMail->name, menu.groups[menu.colorGroupPosition].name);
		for (i = 0; i < menu.groups[menu.colorGroupPosition].size; i++){
			pMail->screen[i] = menu.groups[menu.colorGroupPosition].names[i];
		}
		
		pMail->position = menu.colorPosition;
		pMail->size = menu.groups[menu.colorGroupPosition].size;
		
		osMailPut (qid_MailQueue, pMail);                         
		// Send Mail
 
    osThreadYield ();                                           
    // suspend thread
}

void clearScreen() {
	int x, y;
	GrContextBackgroundSet(&sContext, 0x000000);
	GrContextForegroundSet(&sContext, 0x000000);
	
	for (x = 0; x < 128; x++){
		for (y = 8; y < 120; y++) {
			GrPixelDraw(&sContext, x, y);
		}
	}
}

void sendMessages() {
		char r, g, b;
		r = (menu.groups[menu.colorGroupPosition].codes[menu.colorPosition] & 0x00ff0000) >> 2 * 8;
		g = (menu.groups[menu.colorGroupPosition].codes[menu.colorPosition] & 0x0000ff00) >> 1 * 8;
		b = (menu.groups[menu.colorGroupPosition].codes[menu.colorPosition] & 0x000000ff);
		osMessagePut(menu_ids.red_led_msg_id, r, osWaitForever);
		osMessagePut(menu_ids.green_led_msg_id, g, osWaitForever);
		osMessagePut(menu_ids.blue_led_msg_id, b, osWaitForever);
		uart_send(menu_ids.UART_send_id);
}
	