/* ***************************************************************** */
/* File name:		 lcd_hal.c							 			 */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*					 controller										 */
/* Author name:      dloubach										 */
/* Creation date:    16out2015										 */
/* Revision date:    03apr2023                                       */
/* ***************************************************************** */

#include <main.h>
#include <i2c.h>
#include "lcd.h"


/* line and columns */
#define LINE0		0U
#define COLUMN0		0U

#define L0C0_BASE	0x80 /* line 0, column 0 */
#define L1C0_BASE	0xC0 /* line 1, column 0 */
#define MAX_COLUMN  15U

static lcdConfig* pLcdConfiguration;
static char cBacklightStatus;

// Function with local scope
static void vLcdWrite2Lcd(unsigned char ucBuffer,  unsigned char cDataType);

/* ************************************************ */
/* Method name:        vLcdInitLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:      *hi2c=>pointer to the i2c    */
/*                     addrress=>LCD I2C address    */
/* ************************************************ */
void vLcdInitLcd(lcdConfig* lcdConfiguration)
{
	pLcdConfiguration = lcdConfiguration;

	unsigned char ucTemp = 0;

	// Time to the LCD's microcontroller start
	HAL_Delay(20);

	// set LCD to 4-bit mode
	ucTemp = 0x20 | LCD_BIT_E;
	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucTemp, 1);
	HAL_Delay(1);
	ucTemp = 0x20;
	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucTemp, 1);
	HAL_Delay(2);

	// turn-on LCD, with data length 4, 2 lines, character 5x8 */
	vLcdSendCommand(CMD_INIT_CONFIG);

	// init LCD
	vLcdSendCommand(CMD_LCDON_CURSOROFF);

	// clear LCD
	vLcdSendCommand(CMD_CLEAR);
}


/* ************************************************ */
/* Method name:        vLcdWriteData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdWriteData(unsigned char ucData)
{
	/* just a relay to send data */
	vLcdWrite2Lcd(ucData, LCD_RS_DATA);
}


/* ************************************************ */
/* Method name:        vLcdSendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdSendCommand(unsigned char ucCmd)
{
	/* just a relay to send command */
	vLcdWrite2Lcd(ucCmd, LCD_RS_CMD);
}


/* ************************************************ */
/* Method name:        vLcdSetCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdSetCursor(unsigned char cLine, unsigned char cColumn)
{
	char cCommand;

	if(LINE0 == cLine)
		/* line 0 */
		cCommand = L0C0_BASE;
	else
		/* line 1 */
		cCommand = L1C0_BASE;

	/* maximum MAX_COLUMN columns */
	cCommand += (cColumn & MAX_COLUMN);

	// send the command to set the cursor
	vLcdSendCommand(cCommand);
}

/* ************************************************ */
/* Method name:        vLcdWriteString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdWriteString(const char *cBuffer)
{
	while(*cBuffer)
	{
		vLcdWriteData(*cBuffer++);
	};
}

void vLcdWriteBuffer(unsigned char *ucBuffer)
{
	while(*ucBuffer)
	{
		vLcdWriteData(*ucBuffer++);
	};
}


/* ************************************************ */
/* Method name:        vLCDDummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void vLcdDummyText(void)
{
	// clear LCD
	vLcdSendCommand(CMD_CLEAR);

	// set the cursor line 0, column 1
	vLcdSetCursor(0,1);

	// send string
	vLcdWriteString("*** ES670 ***");

	// set the cursor line 1, column 0
	vLcdSetCursor(1,0);
	vLcdWriteString("Prj Sis Embarcad");
}

void vLcdBacklightON(){
	cBacklightStatus = 1;
}

void vLcdBacklightOFF(){
	cBacklightStatus = 0;
}

/* ************************************************ */
/* Method name: 	   vLcdWrite2Lcd         		*/
/* Method description: Send command or data to LCD  */
/* Input params:	   ucBuffer => byte to be send  */
/*                   cDataType => command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA          */
/* Output params:	   n/a 							*/
/* ************************************************ */
static void vLcdWrite2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
	// cDataType indica se deve ser enviado um dado ou um comando ao display
	// Se cDataType for igual a LCD_RS_CMD, deve ser enviado um comando (Pino RS do display em nível baixo)
	// Se cDataType for igual a LCD_RS_DATA, deve ser enviado um dado (Pino RS do display em nível alto)
	unsigned char ucDataPackage = ucBuffer;

	switch (cDataType)
	{
	case LCD_RS_CMD:
		// Send first 4 MSB plus the enable signal
		ucDataPackage = (ucDataPackage & 0xF0) | (SIG_ENABLE | cBacklightStatus << 3);
	 	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(1);

		// Pull down enable pin 
		ucDataPackage &= ~SIG_ENABLE;
	 	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(2);

		// Send Last 4 LSB plus enable signal
		ucDataPackage = (ucBuffer << 4) | (SIG_ENABLE | cBacklightStatus << 3);
		HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(1);

		// Pull down enable pin 
		ucDataPackage &= ~SIG_ENABLE;
	 	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(2);
		break;
	
	case LCD_RS_DATA:
		// First set the cursor shift functionality, which automatically increments the cursor one to the left after
		// a write operation to the DDRAM
//		vLcdSendCommand(0b00000110);

		// Send the first 4 MSB plus the enable signal, the RS as write data and the backlight
		ucDataPackage = (ucBuffer & 0xF0) | (SIG_ENABLE | SIG_DATA_W | cBacklightStatus << 3);
		HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(1);

		// Pull down enable pin 
		ucDataPackage &= ~SIG_ENABLE;
	 	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(2);

		// Send Last 4 LSB plus enable signal
		ucDataPackage = (ucBuffer << 4) | (SIG_ENABLE | SIG_DATA_W | cBacklightStatus << 3);
		HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(1);

		// Pull down enable pin 
		ucDataPackage &= ~SIG_ENABLE;
	 	HAL_I2C_Master_Transmit_IT(pLcdConfiguration->pHi2c, pLcdConfiguration->cAddress<<1, &ucDataPackage, 1);
		HAL_Delay(2);
		break;

	default:
		break;
	}

	// Vocês irão enviar o byte de dados ou comando em duas etapas
	// Na primeira etapa serão enviados os 4 bits mais significativos
	// Na segunda etapa serão enviados os 4 bits menos significativos
	// Para enviar cada bloco de 4 bits, os dados devem ser colocados nos pinos D4-D7, e deve ser dado
	// um pulso de duração de 1 ms no pino Enable do display, em seguida, o pino Enable deve voltar
	// para nível baixo. Após voltar o pino Enable para nível baixo aguarde 2 ms para enviar os próximos
	// 4 bits.
	// Para escrever um dado ou um comando o pino Write/Read do display deve estar em nível baixo

	// Na escrita vocês podem acender ou desligar o backlight do LCD (P3 do CI PCF8574). Registrem em uma
	// variável global se o backlight deve ficar aceso ou apagado. Essa variável global será atualizada nas
	// funções vLcdBacklighON() e vLcdBacklighOFF()
}
