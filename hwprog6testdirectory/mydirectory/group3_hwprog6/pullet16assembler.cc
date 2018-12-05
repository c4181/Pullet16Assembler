#include "pullet16assembler.h"

/***************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456
 * Class 'Assembler' for assembling code.
 *
 * Author/copyright:  Duncan A. Buell.  All rights reserved.
 * Used with permission and modified by: Adarius Adams, Jeejun Kim, Andrew Gray, Christopher Moyer, Vinay Penmetsa
 * Date: 27 November 2018
**/

/***************************************************************************
 * Constructor
**/
Assembler::Assembler() {
}

/***************************************************************************
 * Destructor
**/
Assembler::~Assembler() {
}

/***************************************************************************
 * Accessors and Mutators
**/

/***************************************************************************
 * General functions.
**/

/***************************************************************************
 * Function 'Assemble'.
 * This top level function assembles the code.
 *
 * Parameters:
 *   in_scanner - the scanner to read for source code
 *   out_stream - the output stream to write to
**/
void Assembler::Assemble(string file_name, string binary_filename,
                         ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter Assemble" << endl;
#endif
  opcodes_ = {                              {"BAN", "000"},
                                            {"SUB", "001"},
                                            {"STC", "010"},
                                            {"AND", "011"},
                                            {"ADD", "100"},
                                            {"LD ", "101"},
                                            {"BR ", "110"},
                                            {"STP", "111"},
                                            {"RD ", "111"},
                                            {"WRT", "111"},
                                            {"HEX", "000"},
                                            {"END", "000"},
                                            {"DS ", "000"},
                                            {"ORG", "000"}
                                          };
  //////////////////////////////////////////////////////////////////////////
  // Pass one
  // Produce the symbol table and detect errors in symbols.
  Utils::log_stream << "PASS ONE" << endl;
  PassOne(file_name);
  PrintSymbolTable();
  //////////////////////////////////////////////////////////////////////////
  // Pass two
  // Generate the machine code.
  Utils::log_stream << "\n" << "PASS TWO" << endl;
  pc_in_assembler_ = 0;
  PassTwo();
  PrintCodeLines();
  PrintSymbolTable();
  Utils::log_stream << endl;
  //////////////////////////////////////////////////////////////////////////
  // Dump the results.
  PrintMachineCode(binary_filename, out_stream);
#ifdef EBUG
  Utils::log_stream << "leave Assemble" << endl;
#endif
}

/***************************************************************************
 * Function 'GetInvalidMessage'.
 * This creates a "value is invalid" error message.
 *
 * Parameters:
 *   leadingtext - the text of what it is that is invalid
 *   symbol - the symbol that is invalid
**/
string Assembler::GetInvalidMessage(string leadingtext, string symbol) {
  string returnvalue = "Value is invalid.\nTXT: ";
  returnvalue += leadingtext;
  returnvalue += "\tSYM: ";
  returnvalue += symbol;
  return returnvalue;
}

/***************************************************************************
 * Function 'GetInvalidMessage'.
 * This creates a "value is invalid" error message.
 *
 * Parameters:
 *   leadingtext - the text of what it is that is invalid
 *   hex - the hex operand that is invalid
**/
string Assembler::GetInvalidMessage(string leadingtext, Hex hex) {
  string returnvalue = "Value is invalid.\nTXT: ";
  returnvalue += leadingtext;
  returnvalue += "\tHEX: ";
  returnvalue += hex.ToString();
  return returnvalue;
}

/***************************************************************************
 * Function 'GetUndefinedMessage'.
 * This creates a "symbol is undefined" error message.
 *
 * Parameters:
 *   badtext - the undefined symbol text
**/
string Assembler::GetUndefinedMessage(string badtext) {
  string returnvalue = "Symbol is undefined.\nSYM: ";
  returnvalue += badtext;
  return returnvalue;
}

/***************************************************************************
 * Function 'PassOne'.
 * Produce the symbol table and detect multiply defined symbols.
 *
 * CAVEAT: We have deliberately forced symbols and mnemonics to have
 *         blank spaces at the end and thus to be all the same length.
 *         Symbols are three characters, possibly with one or two blank at end.
 *         Mnemonics are three characters, possibly with one blank at end.
 *
 * Parameters:
 *   in_scanner - the input stream from which to read
 *   out-stream - the output stream to which to write
**/
void Assembler::PassOne(string file_name) {
#ifdef EBUG
  Utils::log_stream << "enter PassOne" << endl;
#endif
  pc_in_assembler_ = 0;
  int counter = 0;
  int org_counter;
  string line;
  CodeLine codeline = CodeLine();
  std::ifstream source(file_name);    // open file
  while (getline(source, line)) {
    // checks if the line is a comment
    if (line.at(0) == '*') {
      codeline.SetCommentsOnly(counter, line);
      codelines_.push_back(codeline);
      counter++;
    } else {
      // makes it so the line is at least 20 characters long
      while (line.size() < 20) {
        line += " ";
      }
      // sets the codeline
      codeline.SetCodeLine(counter, pc_in_assembler_, line.substr(0, 3),
      line.substr(4, 3), line.substr(8, 1), line.substr(10, 3),
      line.substr(14, 5), line.substr(20), line);
      codelines_.push_back(codeline);
      // checks if there is a symbol, if so adds it to the symbol table
      if (line.substr(0, 3) != "   ") {
        UpdateSymbolTable(pc_in_assembler_, line.substr(0, 3));
        SetNewPC(codeline);
      }
      // if the mnemonic is DS, iterates the PC appropriately
      if (line.substr(4, 3) == "DS ") {
        if (codeline.GetHexObject().GetValue() < maxpc_ &&
           codeline.GetHexObject().GetValue() > 0) {
          pc_in_assembler_ += codeline.GetHexObject().GetValue() - 1;
        }
      }
      if (line.substr(4, 3) == "ORG") {
        if (codeline.GetHexObject().GetValue() < maxpc_ &&
           codeline.GetHexObject().GetValue() > 0) {
          pc_in_assembler_ = codeline.GetHexObject().GetValue() - 1;
        }
      }
      if (line.substr(4, 3) == "END") {
        pc_in_assembler_--;
      }
      counter++;
      pc_in_assembler_++;
    }
  }
  source.close();  // closes file

#ifdef EBUG
  Utils::log_stream << "leave PassOne" << endl;
#endif
}

/***************************************************************************
 * Function 'PassTwo'.
 * This function does pass two of the assembly process.
**/
void Assembler::PassTwo() {
#ifdef EBUG
  Utils::log_stream << "enter PassTwo" << endl;
#endif
  int counter = 0;
  while (codelines_.size() > counter) {
    if (codelines_.at(counter).IsAllComment() == true) {
      counter++;
    } else {
    string mnemonic = codelines_.at(counter).GetMnemonic();  // gets mnemonic
    string opcode;
    string addressing_type;
    string sym_operand;
    Symbol the_symbol;
    Symbol label;
    int operand_location;
    int org_counter;
    int ds_counter = 0;
    int memory_address = pc_in_assembler_;
    string machine_code;
    bool valid_symbol = true;
    // Retrieve all necessary values from codelines
    // finds opcode in the codeline
    if (opcodes_.count(mnemonic) == 0) {
      codelines_.at(counter).SetErrorMessages("MNEMONIC " + mnemonic +
      " IS INVALID");
      has_an_error_ = true;
    }
    if (opcodes_.find(mnemonic) != opcodes_.end()) {
      opcode = opcodes_.find(mnemonic) -> second;
    }
    addressing_type = codelines_.at(counter).GetAddr();
    label = symboltable_[codelines_.at(counter).GetLabel()];
    if (label.ToString().substr(0, 3) != "   " && label.HasAnError()) {
      codelines_.at(counter).SetErrorMessages(label.GetErrorMessages());
      has_an_error_ = true;
    }
    if (codelines_.at(counter).HasSymOperand()) {
      sym_operand = codelines_.at(counter).GetSymOperand();
      if (symboltable_.count(sym_operand) == 0) {
        valid_symbol = false;
        machine_code = kDummyCodeA;
        machinecode_.push_back(machine_code);
        codelines_.at(counter).SetErrorMessages("SYMBOL " +
                                                sym_operand + " IS UNDEFINED");
        has_an_error_ = true;
      }
      if (symboltable_.find(sym_operand) != symboltable_.end()) {
        the_symbol = symboltable_.find(sym_operand) -> second;
        operand_location = the_symbol.GetLocation();
      }
      memory_address = operand_location;
    }
    // checks what the opcode is, then creates the machine code line
    // based on the opcode
    if (mnemonic == "END") {
      found_end_statement_ = true;
    }
    if (opcode != "111" && opcode != "000" && valid_symbol) {
      machine_code = opcode;
      // Set machine code for any instruction in Format 1
      if (addressing_type == "*") {
        machine_code += "1";
      } else {
        machine_code += "0";
      }
      machine_code += DABnamespace::DecToBitString(memory_address, 12);
      machinecode_.push_back(machine_code);
    } else if (valid_symbol) {
      //  Set machine code for any instruction in Format 2
      machine_code = opcode;
      machine_code += "0";
      if (mnemonic == "RD ") {
        machine_code += "000000000001";
      } else if (mnemonic == "STP") {
        machine_code += "000000000010";
      } else if (mnemonic == "WRT") {
        machine_code += "000000000011";
      } else if (mnemonic == "HEX") {
        if (!codelines_.at(counter).GetHexObject().HasAnError()) {
        machine_code = DABnamespace::DecToBitString(
          codelines_.at(counter).GetHexObject().GetValue(), 16);
        } else {
          machine_code = kDummyCodeC;
          codelines_.at(counter).SetErrorMessages("ERROR, " +
          codelines_.at(counter).GetHexObject().GetText()  +
          " IS INVALID");
        }
      } else if (mnemonic == "BAN") {
        machine_code = opcode;
        if (addressing_type == "*") {
          machine_code += "1";
        } else {
          machine_code += "0";
        }
        machine_code += DABnamespace::DecToBitString(memory_address, 12);
      } else if (mnemonic == "END") {
          machine_code = "";
          pc_in_assembler_--;
        } else if (mnemonic == "DS ") {
          if (codelines_.at(counter).GetHexObject().GetValue() < maxpc_ &&
            codelines_.at(counter).GetHexObject().GetValue() > 0) {
            org_counter = pc_in_assembler_;
            pc_in_assembler_ +=
            codelines_.at(counter).GetHexObject().GetValue() - 1;
            machine_code = "1111000000000000";
            machinecode_.push_back(machine_code);
            while (org_counter < pc_in_assembler_) {
              machinecode_.push_back(kDummyCodeA);
              org_counter++;
            }
            machine_code = "";
          } else {
            machine_code = kDummyCodeA;
            codelines_.at(counter).SetErrorMessages("DS ALLOCATION " +
            codelines_.at(counter).GetHexObject().GetText() +
            " IS INVALID");
            has_an_error_ = true;
          }
      } else if (mnemonic == "ORG") {
          if (codelines_.at(counter).GetHexObject().GetValue() < maxpc_ &&
            codelines_.at(counter).GetHexObject().
            GetValue() > 0) {
            machine_code = "";
            org_counter = pc_in_assembler_;
            pc_in_assembler_ = codelines_.at(counter).GetHexObject().GetValue();
            while (org_counter < pc_in_assembler_) {
              machinecode_.push_back(kDummyCodeA);
              org_counter++;
            }
            } else {
            codelines_.at(counter).SetErrorMessages("ERROR, " +
            codelines_.at(counter).GetHexObject().GetText() +
            " is out of bounds");
            has_an_error_ = true;
          }
       }
      if (machine_code != "") {
        machinecode_.push_back(machine_code);
      }
    }
    ++pc_in_assembler_;
    counter++;
  }
  }

#ifdef EBUG
  Utils::log_stream << "leave PassTwo" << endl;
#endif
}

/***************************************************************************
 * Function 'PrintCodeLines'.
 * This function prints the code lines.
**/
void Assembler::PrintCodeLines() {
#ifdef EBUG
  Utils::log_stream << "enter PrintCodeLines" << endl;
#endif
  string s = "";

  for (auto iter = codelines_.begin(); iter != codelines_.end(); ++iter) {
    if ((*iter).IsAllComment()) {
      s += (*iter).GetCode() + '\n';
    } else {
      s += (*iter).ToString() + '\n';
    }
  }

  if (!found_end_statement_) {
    s += "\n***** ERROR -- NO 'END' STATEMENT\n";
    has_an_error_ = true;
  }

#ifdef EBUG
  Utils::log_stream << "leave PrintCodeLines" << endl;
#endif
  Utils::log_stream << s << endl;
}

/***************************************************************************
 * Function 'PrintMachineCode'.
 * This function prints the machine code.
**/
void Assembler::PrintMachineCode(string binary_filename,
                                 ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter PrintMachineCode" << " "
                    << binary_filename << endl;
#endif
  if (found_end_statement_  && has_an_error_ == false) {
  int i = 0;
  // Uses a bitset to convert the ascii to binary and then writes binary to
  // a file 16 bits at a time
  if (found_end_statement_ && has_an_error_ == false) {
  for (int i = 0; i < machinecode_.size(); i++) {
    out_stream << machinecode_.at(i) << endl;
    Utils::log_stream << machinecode_.at(i) << endl;
  }
  ofstream output_file(binary_filename, ofstream::binary);
  if (output_file) {
    char* buffer = new char[2];
    for (int i = 0; i < machinecode_.size()-1; ++i) {
      string ascii = machinecode_.at(i);
      bitset<16> bs(ascii);
      int the_bin = static_cast<int>(bs.to_ulong());
      buffer = reinterpret_cast<char*>(&the_bin);
      output_file.write(buffer, 2);
    }
    output_file.close();
  }
  }
  } else {
    Utils::log_stream << "ERRORS EXIST IN CODE" << endl;
    Utils::log_stream << "NO MACHINE CODE GENERATED" << endl;
  }
#ifdef EBUG
  Utils::log_stream << "leave PrintMachineCode" << endl;
#endif
}

/******************************************************************************
 * Function 'PrintSymbolTable'.
 * This function prints the symbol table.
**/
void Assembler::PrintSymbolTable() {
#ifdef EBUG
  Utils::log_stream << "enter PrintSymbolTable" << endl;
#endif

#ifdef EBUG
  Utils::log_stream << "leave PrintSymbolTable" << endl;
#endif
  // goes through the symbol table and prints each element
  for (map<string, Symbol>::iterator s = symboltable_.begin();
        s != symboltable_.end(); ++s) {
    if (s->second.ToString().substr(0, 3) != "   ") {
    Utils::log_stream << "SYM " << s->second.ToString() << endl;
    }
  }
}

/******************************************************************************
 * Function 'SetNewPC'.
 * This function gets a new value for the program counter.
 *
 * No return value--this sets the class's PC variable.
 *
 * Parameters:
 *   codeline - the line of code from which to update
**/
void Assembler::SetNewPC(CodeLine codeline) {
#ifdef EBUG
  Utils::log_stream << "enter SetNewPC" << endl;
#endif
  // sets new pc
  if (codeline.GetPC() < maxpc_ && codeline.GetPC() >= 0) {
    pc_in_assembler_ = codeline.GetPC();
  } else {
    has_an_error_ = true;
  }

#ifdef EBUG
  Utils::log_stream << "leave SetNewPC" << endl;
#endif
}

/******************************************************************************
 * Function 'UpdateSymbolTable'.
 * This function updates the symbol table for a putative symbol.
 * Note that there is a hack here, in that the default value is 0
 * and that would mean we can't store a symbol at location zero.
 * So we add one, and then back that out after the full first pass is done.
**/
void Assembler::UpdateSymbolTable(int pc, string symboltext) {
#ifdef EBUG
  Utils::log_stream << "enter UpdateSymbolTable" << endl;
#endif
    Symbol symbol;
    if (symboltable_.count(symboltext) < 1) {
      symbol = Symbol(symboltext, pc);
      symboltable_[symboltext] = symbol;
    } else {
      symboltable_.find(symboltext)->second.SetMultiply();
    }
#ifdef EBUG
  Utils::log_stream << "leave UpdateSymbolTable" << endl;
#endif
}

