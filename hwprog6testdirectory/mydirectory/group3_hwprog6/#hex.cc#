#include "hex.h"
/***************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456
 * Class 'Hex' as a container for one hex operand.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 17 August 2018
 *
 * We use an instance of a class for a hex operand since there are
 * a nuber of things we need to do with the operand and a number of tests
 * to be performed on the operands to make sure they are legal, etc.
 *
 * Variables used in this class:
 *
 *  bool is_invalid_       : is this operand invalid?
 *  bool is_negative_      : is this operand negative?
 *  bool is_null_          : is this operand null (i.e., blank)?
 *  int value_             : the actual 'int' translation of the hex
 *  string error_messages_ : error messages about invalidity
 *  string text_           : the actual source text of the operand
 *
 * Note that "null" is used as the flag for an opcode's target if that
 * opcode is actually all blanks.
**/

/***************************************************************************
 * Constructor
**/
Hex::Hex() {
}

/***************************************************************************
 * Constructor
**/
Hex::Hex(string text) {
  this->Init(text);
}

/***************************************************************************
 * Destructor
**/
Hex::~Hex() {
}

/***************************************************************************
 * Accessors and Mutators
**/

/***************************************************************************
 * Accessor for 'error_messages_'.
 * This simply returns an error message string if the 'is_invalid_' flag
 * has been set anywhere during execution of the program.
**/
string Hex::GetErrorMessages() const {
  string error_messages = "";
  if (is_invalid_) {
    error_messages += "\n***** ERROR -- HEX " + text_ + " IS INVALID";
  }
  return error_messages;
}

/***************************************************************************
 * Accessor for 'text_'.
**/
string Hex::GetText() const {
  return text_;
}

/***************************************************************************
 * Accessor for 'value_'.
**/
int Hex::GetValue() const {
  return value_;
}

/***************************************************************************
 * Accessor for error flag 'is_invalid_'.
 * The answer to 'HasAnError' is 'true' iff 'is_invalid_' is true.
**/
bool Hex::HasAnError() const {
  return is_invalid_;
}

/***************************************************************************
 * Accessor for 'is_negative_'.
**/
bool Hex::IsNegative() const {
  return is_negative_;
}

/***************************************************************************
 * Accessor for 'is_null_' in the negative.
**/
bool Hex::IsNotNull() const {
  return !is_null_;
}

/***************************************************************************
 * Accessor for 'is_null_' in the positive.
**/
bool Hex::IsNull() const {
  return is_null_;
}

/***************************************************************************
 * General functions.
**/

/***************************************************************************
 * Initialization function.
 * Set the iternal 'text_' variable with the text as read, and then parse
 * the text to create the 'value' and set validity flags.
**/
void Hex::Init(string text) {
  text_ = text;
  this->ParseHexOperand();
}

/***************************************************************************
 * Function 'ParseHexOperand'.
 * Parses the text into a decimal value and sets the error flag.
 *
 * The text to be parsed must be exactly five characters long
 * with a plus or minus sign present followed by exactly four
 * legitimate hex digit ASCII characters, with the letters uppercase.
**/
void Hex::ParseHexOperand() {
#ifdef EBUG
  Utils::log_stream << "enter ParseHexOperand" << endl;
#endif

  string hexdigits = "0123456789ABCDEF";

  is_invalid_ = false;

  // All blanks is legal, but if any non-blank, the text must be
  // 5 characters long, and legal characters. We check for legal by
  // a lookup in a string and then test later for invalid.
  // We set the value to zero for invalid input and set error flags
  // for this hex operand so as to indicate that the zero value
  // is in fact bogus..
  if (text_.length() != 5) {
    value_ = 0;
    is_invalid_ = true;
  } else if (text_ == "     ") {
    is_null_ = true;
  } else {
    // This is clumsy but functional.
    char char0 = text_.at(0);
    char char1 = text_.at(1);
    int value1 = hexdigits.find(char1);
    char char2 = text_.at(2);
    int value2 = hexdigits.find(char2);
    char char3 = text_.at(3);
    int value3 = hexdigits.find(char3);
    char char4 = text_.at(4);
    int value4 = hexdigits.find(char4);

    // If any of the characters weren't in the lookup we have an error.
    // Otherwise, we can build the decimal equiv of the hex.
    if ((value1 == string::npos) || (value2 == string::npos) ||
        (value3 == string::npos) || (value4 == string::npos)) {
      value_ = 0;
      is_invalid_ = true;
    } else {
      value_ = value4;
      value_ += value3 * 16;
      value_ += value2 * 16 * 16;
      value_ += value1 * 16 * 16 * 16;
    }

    // Deal with the signum to convert neg values to 2s complement
    // and check that the lead char is either '+' or '-'.
    is_negative_ = false;
    if (char0 == '-') {
      value_ = 65536 - value_;
      is_negative_ = true;
    } else if (char0 != '+') {
      value_ = 0;
      is_invalid_ = true;
    }
  }

#ifdef EBUG
  Utils::log_stream << "leave ParseHexOperand" << endl;
#endif
}

/***************************************************************************
 * Function 'ToString'.
 * This function formats a 'Hex' for prettyprinting.
 * If the operand is null (e.g., for an instruction that does not take an
 * operand, we print five dots.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string Hex::ToString() const {
#ifdef EBUG
  Utils::log_stream << "enter ToString" << endl;
#endif
  string s = "";

  if (text_ == "nullhexoperand") {
    s += Utils::Format(".....", 5);
  } else {
    s += Utils::Format(text_, 5);
  }

#ifdef EBUG
  Utils::log_stream << "leave ToString" << endl;
#endif
  return s;
}
