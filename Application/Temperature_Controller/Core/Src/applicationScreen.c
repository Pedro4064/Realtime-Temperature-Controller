// **********************************************//
// File name:        applicationScreen.c         //
// File description: This file implements the    //
//                   application Screens.        //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 21/Jun/2024                 //
// Revision date:    21/Jun/2024                 //
// **********************************************//


#include "application.h"
#include "parser.h"
#include "lcd.h"

#define CLEAR_SCREEN() vLcdSetCursor(0,0);\
                       vLcdWriteString("                ");\
                       vLcdSetCursor(1,0);\
                       vLcdWriteString("                ")

#define RESET_INPUT_TEMPLATE(x) x[0] = '_';\
                                x[1] = '_';\
                                x[2] = ',';\
                                x[3] = '_';\
                                x[4] = '_'

#define RESET_BTN_STATUS(btn) btn = NOT_PRESSED
#define UPDATE_CURSOR(x) (x+1 == 2)? 3: ((x+1 > 4)? 0 : x+1)
#define IS_NUMERIC(x) (x >= 48 && x<= 57)


typedef enum {
    INITIAL_SCREEN,
    DATA_SCREEN_1,
    DATA_SCREEN_2,
    DATA_SCREEN_3,
    CONFIG_SCREEN_1,
    CONFIG_SCREEN_2,
    CONFIG_SCREEN_3,
    CONFIG_SCREEN_INPUT,
    MAX_VAL_ERROR_SCREEN
} screenState;

static screenState xCurrentState;
static applicationParameters* pApplicationParameters;
static char cConfigParameter;

static unsigned char ucLcdScreenString[2][16];

void vInitialScreenHandle(){
    static unsigned int ucEnterTime;
    unsigned int ucCurrentTime = HAL_GetTick();

    if (ucEnterTime == 0){

        ucEnterTime = ucCurrentTime;

        vLcdSetCursor(0,0);
        vLcdWriteString(" Controlador de ");
        vLcdSetCursor(1,0);
        vLcdWriteString("  Temperatura   ");

        return;
    }

    else if((ucCurrentTime - ucEnterTime) >= 2000){

        xCurrentState = DATA_SCREEN_1;
        CLEAR_SCREEN();

    }

}

void vDataScreen1Handle(){
    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("Temp. At:");
    vLcdSetCursor(0,9);
    vParserFlexibleFloatToString(ucLcdScreenString[0], 16, pApplicationParameters->tempMgtCtl.fTemperatureCurrent, 2, 2 , ',');
    vLcdWriteBuffer(ucLcdScreenString[0]);


    vLcdSetCursor(1,0);
    vLcdWriteString("Temp. Ds:");
    vLcdSetCursor(1,9);
    if(!pApplicationParameters->tempMgtCtl.ucHeatingOn){
        vLcdWriteString("-----");
    }
    else{
        vParserFlexibleFloatToString(ucLcdScreenString[1], 16, pApplicationParameters->tempMgtCtl.fTemperatureTarget, 2, 2 , ',');
        vLcdWriteBuffer(ucLcdScreenString[1]);
    }

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = DATA_SCREEN_2;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = DATA_SCREEN_3;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }

}

void vDataScreen2Handle(){
    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("Vel. C:");
    vLcdSetCursor(0,7);
    vParserFlexibleFloatToString(ucLcdScreenString[0], 16, pApplicationParameters->tempMgtCtl.uiVelocityCooler, 4, 2, ',');
    vLcdWriteBuffer(ucLcdScreenString[0]);

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = DATA_SCREEN_3;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = DATA_SCREEN_1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }
}

void vDataScreen3Handle(){
    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("Kp:");
    vLcdSetCursor(0,3);
    vParserFlexibleFloatToString(ucLcdScreenString[0], 16, pApplicationParameters->tempMgtCtl.fKp, 2, 2, ',');
    vLcdWriteBuffer(ucLcdScreenString[0]);

    vLcdSetCursor(0,8);
    vLcdWriteString("Ki:");
    vLcdSetCursor(0,11);
    vParserFlexibleFloatToString(ucLcdScreenString[0], 16, pApplicationParameters->tempMgtCtl.fKi, 2, 2, ',');
    vLcdWriteBuffer(ucLcdScreenString[0]);

    vLcdSetCursor(1,0);
    vLcdWriteString("Kd:");
    vLcdSetCursor(1,3);
    vParserFlexibleFloatToString(ucLcdScreenString[1], 16, pApplicationParameters->tempMgtCtl.fKd, 2, 2, ',');
    vLcdWriteBuffer(ucLcdScreenString[1]);

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = DATA_SCREEN_1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = DATA_SCREEN_2;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }
}

void vConfigScreen1Handle(){
    // Clear the buffer queue to avoid skipping any screen options due to old user input
    static char cFirstRendering = 1;
    if(cFirstRendering){
        vQueueClear(&pApplicationParameters->xKeyboardQueue);
        cFirstRendering = 0;
    }

    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("**Configuracao**");

    vLcdSetCursor(1,0);
    vLcdWriteString("1-Temp. Desejada");

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_2;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_3;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = DATA_SCREEN_1;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }
    else if(cQueueGet(&pApplicationParameters->xKeyboardQueue) == '1'){
        xCurrentState = CONFIG_SCREEN_INPUT;
        cConfigParameter = '1';
        cFirstRendering = 1;
        CLEAR_SCREEN();
    }

}

void vConfigScreen2Handle(){
    // Clear the buffer queue to avoid skipping any screen options due to old user input
    static char cFirstRendering = 1;
    if(cFirstRendering){
        vQueueClear(&pApplicationParameters->xKeyboardQueue);
        cFirstRendering = 0;
    }

    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("2-Kp");

    vLcdSetCursor(1,0);
    vLcdWriteString("3-Ki");

    // Update the state depending on buttons states 
    char cKeyboardInput = cQueueGet(&pApplicationParameters->xKeyboardQueue);

    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_3;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = DATA_SCREEN_1;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }
    else if(cKeyboardInput == '2'){
        xCurrentState = CONFIG_SCREEN_INPUT;
        cConfigParameter = '2';
        cFirstRendering = 1;
        CLEAR_SCREEN();
    }
    else if(cKeyboardInput == '3'){
        xCurrentState = CONFIG_SCREEN_INPUT;
        cConfigParameter = '3';
        cFirstRendering = 1;
        CLEAR_SCREEN();
    }

}

void vConfigScreen3Handle(){
    // Clear the buffer queue to avoid skipping any screen options due to old user input
    static char cFirstRendering = 1;
    if(cFirstRendering){
        vQueueClear(&pApplicationParameters->xKeyboardQueue);
        cFirstRendering = 0;
    }

    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("4-Kd");

    vLcdSetCursor(1,0);
    if(!pApplicationParameters->tempMgtCtl.ucHeatingOn)
        vLcdWriteString("5-Heater Off");
    else
        vLcdWriteString("5-Heater  On");



    // Update the state depending on buttons states 
    char cKeyboardInput = cQueueGet(&pApplicationParameters->xKeyboardQueue);
    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_2;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
        CLEAR_SCREEN();
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = DATA_SCREEN_1;
        cFirstRendering = 1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }
    else if(cKeyboardInput == '4'){
        xCurrentState = CONFIG_SCREEN_INPUT;
        cConfigParameter = '4';
        cFirstRendering = 1;
        CLEAR_SCREEN();
    }
    else if(cKeyboardInput == '5'){
        cFirstRendering = 1;
        pApplicationParameters->tempMgtCtl.ucHeatingOn = !pApplicationParameters->tempMgtCtl.ucHeatingOn;
    }

}

void vConfigScreenInputHandle(){

    // Clear the buffer queue to avoid skipping any screen options due to old user input the first time
    static char cFirstRendering = 1;
    static char cBlinkStatus;
    static char cIsComplete;
    if(cFirstRendering){
        vQueueClear(&pApplicationParameters->xKeyboardQueue);
        cFirstRendering = 0;
    }

    // Create input buffer for the data
    static unsigned char ucUserInput[5] = {'_', '_', ',', '_', '_'};
    static int iCursorPosition = 0;

    // Blink the cursor until user inputs information
    ucUserInput[iCursorPosition] = (++cBlinkStatus%4 == 0)? ' ': '_';

    // If any keys were pressed and add to user input until user input is full
    if(!cQueueIsEmpty(&pApplicationParameters->xKeyboardQueue) && iCursorPosition <= 4){
        char cInput = cQueueGet(&pApplicationParameters->xKeyboardQueue);

        cIsComplete = (iCursorPosition == 4)? 1 : 0;
        ucUserInput[iCursorPosition] = IS_NUMERIC(cInput)? cInput : ucUserInput[iCursorPosition];
        iCursorPosition = IS_NUMERIC(cInput)? UPDATE_CURSOR(iCursorPosition) : iCursorPosition;
    }   


    // Parse and Save User input when full and Print to Screen the correct information
    switch (cConfigParameter)
    {
        case '1':
            
            // When full, convert the value to float and save it to the configuration parameters
            if(cIsComplete){
                float fConvertedValue = fParserToFloat(ucUserInput, 5);

                if(fConvertedValue <= 90){
                    pApplicationParameters->tempMgtCtl.fTemperatureTarget = fConvertedValue;
                    pApplicationParameters->buzzerInterface.cPlay = 1;
                    xCurrentState = CONFIG_SCREEN_1;
                }
                else{
                    CLEAR_SCREEN();
                    xCurrentState = MAX_VAL_ERROR_SCREEN;
                }

                // Reset input dialog configurations for next config user interaction
                RESET_INPUT_TEMPLATE(ucUserInput);
                cFirstRendering = 1;
                iCursorPosition = 0;
                cIsComplete = 0;
            }

            // Print to screen
            vLcdSetCursor(0,0);
            vLcdWriteString("Temp. Desejada");
            vLcdSetCursor(1,0);
            vLcdWriteBuffer(ucUserInput);

            break;

        case '2':
            // When full, convert the value to float and save it to the configuration parameters
            if(cIsComplete){
                float fConvertedValue = fParserToFloat(ucUserInput, 5);
                pApplicationParameters->tempMgtCtl.fKp = fConvertedValue;
                pApplicationParameters->tempMgtCtl.cPidConfigChanged = 1;
                pApplicationParameters->buzzerInterface.cPlay = 1;
                xCurrentState = CONFIG_SCREEN_1;

                // Reset input dialog configurations for next config user interaction
                RESET_INPUT_TEMPLATE(ucUserInput);
                cFirstRendering = 1;
                iCursorPosition = 0;
                cIsComplete = 0;
            }

            // Print to screen
            vLcdSetCursor(0,0);
            vLcdWriteString("PID - Kp:");
            vLcdSetCursor(1,0);
            vLcdWriteBuffer(ucUserInput);

            break;

        case '3':
            // When full, convert the value to float and save it to the configuration parameters
            if(cIsComplete){
                float fConvertedValue = fParserToFloat(ucUserInput, 5);
                pApplicationParameters->tempMgtCtl.fKi = fConvertedValue;
                pApplicationParameters->tempMgtCtl.cPidConfigChanged = 1;
                pApplicationParameters->buzzerInterface.cPlay = 1;
                xCurrentState = CONFIG_SCREEN_1;

                // Reset input dialog configurations for next config user interaction
                RESET_INPUT_TEMPLATE(ucUserInput);
                cFirstRendering = 1;
                iCursorPosition = 0;
                cIsComplete = 0;
            }

            // Print to screen
            vLcdSetCursor(0,0);
            vLcdWriteString("PID - Ki:");
            vLcdSetCursor(1,0);
            vLcdWriteBuffer(ucUserInput);

            break;

        case '4':
            // When full, convert the value to float and save it to the configuration parameters
            if(cIsComplete){
                float fConvertedValue = fParserToFloat(ucUserInput, 5);
                pApplicationParameters->tempMgtCtl.fKd = fConvertedValue;
                pApplicationParameters->tempMgtCtl.cPidConfigChanged = 1;
                pApplicationParameters->buzzerInterface.cPlay = 1;
                xCurrentState = CONFIG_SCREEN_1;

                // Reset input dialog configurations for next config user interaction
                RESET_INPUT_TEMPLATE(ucUserInput);
                cFirstRendering = 1;
                iCursorPosition = 0;
                cIsComplete = 0;
            }

            // Print to screen
            vLcdSetCursor(0,0);
            vLcdWriteString("PID - Kd:");
            vLcdSetCursor(1,0);
            vLcdWriteBuffer(ucUserInput);

            break;
        
        default:
            break;
    }

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        cFirstRendering = 1;
        iCursorPosition = 0;

        RESET_INPUT_TEMPLATE(ucUserInput);
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);
        CLEAR_SCREEN();
    }

}

void vMaxValueExceededScreenHandle(){
    static unsigned int ucEnterTime;
    unsigned int ucCurrentTime = HAL_GetTick();

    if (ucEnterTime == 0){

        ucEnterTime = ucCurrentTime;

        vLcdSetCursor(0,0);
        vLcdWriteString("Max Ultrapassado");
        vLcdSetCursor(1,0);
        vLcdWriteString("Verifique Manual");

        return;
    }
    else if((ucCurrentTime - ucEnterTime) >= 2000){

        xCurrentState = CONFIG_SCREEN_INPUT;
        ucEnterTime = 0;
        CLEAR_SCREEN();

    }

}

void vApplicationScreenInit(lcdConfig* pLcdConfiguration, applicationParameters* pAppParam){

    xCurrentState = INITIAL_SCREEN;
    pApplicationParameters = pAppParam;

	vLcdInitLcd(pLcdConfiguration);
	vLcdBacklightON();
}

void vApplicationScreenUpdate(){
    switch (xCurrentState)
    {
        case INITIAL_SCREEN:
            vInitialScreenHandle();
            break;

        case DATA_SCREEN_1:
            vDataScreen1Handle();
            break;

        case DATA_SCREEN_2:
            vDataScreen2Handle();
            break;

        case DATA_SCREEN_3:
            vDataScreen3Handle();
            break;

        
        case CONFIG_SCREEN_1:
            vConfigScreen1Handle();
            break;

        case CONFIG_SCREEN_2:
            vConfigScreen2Handle();
            break;

        case CONFIG_SCREEN_3:
            vConfigScreen3Handle();
            break;

        case CONFIG_SCREEN_INPUT:
            vConfigScreenInputHandle();
            break;

        case MAX_VAL_ERROR_SCREEN:
            vMaxValueExceededScreenHandle();
            break;
        
        default:
            break;
    }

}
