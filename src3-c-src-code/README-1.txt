Birzeit University - Faculty of Engineering
Electrical & Computer Engineering Department
Real-Time & Embedded Systems course - ENCS4330

Dr. Hanna Bullata
-----------------

Instructions on how to install the source code present in the file
basic.tar.gz
------------------------------------------------------------------

1/ log on your machine using your username and password 

2/ create the directory called "4330" if you haven't done that
already. The command is:

	> mkdir 4330

3/ Put the tarred and zipped file "basic.tar.gz" under the
directory "4330"

4/ execute the following 2 commands

	> gunzip basic.tar.gz
	> tar xvf basic.tar

The following directories will be created:
	args, exec, fork

5/ delete the file basic.tar since it is no more needed.

	> rm basic.tar

Note:
-----
For the unix gurus, the 2 commands in step 4 can be grouped in one
command as follows:
	
	> gzip -dc basic.tar.gz | tar -xvf -

where the command "gzip -dc" is equivalent to "gunzip"

6/ Now that the directories have been created, cd to the directory of
your choice and compile each of the C files as follows:

	> gcc "FileName.c" -o "FileName"

where you replace "FileName.c" by the C-file. If you want to be able
to debug your code using the gdb debugger, compile each of the C files
as follows:

	> gcc -g "FileName.c" -o "FileName"

where the option "-g" will create the symbols table needed by the
debugger.

To start the debugger, execute the following command:

	> gdb "Executable"

Where "Executable" is the executable you are trying to debug.


Under gdb, you can place a breakpoint on line 17 by typing the command 

	(gdb) break 17

To run the program, use the command:

	(gdb) run

To print the value of the variable i, use the command: 

	(gdb) print i

To go to the next line, use the command: 

	(gdb) next


Good Luck.