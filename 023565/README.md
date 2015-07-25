#### (023565) - Languages Technology [:link:](https://www.ceid.upatras.gr/en/undergraduate/courses/23565)
This repository contains the course assignment for the academic period of 2012-2013, done by
[George Kaffezas](https://github.com/gkffzs), [Aris Magripis](https://github.com/aris-mag) and George Kolokythas. For
this assignment we had to implement a text categorization system.

In short, we had two collections of texts: collection E, with texts already categorized in two categories (sci & rec),
and collection A, with texts to be categorized. So, with the use of a characteristics space S, the respective vectors
and matrices with weights (normalized TF-IDF), and similarity functions (like Tanimoto, Jaccard, etc), we implemented
our system in Python. For a more detailed description of the assignment, read `assignment.pdf` (which is in Greek). 

Having our system ready (see `A22_project.py`, it is the source code), we performed various runs in order to check its
functionality. The results of some of those runs are included in `/results` folder, while our final report is 
`A22_report.pdf` (also in Greek). Finally, the two collections of texts, E and A, are included in `/Askisi-A-Corpus`.

If you want to test any of the above, you should have a version of [Python](https://www.python.org/) installed, along
with the libraries [NLTK](http://www.nltk.org/), [SciPy](http://www.scipy.org/) and [NumPy](http://www.numpy.org/).
Also, you should either place the collections of the texts in `C:/lt/` folder, or you could change their path in the
lines 40, 41, 44 and 45 of the source code.
