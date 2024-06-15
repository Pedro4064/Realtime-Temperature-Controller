#include "application.h"
#include "parser.h"
#include "lcd.h"

#define RESET_BTN_STATUS(btn) btn = NOT_PRESSED

typedef enum {
    INITIAL_SCREEN,
    DATA_SCREEN_1,
    DATA_SCREEN_2,
    DATA_SCREEN_3,
    CONFIG_SCREEN_1,
    CONFIG_SCREEN_2,
    CONFIG_SCREEN_3
} screenState;

static screenState xCurrentState;
static applicationParameters* pApplicationParameters;

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

    }

}

void vDataScreen1Handle(){
    // Write to Screen
    vLcdSetCursor(0,0);
    vLcdWriteString("T.at:");
    vLcdSetCursor(0,5);
    vParserFloatToString(ucLcdScreenString[0], pApplicationParameters->tempMgtCtl.fTemperatureCurrent);
    vLcdWriteString(ucLcdScreenString[0]);


    vLcdSetCursor(1,0);
    vLcdWriteString("T.ds:");
    vLcdSetCursor(1,5);
    vParserFloatToString(ucLcdScreenString[1], pApplicationParameters->tempMgtCtl.fTemperatureTarget);
    vLcdWriteString(ucLcdScreenString[1]);

    // Update the state depending on buttons states 
    if(pApplicationParameters->appButtons.discreteMapping.xDownBtn == PRESSED){
        xCurrentState = DATA_SCREEN_2;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xDownBtn);
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xUpBtn == PRESSED){
        xCurrentState = DATA_SCREEN_3;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xUpBtn);
    }
    else if(pApplicationParameters->appButtons.discreteMapping.xCenterBtn == LONG_PRESSED){
        xCurrentState = CONFIG_SCREEN_1;
        RESET_BTN_STATUS(pApplicationParameters->appButtons.discreteMapping.xCenterBtn);

    }

}
void vDataScreen2Handle(){}
void vDataScreen3Handle(){}

void vConfigScreen1Handle(){}
void vConfigScreen2Handle(){}
void vConfigScreen3Handle(){}

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
        
        default:
            break;
    }

}
