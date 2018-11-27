/****************************************************************
 * Header file for the 'Hex' class to contain one hex operand.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 22 September 2018
**/

#ifndef HEX_H
#define HEX_H

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// #include "../../Utilities/scanner.h"
// #include "../../Utilities/scanline.h"
#include "../../Utilities/utils.h"

#include "dabnamespace.h"

class Hex {
 public:
  Hex();
  Hex(string hexoperand);
  virtual ~Hex();

  string GetErrorMessages() const;
  int GetValue() const;
  string GetText() const;
  bool HasAnError() const;
  bool IsNegative() const;
  bool IsNotNull() const;
  bool IsNull() const;
  string ToString() const;

 private:
  bool is_invalid_;
  bool is_negative_;
  bool is_null_;
  int value_;
  string error_messages_;
  string text_;

  void Init(string hexoperand);
  void ParseHexOperand();
};
#endif
