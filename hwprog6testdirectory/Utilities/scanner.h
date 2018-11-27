/****************************************************************
 * Header for the 'Scanner' class.
 * Copyright 2018 Duncan A. Buell
 *
 * Author/copyright:  Duncan Buell
 * Date: 12 August 2018
**/

#ifndef SCANNER_H_
#define SCANNER_H_

#define NDEBUG
#include <cassert>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "utils.h"
#include "scanline.h"

typedef int64_t LONG;

class Scanner {
 public:
/****************************************************************
 * Constructors and destructors for the class. 
**/
  Scanner();
  virtual ~Scanner();

/****************************************************************
 * Variables.
**/
  std::ifstream local_stream_;

/****************************************************************
 * General functions.
**/
  void Close();
  bool HasNext();
  double NextDouble();
  std::string Next();
  std::string NextLine();
  void OpenFile(std::string filename);
  int NextInt();
  LONG NextLONG();

 private:
  const std::string kTag = "SCANNER: ";

  ScanLine scanline_;
};

#endif  // SCANNER_H_
