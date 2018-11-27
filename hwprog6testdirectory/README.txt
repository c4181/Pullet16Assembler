Do your programming in the 'mydirectory' directory, in a directory
lastnamefirstname_hwx (all lower case). In my case, I do all my
programming in the directory 'mydirectory/buellduncan_hwx' for
programming assignment number x. That is, the 'x' should be replaced
by the actual number of the homework assignment.

Run the script zaZipUpScript.txt to tar and gzip your directory
and copy it to the 'assignment' directory.

Run the script zbFileCopyScript.txt to create directory 'testdirectory'
and unzip and untar your submission from 'assignment' into 'testdirectory'.

Run the script zcCompileScript.txt to compile all the programs in
the subdirectories of 'testdirectory'.  (For the most part, this should
only be your directory.)

Run the script zdExecuteScript.txt to execute all the programs in
the subdirectories that were compiled in the previous step.

If this works, you should have the appropriate output files in your
directory. To determine the names of the appropriate output files,
look at the zdExecuteScript.txt to see from where it is taking input
and to where it is sending the output either by redirecting standard
output or by providing command line arguments that are the file names.
You will sometimes have sample input files that have different names.

It is generally a good idea to have a backup copy of your input file
just in case you go brain dead and use the input file name for the
output file name and erase the input data.

Or, you can have several input files, perhaps with a number at the
end to differentiate them, and then copy whichever you want to the
"official" name you use when you run the executable.
