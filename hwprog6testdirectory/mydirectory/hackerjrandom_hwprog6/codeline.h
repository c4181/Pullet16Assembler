/****************************************************************
 * Header file for the 'CodeLine' class to contain one code line.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 17 August 2018
**/

#ifndef CODELINE_H
#define CODELINE_H

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
#include "hex.h"

class CodeLine {
 public:
  CodeLine();
  virtual ~CodeLine();

  string GetAddr() const;
  string GetCode() const;
  string GetComments() const;
  string GetErrorMessages() const;
  Hex GetHexObject() const;
  string GetLabel() const;
  string GetMnemonic() const;
  string GetPC() const;
  string GetSymOperand() const;

  bool HasLabel() const;
  bool HasSymOperand() const;

  bool IsAllComment() const;
  void SetCodeLine(int linecounter, int pc, string label, string mnemonic,
                   string addr, string symoperand, string hexoperand,
                   string comments, string code);
  void SetCommentsOnly(int linecounter, string line);
  void SetErrorMessages(string messages);
  void SetMachineCode(string code);
  void SetPC(int what);
  string ToString() const;

 private:
  bool is_all_comment_;

  int linecounter_;
  int pc_;

  string addr_;
  string code_;
  string comments_;
  string error_messages_;
  string label_;
  string mnemonic_;
  string symoperand_;

  Hex hex_;
};
#endif
