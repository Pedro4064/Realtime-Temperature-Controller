// **********************************************//
// File name:        parser.c                    //
// File description: Implementation file 		 //
//					 containing parser functions //
//					 for converting parameter    //
//					 values between string and   //
//					 float formats, ensuring 	 //
//					 standardized formatting.	 //
//                   parser.                     //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 19/Abr/2024                 //
// Revision date:    26/Abr/2024                 //
// **********************************************//

#include <stdlib.h>
#include <math.h>

#define MIN_VAL(x, y) (x>y)? y : x
#define WHOLE_DIGIT_EXTRACT(x,y) (int)((fmod(fabs(y), pow(10,x))) / pow(10,(x-1)))
#define DECIMAL_DIGIT_EXTRACT(x,y) (int)(fmod(fabs(y) * pow(10,x), 10))


void vParserStandardizeNumericInput(unsigned char* cUartMessage, int iMessageMaxSize){
	int iCommaPosition = -1;

	for(int iIndex = 0; iIndex <=iMessageMaxSize; iIndex++ ){
			if(cUartMessage[iIndex] == ','){
				iCommaPosition = iIndex;
				break;
			}
		}

	//if there is a comma
	if(iCommaPosition != -1){
		cUartMessage[iCommaPosition] = '.';
		cUartMessage[MIN_VAL(iCommaPosition+4,iMessageMaxSize)] = '\0';
	}
}

float fParserToFloat(unsigned char* cUartMessage, int iBufferMaxSize){
	vParserStandardizeNumericInput(cUartMessage, iBufferMaxSize);
	return atof(cUartMessage);
}

void vParserFloatToString(unsigned char* ucStringBuffer, float fNumberInput){

	if(fNumberInput<0){
		ucStringBuffer[0] = '-';
		ucStringBuffer++;
	}

	ucStringBuffer[0] = WHOLE_DIGIT_EXTRACT(4,fNumberInput) + 48;
	ucStringBuffer[1] = WHOLE_DIGIT_EXTRACT(3,fNumberInput) + 48;
	ucStringBuffer[2] = WHOLE_DIGIT_EXTRACT(2,fNumberInput) + 48;
	ucStringBuffer[3] = WHOLE_DIGIT_EXTRACT(1,fNumberInput) + 48;
	ucStringBuffer[4] = ',';
	ucStringBuffer[5] = DECIMAL_DIGIT_EXTRACT(1,fNumberInput) + 48;
	ucStringBuffer[6] = DECIMAL_DIGIT_EXTRACT(2,fNumberInput) + 48;
	ucStringBuffer[7] = DECIMAL_DIGIT_EXTRACT(3,fNumberInput) + 48;
	ucStringBuffer[8] = '\n';
	ucStringBuffer[9] = '\r';

}

void vParserFlexibleFloatToString(unsigned char* ucStringBuffer, int iBufferSize, float fNumberInput, int iNumberWholeDigits, int iNumberDecimalDigits, char cDelimiter){
	int iDigitIndex = 0;
	int iDecimalIndex = 1;

	if(fNumberInput<0){
		ucStringBuffer[0] = '-';
		iDigitIndex++;
	}

	for(iDigitIndex; iDigitIndex<iBufferSize; iDigitIndex++){
		if(iNumberWholeDigits > 0){
			ucStringBuffer[iDigitIndex] = WHOLE_DIGIT_EXTRACT(iNumberWholeDigits, fNumberInput) + 48;
			iNumberWholeDigits--;
		}
		else if(iNumberWholeDigits == 0){
			ucStringBuffer[iDigitIndex] = cDelimiter;
			iNumberWholeDigits--;
		}
		else if(iNumberDecimalDigits > 0){
			ucStringBuffer[iDigitIndex] = DECIMAL_DIGIT_EXTRACT(iDecimalIndex, fNumberInput) + 48;
			iNumberDecimalDigits--;
			iDecimalIndex++;
		}
		else{
			ucStringBuffer[iDigitIndex] = '\0';
		}
	}

}