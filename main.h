#ifndef MAIN_H
#define MAIN_H

#define TOTAL_ROOMS 			255 // rooms numbered from 1 tp 255

#define OPEN_DOOR_BUTTON 				'D'
#define OPEN_DOOR_PIN						PIN4

typedef enum{
	SET_NUM,
	SET_STATUS,
	SET_PASSWORD,
	FREE,
	OCC,
	CLEAN,
	SAVE_DATA,
	OPEN_DOOR
} COMM;

#endif
