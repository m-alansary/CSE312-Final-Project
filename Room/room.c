#include "room.h"
#include "stdlib.h"
#include "flash.h"
#include "main.h"

extern uint32_t passwords[TOTAL_ROOMS];
extern uint32_t status[TOTAL_ROOMS + 1];

void saveRooms(){
	uint32_t* data = malloc((TOTAL_ROOMS * 2 + 1) * sizeof(uint32_t));
	int i, j;
	for(i = 0, j = 0; i < TOTAL_ROOMS; i++, j+= 2){
		data[j] = passwords[i];
		data[j + 1] = status[i];
	}
	status[i] = 1;
	data[j] = 1;
	FLASH_Write(data, TOTAL_ROOMS * 2 + 1);
}
void getRooms(){
	uint32_t* data = malloc((TOTAL_ROOMS * 2 + 1) * sizeof(uint32_t));
	FLASH_Read(data, TOTAL_ROOMS * 2 + 1);
	if(!data [TOTAL_ROOMS * 2]){
		int i, j;
		for(i = 0, j = 0; i < TOTAL_ROOMS; i++, j+= 2){
			passwords[i] = ('0' << 0) + ('0' << 8) + ('0' << 16) + ('0' << 24); // initialy password is 0000
			status[i] = FREE;	// initially all rooms are free
			data[j] = passwords[i];
			data[j + 1] = status[i];
		}
		status[i] = 1;	// indicates that data is saved
		data[j] = 1;
		FLASH_Write(data, TOTAL_ROOMS * 2 + 1);
	}
	else{
		int i, j;
		for(i = 0, j = 0; i < TOTAL_ROOMS; i++, j+= 2){
			passwords[i] = data[j]; // initialy password is 0000
			status[i] = data[j + 1];	// initially all rooms are free
		}
		status[i] = data[j + 1]; // equals 1 for sure
	}
}


