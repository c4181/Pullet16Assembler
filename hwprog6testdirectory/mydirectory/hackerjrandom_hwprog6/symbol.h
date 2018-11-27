/****************************************************************
 * Header file for the 'Symbol' class to contain one symbol.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 17 August 2018
**/

#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// #include "../../Utilities/scanner.h"
// #include "../../Utilities/scanline.h"
#include "../../Utilities/utils.h"

class Symbol {
 public:
  Symbol();
  Symbol(string symboltext, int programcounter);
  virtual ~Symbol();

  string GetErrorMessages() const;
  int GetLocation() const;
  bool HasAnError() const;
  void SetMultiply();
  string ToString() const;

 private:
  int location_;
  bool is_multiply_;
  bool is_invalid_;
  string error_messages_;
  string text_;

  bool CheckInvalid() const;
};
#endif
