/*
 * parser.h
 *
 *  Created on: Apr 26, 2024
 *      Author: pedro
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

void pParserFloatToString(unsigned char* ucStringBuffer, float fNumberInput);
void pParserStandardizeNumericInput(unsigned char* cUartMessage, int iMessageMaxSize);
float fParserToFloat(unsigned char* cUartMessage);


#endif /* INC_PARSER_H_ */

