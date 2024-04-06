/*
 * matrixKeyboard.h
 *
 *  Created on: Apr 5, 2024
 *      Author: ES670 B
 */

#ifndef INC_MATRIXKEYBOARD_H_
#define INC_MATRIXKEYBOARD_H_

typedef enum{
	HIGH,
	LOW
}KeyStatus;

typedef struct{
	char cOne;
	char cTwo;
	char cThree;
	char cA;

	char cFour;
	char cFive;
	char cSix;
	char cB;

	char cSeven;
	char cEight;
	char cNine;
	char cC;

	char cAsterisk;
	char cZero;
	char cHashtag;
	char cD;
}KeyboardMapping;

typedef union{
	KeyboardMapping xKeyboard;
	char cKeayboardValues[4][4];
}MatrixKeyboard;

//MatrixKeyboard matrix_keyboard;
//matrix_keyboard.xKeyboard.cB;
//matrix_keyboard.cKeayboardValues[1][3]

#endif /* INC_MATRIXKEYBOARD_H_ */
