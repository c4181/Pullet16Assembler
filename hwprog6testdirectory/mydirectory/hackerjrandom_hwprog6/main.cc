#include "main.h"
static const char kTag[] = "Main: ";
/****************************************************************
 * Main program for Pullet Assembler program.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Used with permission and modified by: Jane Random Hacker
 * Date: 17 August 2017
 *
 * Note that the output file name is without extensions because
 * we create both a dot bin and a dot txt as output.
**/

int main(int argc, char *argv[]) {
  string in_filename = "";
  string binary_filename = "";
  string out_filename = "";
  string log_filename = "";

  Scanner in_scanner;
  ofstream out_stream;

  Assembler assembler;

  Utils::CheckArgs(3, argc, argv, "infilename outfilename logfilename");
  in_filename = static_cast<string>(argv[1]);
  binary_filename = static_cast<string>(argv[2]) + ".bin";
  out_filename = static_cast<string>(argv[2]) + ".txt";
  log_filename = static_cast<string>(argv[3]);

  Utils::LogFileOpen(log_filename);
  in_scanner.OpenFile(in_filename);
  Utils::FileOpen(out_stream, out_filename);

  Utils::log_stream << kTag << "Beginning execution" << endl;
  Utils::log_stream.flush();

  Utils::log_stream << kTag << "logfile '" << log_filename << endl;

  assembler.Assemble(in_scanner, binary_filename, out_stream);

  Utils::log_stream << kTag << "Ending execution" << endl;
  Utils::log_stream.flush();

  Utils::FileClose(Utils::log_stream);

  return 0;
}

