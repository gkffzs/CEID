#### (23330E) - Operating Systems Laboratory [:link:](https://www.ceid.upatras.gr/en/undergraduate/courses/23330%CE%95)

This repository contains two selected assignments, the first from the academic period of 2010-2011, and the second from
that of 2011-2012, both done by [George Kaffezas](https://github.com/gkffzs). The rest of the course assignments had
to do with kernel and system calls in [MINIX 3](http://www.minix3.org/), so they're not included due to their more
specific and complex nature.

###### [Assignment #1](https://github.com/gkffzs/CEID/tree/master/23330E/Assignment%20%231)
For this assignment we had to specify several commands of the Linux command line, in order to perform various tasks, such
as finding the files that don't belong to the root user, etc. You can find them in details in `assignment.pdf` (in
Greek), while the respective answers are all in `answers.txt`. To test any of the commands, you need access to a
GNU/Linux distribution, so that you can type them in the terminal.

###### [Assignment #2](https://github.com/gkffzs/CEID/tree/master/23330E/Assignment%20%232)
For this assignment we had to create a Bash script for the management of a simple students' grades file. The program 
had 6 functions (load the file, show a student's grade, change a student's grade, show the grades list, save the grades
list, exit) and its source file is `4465_ex1.sh`. For a more thorough explanation, you could read `assignment.pdf`.
Finally, the grades list is a text file, and `grades.txt` is a sample list that you can use to test the functionality of
the program. In order to run it, you should have a GNU/Linux distribution with the
[Bash shell](https://www.gnu.org/software/bash/) installed (its the default for many distributions). If you have, then
you should type:
- `chmod u+x 4465_ex1.sh`: to make the script readable and executable
- `bash 4465_ex1.sh`: to run the script
