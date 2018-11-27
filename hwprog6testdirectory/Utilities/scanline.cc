#include "scanline.h"
/****************************************************************
 * Copyright 2018 Duncan A. Buell
**/

using namespace std;

// static const string TAG = "ScanLine: ";

// ifstream Utils::inStream; // deprecated
// ofstream Utils::outStream; // deprecated
// ofstream ScanLine::zorklogStream;
// ostringstream ScanLine::zorkoss;
// stringstream ScanLine::zorkss;

// stringstream ScanLine::myss;

/****************************************************************
 * Constructor.
**/
ScanLine::ScanLine() {
}
/****************************************************************
 * Destructor.
**/
ScanLine::~ScanLine() {
}

/****************************************************************
 * General functions.
**/
/****************************************************************
 * Function 'HasMoreData'.
 *
 * Returns:
 *   true if there are ANY more characters in the input 'string'
**/
bool ScanLine::HasMoreData() {
  bool return_value = true;
#ifdef EBUGS
  Utils::logStream << TAG << "enter HasMoreData" << std::endl;
#endif

  if (scanline_ss_.eof()) {
    return_value = false;
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave HasMoreData '" << return_value
                   << "'" << std::endl;
#endif

  return return_value;
}

/****************************************************************
 * Function 'HasNext'.
 *
 * Returns:
 *   true if there are ANY more characters in the input 'string'
**/
bool ScanLine::HasNext() {
  bool return_value = true;
#ifdef EBUGS
  Utils::logStream << TAG << "enter HasNext" << std::endl;
#endif

  if (scanline_ss_.eof()) {
    return_value = false;
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave HasNext '" << return_value
                   << "'" << std::endl;
#endif

  return return_value;
}

/****************************************************************
 * Initialization. This because I can't make constructors work.
**/
void ScanLine::OpenString(std::string line) {
  std::string token;

#ifdef EBUGS
  Utils::logStream << TAG << "enter OpenString '" << line
                   << "'" << std::endl;
#endif

  scanline_ss_.clear();
  scanline_ss_.str(line);

#ifdef EBUGS
  Utils::logStream << TAG << "leave OpenString" << std::endl;
#endif
}

/****************************************************************
 * Function 'Next' to return the next string.
 *
 * The definition of a 'token' is anything other than whitespace.
 * In this implementation, whitespace includes newline, carriage
 * return, and tab.
 *
 * Returns:
 *   the 'string' version of the next token
**/
string ScanLine::Next() {
  std::string token;

#ifdef EBUGS
  Utils::logStream << TAG << "enter next" << std::endl;
#endif

  token = "";
  if (!scanline_ss_.eof()) {
    scanline_ss_ >> token;
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave next '" << token << "'" << std::endl;
#endif

  return token;
}

/****************************************************************
 * Function 'NextDouble' to return the next double.
 *
 * This function does not really trap erorrs. Errors converting
 * from 'string' to 'double' simply cause crashing.
 *
 * Returns:
 *   the next token in the file, parsed as a 'double'
**/
double ScanLine::NextDouble() {
  double local_double = 0.0;

#ifdef EBUGS
  Utils::logStream << TAG << "enter NextDouble" << std::endl;
#endif

  if (!scanline_ss_.eof()) {
    scanline_ss_ >> local_double;
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave NextDouble '" << nextValue
                   << "'" << std::endl;
#endif

  return local_double;
}

/****************************************************************
 * Function 'NextInt' to return the next integer.
 *
 * This function does not really trap erorrs. Errors converting
 * from 'string' to 'int' simply cause crashing.
 *
 * Returns:
 *   the next token in the file, parsed as an 'int'
**/
int ScanLine::NextInt() {
  int next_value = 0;
  std::string token = "";

#ifdef EBUGS
  Utils::logStream << TAG << "enter NextInt" << std::endl;
#endif

  if (!scanline_ss_.eof()) {
    scanline_ss_ >> token;
    next_value = Utils::StringToInteger(token);
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave NextInt '" << NextValue << "'" << std::endl;
#endif

  return next_value;
}

/****************************************************************
 * Function 'NextLine' to return the rest of the line.
 *
 * This is just a wrapper for the 'getline' function.
 * Note that this does not trim whitespace at the beginning
 * or at the end.
 *
 * CAVEAT: We have put a max of 1024 characters that can be
 *         parsed with this function.
 *
 * Returns:
 *   the 'string' version of the rest of the line
**/
string ScanLine::NextLine() {
  char xx[1025];
  std::string token;

#ifdef EBUGS
  Utils::logStream << TAG << "enter NextLine" << std::endl;
#endif

  if (scanline_ss_.eof()) {
    token = "";
  } else {
    scanline_ss_.getline(xx, 1024);
    token = string(xx);
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave NextLine '" << token
                   << "'" << std::endl;
#endif

  return token;
}

/****************************************************************
 * Function 'nextLONG' to return the next LONG.
 *
 * This function does not really trap errors. Errors converting
 * from 'string' to 'LONG' simply cause crashing.
 *
 * Returns:
 *   the next token in the file, parsed as a 'LONG'
**/
LONG ScanLine::NextLONG() {
  LONG next_value = 0;
  std::string token = "";

#ifdef EBUGS
  Utils::logStream << TAG << "enter NextLONG" << std::endl;
#endif

  if (!scanline_ss_.eof()) {
    scanline_ss_ >> token;
    next_value = Utils::StringToLONG(token);
  }

#ifdef EBUGS
  Utils::logStream << TAG << "leave NextLONG '" << next_value
                   << "'" << std::endl;
#endif

  return next_value;
}

/****************************************************************
 * Test function to read.
void ScanLine::zork() {
  string token;

#ifdef EBUGS
  Utils::logStream << TAG << "enter zork" << endl;
#endif

// while (!scanLineSS.eof())
  while (this->hasNext()) {
    token = next();

    Utils::logStream << TAG << "mytoken '" << token << "'" << endl;
  }
  scanLineSS.clear();

#ifdef EBUGS
  Utils::logStream << TAG << "leave zork" << endl;
#endif
}
**/
