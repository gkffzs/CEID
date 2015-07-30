#### (23Y384) - Digital Communications [:link:](https://www.ceid.upatras.gr/en/undergraduate/courses/23%CE%A5384)
This repository contains the two course assignments for the academic period of 2013-2014, done by
[George Kaffezas](https://github.com/gkffzs). In order to test any of the assignments, you should have a version of 
[MATLAB](https://www.mathworks.com/products/matlab/) installed (for these assignments, version R2012b was used).

###### [Assignment #1](https://github.com/gkffzs/CEID/tree/master/23Y384/Assignment%20%231)
This folder contains the material of the first assignment. For this assignment we had to implement both a uniform and 
a non-uniform (based on Lloyd-Max algorithm) PCM quantizer, and to compare the results of several different levels of
quantization of `speech.wav`. Also, using Huffman coding (its source code, `huffman.m` was provided with the assignment)
and having `keimeno.txt` as input, we had to calculate the probability of each symbol of the alphabet, the entropy of the
source, and Huffman's efficiency. In specific:
- `/graphs` contains figures and pictures of the various implementations
- `/scripts` contains all the source files, the MATLAB scripts
- `/sources` contains the files that were used as input
- `4465_report_1.pdf` is the report for this assignment, in Greek
- `assignment_1.pdf` is the assignment's objectives and specifications, also in Greek

###### [Assignment #2](https://github.com/gkffzs/CEID/tree/master/23Y384/Assignment%20%232)
This folder contains the material of the second assignment. For this assignment we had to implement a simulation of a
basic telecommunication system (transmitter-channel-receiver), including filters, noise, upsampling and decision modules.
We used 2-PAM, 4-PAM, and 4-QAM modulation, calculated BER and then compared the different results. In specific:
- `/graphs` contains figures and pictures of each case
- `/scripts` contains all the source files, the MATLAB scripts
- `4465_report_2.pdf` is the report for this assignment, in Greek
- `assignment_2.pdf` is the assignment's objectives and specifications, also in Greek
- `results_2_e.txt` is a text file, containing the final results
