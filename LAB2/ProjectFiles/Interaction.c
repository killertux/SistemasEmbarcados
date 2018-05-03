#include "cmsis_os.h"
#include "Interaction.h"

osThreadId tid_interaction;                            // thread id
osThreadDef (interaction, osPriorityNormal, 1, 0);

int init_interaction() {
    tid_interaction = osThreadCreate(osThread(interaction), NULL);
    if (!tid_interaction) return (-1);
    return 0;
}

void interaction() {
			/*
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
			s1_press = button_read_s1();
			s2_press = button_read_s2();
			if(s1_press)
				road.state = -1;
			if(s2_press)
				road.state = 1;
			if(!s2_press && !s1_press)
				road.state = 0;*/
}
