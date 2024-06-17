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
                                x[3] = '_'

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
    vLcdWriteString(ucLcdScreenString[0]);


    vLcdSetCursor(1,0);
    vLcdWriteString("Temp. Ds:");
    vLcdSetCursor(1,9);
    vParserFlexibleFloatToString(ucLcdScreenString[1], 16, pApplicationParameters->tempMgtCtl.fTemperatureTarget, 2, 2 , ',');
    vLcdWriteString(ucLcdScreenString[1]);

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
    vLcdWriteString(ucLcdScreenString[0]);

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
    vLcdWriteString(ucLcdScreenString[0]);

    vLcdSetCursor(0,8);
    vLcdWriteString("Ki:");
    vLcdSetCursor(0,11);
    vParserFlexibleFloatToString(ucLcdScreenString[0], 16, pApplicationParameters->tempMgtCtl.fKi, 2, 2, ',');
    vLcdWriteString(ucLcdScreenString[0]);

    vLcdSetCursor(1,0);
    vLcdWriteString("Kd:");
    vLcdSetCursor(1,3);
    vParserFlexibleFloatToString(ucLcdScreenString[1], 16, pApplicationParameters->tempMgtCtl.fKd, 2, 2, ',');
    vLcdWriteString(ucLcdScreenString[1]);

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
void vConfigScreen2Handle(){}
void vConfigScreen3Handle(){}
void vConfigScreenInputHandle(){

    // Clear the buffer queue to avoid skipping any screen options due to old user input the first time
    static char cFirstRendering = 1;
    static char cBlinkStatus;
    if(cFirstRendering){
        vQueueClear(&pApplicationParameters->xKeyboardQueue);
        cFirstRendering = 0;
    }

    // Create input buffer for the data
    static char cUserInput[5] = {'_', '_', ',', '_', '_'};
    static int iCursorPosition = 0;

    // Blink the cursor until user inputs information
    cUserInput[iCursorPosition] = (++cBlinkStatus%4 == 0)? ' ': '_';

    // If any keys were pressed and add to user input until user input is full
    if(!cQueueIsEmpty(&pApplicationParameters->xKeyboardQueue) && iCursorPosition <= 4){
        char cInput = cQueueGet(&pApplicationParameters->xKeyboardQueue);

        cUserInput[iCursorPosition] = IS_NUMERIC(cInput)? cInput : cUserInput[iCursorPosition];
        iCursorPosition = IS_NUMERIC(cInput)? UPDATE_CURSOR(iCursorPosition) : iCursorPosition;
    }   


    // Parse and Save User input when full and Print to Screen the correct information
    switch (cConfigParameter)
    {
        case '1':
            
            // When full, convert the value to float and save it to the configuration parameters
            if(iCursorPosition > 4){
                float fConvertedValue = fParserToFloat(cUserInput, 5);

                if(fConvertedValue > 90){
                    CLEAR_SCREEN();
                    RESET_INPUT_TEMPLATE(cUserInput);
                    xCurrentState = MAX_VAL_ERROR_SCREEN;
                    return;
                }

                pApplicationParameters->tempMgtCtl.fTemperatureTarget = fConvertedValue;
            }

            // Print to screen
            vLcdSetCursor(0,0);
            vLcdWriteString("Temp. Desejada");
            vLcdSetCursor(1,0);
            vLcdWriteString(cUserInput);

            break;
        
        default:
            break;
    }

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        cFirstRendering = 1;
        iCursorPosition = 0;

        RESET_INPUT_TEMPLATE(cUserInput);
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

    else if((ucCurrentTime - ucEnterTime) >= 1000){

        xCurrentState = vConfigScreenInputHandle;
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
