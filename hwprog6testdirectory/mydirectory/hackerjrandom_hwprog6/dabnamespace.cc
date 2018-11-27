#include "dabnamespace.h"

/***************************************************************************
 * Code file for the 'DABnamespace' for global constants and
 * functions.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 21 September 2018
 *
 * Documentation for the functions is in the header for those
 * functions.
**/

namespace DABnamespace {
/***************************************************************************
 * Function 'BitStringToDec'.
 * Convert a bit string to a decimal value.
 * This is merely a wrapper for the 'stoi' function.
 *
 * Parameters:
 *   thebits - the ASCII array of "bits" to be converted
 *
 * Returns:
 *   the array 'thebits' converted to an 'int'
**/
int BitStringToDec(const string thebits) {
#ifdef EBUG
  Utils::log_stream << "enter BitStringToDec" << endl;
#endif

  // Remember that the second parameter is for positioning the pointer
  // after doing the conversion (so we don't care here) and the third
  // says we are converting from a string of digits in binary.
  int stoivalue = std::stoi(thebits, nullptr, 2);

#ifdef EBUG
  Utils::log_stream << "leave BitStringToDec" << endl;
#endif

  return stoivalue;
}

/***************************************************************************
 * Function 'DecToBitString'.
 * This function converts a decimal 'int' to a string of 0s and 1s.
 *
 * We only allow conversion to a string of length 12 or of length 16
 * because we only allow an address (lessequal 4096 = 2^12) or a hex
 * operand of 16 bits.
 *
 * This is basically just a wrapper for the 'bitset' function.
 *
 * Parameters:
 *   value - the value to convert
 *   how_many_bits - the length of the result
 *
 * Returns:
 *   the 'string' of bits obtained from the 'value' parameter
**/
string DecToBitString(const int value, const int how_many_bits) {
#ifdef EBUG
  Utils::log_stream << "enter DecToBitString" << endl;
#endif

  string bitsetvalue = "";
  if (how_many_bits == 12) {
    bitsetvalue = std::bitset<12>(value).to_string();
  } else if (how_many_bits == 16) {
    bitsetvalue = std::bitset<16>(value).to_string();
  } else {
    Utils::log_stream << "ERROR DECTOBITSTRING " << value << " "
                      << how_many_bits << endl;
    exit(0);
  }

#ifdef EBUG
  Utils::log_stream << "leave DecToBitString" << endl;
#endif

  return bitsetvalue;
}

/******************************************************************************
 * Function 'GetMnemonicFromBits'.
 * This function retrieves the textual mnemonic from the bitstring code.
string GetMnemonicFromBits(string codebits) {
#ifdef EBUG
  Utils::log_stream << "enter GetMnemonicFromBits" << endl;
#endif
  return code_to_mnemonic_.at(codebits);
#ifdef EBUG
  Utils::log_stream << "leave GetMnemonicFromBits" << endl;
#endif
}
**/

}  // namespace DABnamespace

