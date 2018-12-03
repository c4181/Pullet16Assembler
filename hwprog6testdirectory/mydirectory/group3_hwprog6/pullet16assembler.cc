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

  //////////////////////////////////////////////////////////////////////////
  // Pass one
  // Produce the symbol table and detect errors in symbols.

  PassOne(file_name);
  PrintSymbolTable();
  //////////////////////////////////////////////////////////////////////////
  // Pass two
  // Generate the machine code.
  pc_in_assembler_ = 0;
  PassTwo();

  //////////////////////////////////////////////////////////////////////////
  // Dump the results.

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
  Symbol symbol;
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
        symbol = Symbol(line.substr(0, 3), pc_in_assembler_);
        symboltable_[line.substr(0, 3)] = symbol;
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

  while (codelines_.size() < pc_in_assembler_) {
    string mnemonic = codelines_.at(pc_in_assembler_).GetMnemonic();
    string opcode;
    string addressing_type;
    string sym_operand;
    Symbol the_symbol;
    int memory_address = -1;
    string machine_code;

    // Retrieve all necessary values from codelines
    if (opcodes_.find(mnemonic) != opcodes_.end()) {
      opcode = opcodes_.find(mnemonic) -> second;
    }

    addressing_type = codelines_.at(pc_in_assembler_).GetAddr();

    if (codelines_.at(pc_in_assembler_).HasSymOperand()) {
      int operand_location = -1;
      sym_operand = codelines_.at(pc_in_assembler_).GetSymOperand();

      if (symboltable_.find(sym_operand) != symboltable_.end()) {
        the_symbol = symboltable_.find(sym_operand) -> second;
        operand_location = the_symbol.GetLocation();
      }

      memory_address = codelines_.at(operand_location).
                       GetHexObject().GetValue();
    }

    if (opcode != "111") {
      machine_code = opcode;
      // Set machine code for any instruction in Format 1
      if (addressing_type == "*") {
        machine_code += "1";
      } else {
        machine_code += "0";
      }
      machine_code += to_string(memory_address);

      machinecode_.push_back(machine_code);
    } else {  //  Set machine code for any instruction in Format 2
      machine_code = opcode;
      machine_code += "0";

      if (mnemonic == "RD") {
        machine_code += "000000000001";
      } else if (mnemonic == "STP") {
        machine_code += "000000000010";
      } else if (mnemonic == "WRT") {
        machine_code += "000000000011";
      }

      machinecode_.push_back(machine_code);
    }
    ++pc_in_assembler_;
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
    s += (*iter).ToString() + '\n';
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

  // Uses a bitset to convert the ascii to binary and then writes binary to
  // a file 16 bits at a time
  ofstream output_file(binary_filename, ofstream::binary);
  if (output_file) {
    char* buffer = new char[2];

    for (int i = 0; i < machinecode_.size(); ++i) {
      string ascii = machinecode_.at(i);
      bitset<16> bs(ascii);
      int the_bin = static_cast<int>(bs.to_ulong());
      buffer = reinterpret_cast<char*>(&the_bin);
      output_file.write(buffer, 2);
    }
    output_file.close();
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
    Utils::log_stream << "SYM " << s->second.ToString().substr(0, 3) << " " <<
    s->second.GetLocation() << " " << s->second.GetErrorMessages() << endl;
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

#ifdef EBUG
  Utils::log_stream << "leave UpdateSymbolTable" << endl;
#endif
}

