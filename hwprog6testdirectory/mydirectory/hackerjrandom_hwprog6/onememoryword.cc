#include "onememoryword.h"

/***************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456
 * Class 'OneMemoryWord' as a container for one word of memory.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 17 August 2018
 *
 * This exists almost entirely to allow the text of a function to indicate
 * what one is extracting from the 16 bit pattern that is a memory word,
 * and to format the bits for printing as 3 + 1 + 12 for opcode, indirect,
 * and address.
**/

/***************************************************************************
 * Constructor
**/
OneMemoryWord::OneMemoryWord() {
}

/***************************************************************************
 * Constructor
**/
OneMemoryWord::OneMemoryWord(string thestring) {
  Initialize(thestring);
}

/***************************************************************************
 * Destructor
**/
OneMemoryWord::~OneMemoryWord() {
}

/***************************************************************************
 * Accessors and Mutators
**/

/***************************************************************************
 * Accessor for the 'address_bits_'.
**/
string OneMemoryWord::GetAddressBits() const {
  return bit_pattern_.substr(4);
}

/***************************************************************************
 * Accessor for the 'bit_pattern_'.
**/
string OneMemoryWord::GetBitPattern() const {
  return bit_pattern_;
}

/***************************************************************************
 * Accessor for the 'indirect_flag_'.
**/
string OneMemoryWord::GetIndirectFlag() const {
  return bit_pattern_.substr(3, 1);
}

/***************************************************************************
 * Accessor for the 'mnemonic_bits_'.
**/
string OneMemoryWord::GetMnemonicBits() const {
  return bit_pattern_.substr(0, 3);
}

/***************************************************************************
 * Accessor for the 'mnemonic_code_'.
string OneMemoryWord::GetMnemonicCode() const {
  string codebits = this->GetMnemonicBits();
  string mnemonic_code = DABnamespace::GetMnemonicFromBits(codebits);
  return mnemonic_code;
}
**/

/***************************************************************************
 * Mutator for the 'bit_pattern_'.
**/
void OneMemoryWord::SetBitPattern(string what) {
  bit_pattern_ = what;
}

/***************************************************************************
 * General functions.
**/

/***************************************************************************
 * Function 'Initialize'.
**/
//void OneMemoryWord::Initialize(Globals globals, string bit_pattern) {
//  globals_ = globals;
void OneMemoryWord::Initialize(string bit_pattern) {
  bit_pattern_ = bit_pattern;
}

/***************************************************************************
 * Function 'ToString'.
 * This function formats a 'OneMemoryWord' for prettyprinting.
 * This makes sense if the word is an instruction.  If it's just a number or a
 * bit pattern, then the prettyprinting makes less sense.  But we do the
 * prettyprinting because taking out spaces in reading a line is easier than
 * adding in spaces that would separate mnemonic, etc.
 *
 * Returns:
 *   the prettyprint string for printing
**/
string OneMemoryWord::ToString() const {
#ifdef EBUG
  Utils::log_stream << "enter ToString" << endl;
#endif
  string sss = "";
  sss += this->GetMnemonicBits() + " " + this->GetIndirectFlag() + " " +
         this->GetAddressBits();


#ifdef EBUG
  Utils::log_stream << "leave ToString" << endl;
#endif
  return sss;
}
