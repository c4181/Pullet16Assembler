/****************************************************************
 * Header file for the namespace for global things.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 21 September 2018
**/

#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <string>
#include <bitset>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;

// #include "../../Utilities/scanner.h"
// #include "../../Utilities/scanline.h"
#include "../../Utilities/utils.h"

namespace DABnamespace {
static const int kMaxMemory = 4096;

int BitStringToDec(const string thebits);
string DecToBitString(const int value, const int how_many_bits);
string GetMnemonicFromBits(string codebits);
}

#endif
