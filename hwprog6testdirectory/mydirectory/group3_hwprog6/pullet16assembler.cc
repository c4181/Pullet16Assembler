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
void Assembler::Assemble(Scanner& in_scanner, string binary_filename,
                         ofstream& out_stream) {
#ifdef EBUG
  Utils::log_stream << "enter Assemble" << endl;
#endif

  //////////////////////////////////////////////////////////////////////////
  // Pass one
  // Produce the symbol table and detect errors in symbols.

  //////////////////////////////////////////////////////////////////////////
  // Pass two
  // Generate the machine code.

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
  string returnvalue = "";
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
  string returnvalue = "";
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
  string returnvalue = "";
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
void Assembler::PassOne(Scanner& in_scanner) {
#ifdef EBUG
  Utils::log_stream << "enter PassOne" << endl;
#endif

  int counter = 0;
  Symbol symbol;
  CodeLine codeline = CodeLine();
  while(in_scanner.HasNext()){
    string line = in_scanner.NextLine();
    if(line.at(0) == '*'){
      continue;
    }
    else if(line.size() < 4) {
      line = "    " + line + "                                   ";
      codeline.SetCodeLine(counter, pc_in_assembler_, line.substr(0,3), line.substr(4,3), line.substr(8,1),
      line.substr(10,3), line.substr(14,5), line.substr(20), line);
      codelines_.push_back(codeline);  
    }
    else if (line.size()>20 && line.at(20) == '*') {
      codeline.SetCodeLine(counter, pc_in_assembler_, line.substr(0,3), line.substr(4,3), line.substr(8,1),
      line.substr(10,3), line.substr(14,5), line.substr(20), line);
      codelines_.push_back(codeline);
      symbol = Symbol(line,counter);
      symboltable_[line.substr(0,3)] = symbol;
    }
    else {
      line = "    " + line;
      codeline.SetCodeLine(counter, pc_in_assembler_, line.substr(0,3), line.substr(4,3), line.substr(8,1),
      line.substr(10,3), line.substr(14,5), line.substr(20), line);
      codelines_.push_back(codeline); 
    }
    counter++;
  }

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

  string mnemonic = codelines_.at(pc_in_assembler_).GetMnemonic();
  string opcode;
  string addressing_type;
  string sym_operand;

  if (opcodes_.find(mnemonic) != opcodes_.end()) {
    opcode = opcode.find(mnemonic);
  }

  addressing_type = codelines_.at(pc_in_assembler_).GetAddr();

  if (codelines_.at(pc_in_assembler_).HasSymOperand()) {
    sym_operand = codelines_.at(pc_in_assembler_).GetSymOperand();
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
  string s = "";

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
  for(map<string, Symbol>::iterator s = symboltable_.begin(); s != symboltable_.end; ++s) {
    Utils::log_stream << s->second.ToString() << endl;
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
