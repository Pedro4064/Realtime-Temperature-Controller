// **********************************************//
// File name:        parser.h                    //
// File description: This file declare functions //
//                   interface and data types for//
//                   parser.                     //
// Author name:		 Isabelle Miki Ikuno         //
//                   Pedro Henrique L. da Cruz   //
// Creation date:	 19/Abr/2024                 //
// Revision date:    26/Abr/2024                 //
// **********************************************//


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
void vParserFloatToString(unsigned char* ucStringBuffer, float fNumberInput);

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
void vParserStandardizeNumericInput(unsigned char* cUartMessage, int iMessageMaxSize);

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
float fParserToFloat(unsigned char* cUartMessage, int iBufferMaxSize);


void vParserFlexibleFloatToString(unsigned char* ucStringBuffer, int iBufferSize, float fNumberInput, int iNumberWholeDigits, int iNumberDecimalDigits, char cDelimiter);

#endif /* INC_PARSER_H_ */

