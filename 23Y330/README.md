#### (23Y330) - Operating Systems I [:link:](https://www.ceid.upatras.gr/en/undergraduate/courses/23%CE%A5330)
This repository contains the two course assignments for the academic period of 2010-2011, done by George Pyrgeris,
[George Kaffezas](https://github.com/gkffzs) and Thomas-Luigi Sdoggos. Unfortunately, there is no assignment document
available, but, on the other hand, almost every line of code has a comment (in Greek), so maybe this will help a little.

In order to test any of these assignments, you could have any GNU/Linux distribution installed and follow the
instructions below, for each case. General instructions for compiling through terminal are (assuming you are in
each assignment's directory):
- `make all`: compiles everything (both `server.c` \& `client.c`)
- `make server`: compiles `server.c`
- `make client`: compiles `client.c`
- `make clean`: deletes all compiled files

Then, you could have a different terminal session for running the server and the client. For example:
- open a terminal in the main directory, where all the compiled files are
- run the server by typing `./server` (or `sudo ./server`, if required)
- open a new terminal session in the same directory, while leaving the other running
- run the client by typing `./client` (or `sudo ./client`, if required)
- play with the various options to test their functionalities

###### [Assignment #1](https://github.com/gkffzs/CEID/tree/master/23Y330/Assignment%20%231)
For this assignment we had to implement a server-client model for the operation and management of parkings, using forks,
sockets and semaphores. 

###### [Assignment #2](https://github.com/gkffzs/CEID/tree/master/23Y330/Assignment%20%232)
For this assignment we had to implement the same server-client model as above, but this time we had to use threads
instead of forks.
