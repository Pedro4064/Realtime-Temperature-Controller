/*
 * parser.h
 *
 *  Created on: Apr 26, 2024
 *      Author: pedro
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_


// ********************************************************** //
// Method name:        pParserFloatToString                   //
// Method description: Transform   float  value  to  string   //
//                     representation                         //
// Input params:       ucStringBuffer                         //
//                        Parameter  that receives the string //
//                        representation                      //
//                     fNumberInput                           //
//                        Float number converted to string    //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void pParserFloatToString(unsigned char* ucStringBuffer, float fNumberInput);

// ********************************************************** //
// Method name:        pParserStandardizeNumericInput         //
// Method description: Converts    the    numeric    value,   //
//                     represented  as  a  string,  to have   //
//                     three  decimal  places  and replaces   //
//                     comma with period                      //
// Input params:       cUartMessage                           //
//                        UART message received as input      //
//                     iMessageMaxSize                        //
//                        Max  number  of  the  elements of a //
//                        message                             //
// Output params:      void                                   //
//                        N/A                                 //
// ********************************************************** //
void pParserStandardizeNumericInput(unsigned char* cUartMessage, int iMessageMaxSize);

// ********************************************************** //
// Method name:        fParserToFloat                         //
// Method description: Converts  the  string representation   //
//                     into a float value                     //
// Input params:       cUartMessage                           //
//                        Numeric   value  represented  as  a //
//                        string                              //
// Output params:      float                                  //
//                        Numeric  value  converted  to float //
//                        type                                //
// ********************************************************** //
float fParserToFloat(unsigned char* cUartMessage);


#endif /* INC_PARSER_H_ */

