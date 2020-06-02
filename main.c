#include "main.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "uart.h"
#include "room.h"
#include "KeyPad.h"
#include "lcd.h"
#include "gpio.h"

uint32_t passwords[TOTAL_ROOMS];
uint32_t status[TOTAL_ROOMS + 1];

int main(){
	uint8_t data = 0;									// buffer to store current values
	uint8_t currentRoomNum = 1;				// Stores room required to change pw, open, etc
	uint32_t i;												// loop iterator
	UART_Init(UART1, UART_BAUD_2400);	// Initializing communication with UART1
	Keypad_init();										// Initializing The Keypad
	LCD_init();												// Initializing The LCD
	LCD_writeCommand(CLEAR);					// CLEAR the LCD to write
	LCD_writeString("+ to Open Door");
	GPIO_initPin(PORTF, OPEN_DOOR_PIN, DIGITAL, OUTPUT);	// Initializing the door pin
	getRooms();												// Reading the rooms from the flash or initializing it if first time
	while(1){
		// Reading command from the UART and processing it
		data = UART_readChar(UART1);
		switch(data){
			case SET_NUM:
				currentRoomNum = UART_readChar(UART1);
				break;
			case SET_STATUS:
				status[currentRoomNum - 1] = UART_readChar(UART1);
				break;
			case SET_PASSWORD:
				passwords[currentRoomNum - 1] = UART_readChar(UART1);
				break;
			case SAVE_DATA:
				saveRooms();
				break;
			case OPEN_DOOR:
				// Reading Keypad password
				data = keypad_getkey();
				switch(data){
					case OPEN_DOOR_BUTTON:
						data = 0;
						for(i = 0; i < 4; i++){
							data += keypad_getkey() << i * 8;
						}
						if(data == passwords[currentRoomNum]){
							GPIO_writePin(PORTF, OPEN_DOOR_PIN, HIGH);
							delayMs(3000);
							GPIO_writePin(PORTF, OPEN_DOOR_PIN, LOW);
						}
						break;
				}
		}
		
	}
}
