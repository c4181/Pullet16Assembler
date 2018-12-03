#include "symbol.h"
/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Symbol' as a container for one symbol.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Adarius Adams, Jeejun Kim, Andrew Gray, Christopher Moyer, Vinay Penmetsa
 * Date: 27 November 2018
**/

/******************************************************************************
 * Constructor
**/
Symbol::Symbol() {
}

/******************************************************************************
 * Constructor
**/
Symbol::Symbol(string text, int programcounter) {
  text_ = text;
  location_ = programcounter;
  is_invalid_ = this->CheckInvalid();
  is_multiply_ = false;
}

/******************************************************************************
 * Destructor
**/
Symbol::~Symbol() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor for 'error_messages_'.
**/
string Symbol::GetErrorMessages() const {
  bool previouserror = false;
  string error_messages = "";
  
  if(is_invalid_) { 
    error_messages += "**** ERROR -- SYMBOL" + text_ + "IS INVALID";
    previouserror = true;
  }
  if(is_multiply_) { 
    if(previouserror) {
     error_messages += "\n";
    }
   error_messages += "**** ERROR -- SYMBOL" + text_ + "IS MULTIPLY DEFINED";
  }
  return error_messages;
}

/******************************************************************************
 * Accessor for the 'location_'.
**/
int Symbol::GetLocation() const {
  return location_;
}

/******************************************************************************
 * Accessor for the existence of errors.
**/
bool Symbol::HasAnError() const {
  return (is_invalid_ || is_multiply_);
}

/******************************************************************************
 * Mutator 'SetMultiply'.
 * Sets the 'is_multiply' value to 'true'.
**/
void Symbol::SetMultiply() {
  is_multiply_ = true;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'CheckInvalid'.
 * Returns the boolean to say whether a symbol is invalid.
**/
bool Symbol::CheckInvalid() const {
  bool returnvalue = false;  // false means no, not invalid

  if(text_ == "   ") {
    return false; //not invalid
  }
  
  char char0 = text_.at(0);
  char char1 = text_.at(1);
  char char2 = text_.at(2);

  if(char1 == ' ') {
   if((char1 != ' ') || (char2 != ' ')) { 
   //starts blank,  non-blanks follow--WRONG!
   returnvalue = true; //false means no, not invalid.
   return returnvalue; //yes invalid
  } 
   else {
   returnvalue = false; //false means no, not invalid
   return returnvalue; //no, true
   }
 }

 //Not all blanks, and not leading blanks 
 //No middle blank, but then a non-blank
 if(char1 == ' ') { 
  if(char1 != ' ') { 
    returnvalue = true; //false means no, not invalid.
    return returnvalue; //yes invalid.
  }
 }
 //Getting this far, then the symbol is not completely blank.
 //If blanks are present they will all be on the RHS. 
  
  if (isalpha(text_.at(0)) == 0) {
    // If the first character is not an alpha symbol
    returnvalue = true;
    return returnvalue; //yes invalid
  }
  if (isalnum(text_.at(1)) == 0 || isalnum(text_.at(2)) == 0) {
    // If the second or third character is not alphanumeric
    returnvalue = true;
    return returnvalue;
  }

  return returnvalue;
}

/******************************************************************************
 * Function 'ToString'.
 * This function formats an 'Symbol' for prettyprinting.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string Symbol::ToString() const {
#ifdef EBUG
  Utils::log_stream << "enter ToString" << endl;
#endif
  string s = "";

  if (text_ == "nullsymbol") {
    s += Utils::Format("sss", 3);
  } else {
    s += Utils::Format(text_, 3);
  }

  s += Utils::Format(location_, 4);
  if (is_invalid_) {
    s += " INVALID";
  }
  if (is_multiply_) {
    s += " MULTIPLY";
  }

#ifdef EBUG
  Utils::log_stream << "leave ToString" << endl;
#endif
  return s;
}
