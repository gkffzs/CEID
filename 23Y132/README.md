#### (23Y132) - Principles of Programming Languages & Compilers [:link:](https://www.ceid.upatras.gr/en/undergraduate/courses/23%CE%A5132)
This repository contains the course project for the academic period of 2012-2013, done by
[George Kaffezas](https://github.com/gkffzs) and [Anastasia Paparrodopoulou](https://github.com/paparrodop-anast).
It's an implementation of a parser for an imaginary object-oriented language called "Simon", created using
[Flex](https://www.gnu.org/software/flex/flex.html) & [Bison](https://www.gnu.org/software/bison/). You can find
the assignment (in Greek) in the file `assignment.pdf`, specifically in section 2.

Assuming you are running a GNU/Linux distribution and that you have those two installed, you can test the parser by
typing the following commands in a terminal:
- `bison -y -d bison_file.y`
- `flex flex_file.l`
- `gcc -c y.tab.c lex.yy.c`
- `gcc y.tab.o lex.yy.o -o parser`
- `./parser input_file.txt`

The `output_file.txt` includes the output you're expecting, and the `included_file.txt` is the file that, as its name
suggests, is included in the beginning of `input_file.txt`.
