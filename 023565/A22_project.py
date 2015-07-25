# -----------------------------------------------------------------------------------------------------------------------------------------|
# -----------------------------------------| LINGUISTIC TECHNOLOGY | PROJECT 2012-2013 | A22 |---------------------------------------------|
# --------------------------| Magripis Aris - 4651 | Kolokythas Giorgos - 4646 | Kaffezas Giorgos - 4465 |---------------------------------|
# -----------------------------------------------------------------------------------------------------------------------------------------|
# REQUIRED LIBRARIES |---------------------------------------------------------------------------------------------------------------------|
import re
import os
import glob
import math
import nltk
import time
import numpy
import string
import operator
from numpy import sqrt
from numpy import divide
from numpy import multiply
from collections import defaultdict
from scipy.sparse import lil_matrix
from nltk.tokenize import RegexpTokenizer

# START OF MAIN PROGRAM |------------------------------------------------------------------------------------------------------------------|
if __name__ == '__main__': # --------------------------------------------------------------------------------------------------------------|
    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "------------------------| LINGUISTIC TECHNOLOGY |-------------------------"
    print "--------------------------| PROJECT 2012-2013 |---------------------------"

    # Start time counting.
    # We use time.time() function that returns the time in seconds since the epoch.
    # We save once when the program begins, and then we calculate its stage's time by subtraction.
    start_time = time.time()
    
    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "STAGE #1: INITIALIZATION |------------------------------------------------"
    # To list the files included in each collection, we use the 'glob' module.
    # It returns a list of unix style pathnames of the files, that makes search and categorization easier.
    # List of files in collection A.
    list_of_files_in_A_rec = glob.glob('C:\\lt\\Askisi-A-Corpus\\sillogi-A\\rec.test\\*')
    list_of_files_in_A_sci = glob.glob('C:\\lt\\Askisi-A-Corpus\\sillogi-A\\sci.test\\*')
    list_of_files_in_A = list_of_files_in_A_rec + list_of_files_in_A_sci
    # List of files in collection E.
    list_of_files_in_E_rec = glob.glob('C:\\lt\\Askisi-A-Corpus\\sillogi-E\\rec.train\\*')
    list_of_files_in_E_sci = glob.glob('C:\\lt\\Askisi-A-Corpus\\sillogi-E\\sci.train\\*')
    list_of_files_in_E = list_of_files_in_E_rec + list_of_files_in_E_sci
    # Number of documents in each collection.
    number_of_files_in_A = len(list_of_files_in_A)
    number_of_files_in_E = len(list_of_files_in_E)
    # Category that each file from collection E belongs to.
    # We use a dictionary to save pathnames as keys and their category as value.
    collection_E_categorized = {}
    for i in range(len(list_of_files_in_E_rec)): # rec.train
        collection_E_categorized[list_of_files_in_E_rec[i]] = 'rec'
    for i in range(len(list_of_files_in_E_sci)): # sci.train
        collection_E_categorized[list_of_files_in_E_sci[i]] = 'sci'
    # Decleration of porter for the stemming. We chose PorterStemmer.
    porter = nltk.PorterStemmer()
    # Setting the size of the space vector.
    space_length = 4000
    # Printing info and time passed.
    print ">>>>>     Files in collection A:", number_of_files_in_A
    print ">>>>>     Files in collection E:", number_of_files_in_E
    print ">>>>>     Time:", time.time() - start_time, "sec"
    passed_time = time.time() - start_time

    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "STAGE #2: TOKENIZATION, STEMMING & TF-IDF FOR COLLECTION E |--------------"      
    # Initialization of variables used in this stage.
    # We use a list for storing the stems of each file.
    stems = []
    # We use a defaultdict dictionary, which has a default value for keys, for storing term and inverse document frequency.
    # By doing this, keys for which no value has been explicitly defined can be accessed without errors.
    term_frequency = defaultdict(int) # Default values of integer type.
    inverse_document_frequency = defaultdict(float) # Default values of float type.
    # Creating a list of dictionaries for each file in collection E.
    tf_for_collection_E = [{}] * number_of_files_in_E 
    # Creating a list of sets for each file in collection E.
    # Sets are unordered collections with no duplicate elements, and thus suitable for storing stems only once.
    stems_of_each_file_in_E = [set()] * number_of_files_in_E
    # Again, we use a defaultdict dictionary to store the results of this stage.
    tf_idf_for_collection_E = defaultdict(float) # Default values of float type.
    # Loop for every file in collection E.
    for i in range(number_of_files_in_E):
        # Reading the data from the source file.
        temp_file = open(list_of_files_in_E[i])
        data = temp_file.read()
        data = data.lower() # Used for lowercase comparisons.
        temp_file.close()
        # Tokenization & stemming. The following tokenizer forms tokens out
        # of alphabetic sequences, money expressions, and any other non-whitespace sequences.
        tokenizer = RegexpTokenizer('\w+|\$[\d\.]+|\S+')
        token_list = tokenizer.tokenize(data)
        stems = [porter.stem(t) for t in token_list]
        stems_of_each_file_in_E[i] = set(stems)
        # Counting term frequency & inverse document frequency.
        for k in range(len(stems)):
            term_frequency[stems[k]] += 1
        for temp_stem in term_frequency.keys():
            inverse_document_frequency[temp_stem] += 1
        tf_for_collection_E[i] = term_frequency
        # Emptying tf-dictionary for next use.
        term_frequency = defaultdict(int)
    # Normalizing the inverse document frequency values.  
    for temp_stem, temp_df in inverse_document_frequency.items():
        inverse_document_frequency[temp_stem] = math.log10(number_of_files_in_E/float(temp_df))
    # Calculating TF-IDF for collection E.
    for i in range(len(tf_for_collection_E)):
        for temp_stem, temp_tf in tf_for_collection_E[i].iteritems():
            temp_tf_idf = temp_tf * inverse_document_frequency[temp_stem]
            # We keep the greater value of TF-IDF for each stem.
            if temp_tf_idf > tf_idf_for_collection_E[temp_stem]:
                tf_idf_for_collection_E[temp_stem] = temp_tf_idf
    # Printing time passed.
    print ">>>>>     Time:", time.time() - start_time - passed_time, "sec"
    passed_time = time.time() - start_time

    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "STAGE #3: TOKENIZATION, STEMMING & TF-IDF FOR COLLECTION A |--------------"
    # Initialization of variables used in this stage. Same as above, except that this time is for collection A.
    stems = []
    term_frequency = defaultdict(int)
    tf_for_collection_A = [{}] * number_of_files_in_A
    stems_of_each_file_in_A = [set()] * number_of_files_in_A
    tf_idf_for_collection_A = defaultdict(float)
    # Loop for every file in collection A.
    for i in range(number_of_files_in_A):
        # Reading the data from the source file.
        temp_file = open(list_of_files_in_A[i])
        data = temp_file.read()
        data = data.lower() # Used for lowercase comparisons.
        temp_file.close()
        # Tokenization & stemming.     
        tokenizer = RegexpTokenizer('\w+|\$[\d\.]+|\S+')
        token_list = tokenizer.tokenize(data)
        stems = [porter.stem(t) for t in token_list]
        stems_of_each_file_in_A[i] = set(stems)
        # Counting term frequency & inverse document frequency.
        for k in range(len(stems)):
            term_frequency[stems[k]] += 1
        tf_for_collection_A[i] = term_frequency
        # Emptying tf-dictionary for next use.
        term_frequency = defaultdict(int)
    # Calculating TF-IDF for collection A.
    for i in range(len(tf_for_collection_A)):
        for temp_stem, temp_tf in tf_for_collection_A[i].iteritems():
            temp_tf_idf = temp_tf * inverse_document_frequency[temp_stem]
            if temp_tf_idf > tf_idf_for_collection_A[temp_stem]:
                tf_idf_for_collection_A[temp_stem] = temp_tf_idf
    # Printing time passed.
    print ">>>>>     Time:", time.time() - start_time - passed_time, "sec"
    passed_time = time.time() - start_time

    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "STAGE #4: SPACE & VECTOR CONSTRUCTION |-----------------------------------"
    # Creating space vector.
    space = []
    # Sorting TF-IDF values with descending order.
    sorted_tf_idf_for_collection_E = sorted(tf_idf_for_collection_E.iteritems(), key = operator.itemgetter(1), reverse = True)
    # Creating space vector by appending stems with maximum values of TF-IDF.
    for i in range(space_length):
        space.append(sorted_tf_idf_for_collection_E[i][0])
    print ">>>>>     Space length:", space_length
    # Creating vectors for every file in collection E.
    # In this point, we use lil_matrix linked list sparse matrix.
    # Sparse matrices can be used efficiently in many arithmetic operations, in our case mainly for cosine similarity's calculation.
    # Each row represents a file of collection E and each column has size equal to the space vector.
    # We chose data type 'float16', which is a half precision float, due to memory errors during the execution of the program.
    vectors_for_collection_E = lil_matrix((number_of_files_in_E, space_length), dtype = 'float16')
    for i in range(len(list_of_files_in_E)):
        j = 0
        for temp_stem in space:
            # If a stem's term frequency or it's inverse document frequency isn't zero, it's TF-IDF is calculated.
            if(tf_for_collection_E[i][temp_stem] * inverse_document_frequency[temp_stem] > 0):
                vectors_for_collection_E[i,j] = tf_for_collection_E[i][temp_stem] * inverse_document_frequency[temp_stem]
            j += 1
    # Creating vectors for every file in collection A. We chose lil_matrix matrix again, for the same reasons as above.
    vectors_for_collection_A = lil_matrix((number_of_files_in_A, space_length), dtype = 'float16')
    for i in range(len(list_of_files_in_A)):
        j = 0
        for temp_stem in space:
            # If a stem's term frequency or it's inverse document frequency isn't zero, it's TF-IDF is calculated.
            if(tf_for_collection_A[i][temp_stem] * inverse_document_frequency[temp_stem] > 0):
                vectors_for_collection_A[i,j] = tf_for_collection_A[i][temp_stem] * inverse_document_frequency[temp_stem]
            j += 1
    # Printing time passed.
    print ">>>>>     Time:", time.time() - start_time - passed_time, "sec"
    passed_time = time.time() - start_time

    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "STAGE #5: COSINE SIMILARITY CALCULATION |---------------------------------"
    # Initialization of a dictionary to save the results and of a lil_matrix for cosine similarity results.
    collection_A_categorized_by_cosine = {} 
    cosine_similarity = lil_matrix((number_of_files_in_A, number_of_files_in_E), dtype = 'float16')
    # Calculation of dot product of vectors_for_collection_A's matrix and transpose vectors_for_collection_E's matrix.
    dot_product = vectors_for_collection_A.dot(vectors_for_collection_E.transpose()).todense()
    # Partial multiplications that are required.
    multiply_A = vectors_for_collection_A.multiply(vectors_for_collection_A).sum(1)
    multiply_E = vectors_for_collection_E.multiply(vectors_for_collection_E).sum(1).transpose()
    # Calculation of cosine similiarity.
    cosine_similarity = divide(dot_product, sqrt(multiply(multiply_A, multiply_E)))
    # Indices of max values.
    max_values = cosine_similarity.argmax(axis = 1)
    # Appending appropriate category to every file in collection A.
    for i in range(number_of_files_in_A):
        collection_A_categorized_by_cosine[list_of_files_in_A[i]] = collection_E_categorized[list_of_files_in_E[max_values[i,0]]]
    # Initialization of several counters used.
    file_no = 0
    files_from_rec_to_rec_by_cosine = 0
    files_from_sci_to_sci_by_cosine = 0
    # Opening a file to save above results in a file for later check.
    result_of_cosine = open('C:\\lt\\Askisi-A-Corpus\\result_of_cosine.txt', 'w')
    # Loop for every categorized file.
    for temp_file, temp_category in collection_A_categorized_by_cosine.items():
        # Writing to previous file.
        result = str(file_no) + "\tFile: " + temp_file + "  >  Category: " + temp_category + "\n"
        result_of_cosine.write(result)
        file_no += 1
        # Counting statistics for precision computation.
        if temp_file in list_of_files_in_A_rec:
            if (temp_category == 'rec'):
                files_from_rec_to_rec_by_cosine += 1
        if temp_file in list_of_files_in_A_sci:
            if (temp_category == 'sci'):
                files_from_sci_to_sci_by_cosine += 1   
    # Closing file.
    result_of_cosine.close()
    # Printing time passed.
    print ">>>>>     Time:", time.time() - start_time - passed_time, "sec"
    passed_time = time.time() - start_time

    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"       
    print "STAGE #6: TANIMOTO SIMILARITY CALCULATION |-------------------------------"
    # Initialization of a dictionary to save the results and of an array for maximum Tanimoto values.
    collection_A_categorized_by_tanimoto = {}
    max_tanimoto = [] * number_of_files_in_A
    # Loop for every file in collection A.
    for i in range(number_of_files_in_A):
        # Setting maximum Tanimoto value to zero.
        max_tanimoto.append(0)
        # Loop for every file in collection E.
        for k in range(number_of_files_in_E):
            # Calculating common stems between file in collection A and file in collection E.
            intersection = [common_item for common_item in stems_of_each_file_in_A[i] if common_item in stems_of_each_file_in_E[k]]
            # Calculation of Tanimoto similarity. If it is larger than current maximum value, it becomes the maximum one.
            tanimoto_similarity = len(intersection)/float(len(stems_of_each_file_in_A[i])+len(stems_of_each_file_in_E[k])-len(intersection))
            if (tanimoto_similarity > max_tanimoto[i]):
                max_tanimoto[i] = tanimoto_similarity
                file_no_where_max_is = k # Saving the position of the file with maximum Tanimoto value.
        # Appending appropriate category to every file in collection A. 
        collection_A_categorized_by_tanimoto[list_of_files_in_A[i]] = collection_E_categorized[list_of_files_in_E[file_no_where_max_is]]
    # Initialization of several counters used.
    file_no = 0
    files_from_rec_to_rec_by_tanimoto = 0
    files_from_sci_to_sci_by_tanimoto = 0
    # Opening a file to save above results in a file for later check.
    result_of_tanimoto = open('C:\\lt\\Askisi-A-Corpus\\result_of_tanimoto.txt', 'w')
    # Loop for every categorized file.
    for temp_file, temp_category in collection_A_categorized_by_tanimoto.items():
        # Writing to previous file.
        result = str(file_no) + "\tFile: " + temp_file + "  >  Category: " + temp_category + "\n"
        result_of_tanimoto.write(result)
        file_no += 1
        # Counting statistics for precision computation.
        if temp_file in list_of_files_in_A_rec:
            if (temp_category == 'rec'):
                files_from_rec_to_rec_by_tanimoto += 1
        if temp_file in list_of_files_in_A_sci:
            if (temp_category == 'sci'):
                files_from_sci_to_sci_by_tanimoto += 1
    # Closing file.
    result_of_tanimoto.close()
    # Printing time passed.
    print ">>>>>     Time:", time.time() - start_time - passed_time, "sec"
    passed_time = time.time() - start_time

    # -------------------------------------------------------------------------------------------------------------------------------------|
    print "--------------------------------------------------------------------------"
    print "STAGE #7: TIME & RESULTS |------------------------------------------------"
    # Calculating all files that were correctly categorized using cosine.
    correct_files_using_cosine = files_from_rec_to_rec_by_cosine + files_from_sci_to_sci_by_cosine
    # Calculating the precision of cosine method & printing the result.
    cosine_precision = (correct_files_using_cosine / float(number_of_files_in_A)) * 100
    print ">>>>>     Cosine's precision:", cosine_precision, "%"
    # Calculation of recall for cosine similarity.
    #rec_recall_cosine = files_from_rec_to_rec_by_cosine / float(len(list_of_files_in_A_rec))
    #sci_recall_cosine = files_from_sci_to_sci_by_cosine / float(len(list_of_files_in_A_sci))
    #cosine_recall = ((rec_recall_cosine + sci_recall_cosine)/float(2)) * 100
    #print ">>>>>     Cosine's recall:", cosine_recall, "%"
    # Calculating all files that were correctly categorized using Tanimoto.
    correct_files_using_tanimoto = files_from_rec_to_rec_by_tanimoto + files_from_sci_to_sci_by_tanimoto
    # Calculating the precision of Tanimoto method & printing the result.
    tanimoto_precision = (correct_files_using_tanimoto / float(number_of_files_in_A)) * 100
    print ">>>>>     Tanimoto's precision:", tanimoto_precision, "%"
    # Calculation of recall for Tanimoto similarity.
    #rec_recall_tanimoto = files_from_rec_to_rec_by_tanimoto / float(len(list_of_files_in_A_rec))
    #sci_recall_tanimoto = files_from_sci_to_sci_by_tanimoto / float(len(list_of_files_in_A_sci))
    #tanimoto_recall = ((rec_recall_tanimoto + sci_recall_tanimoto)/float(2)) * 100
    #print ">>>>>     Tanimoto's recall:", tanimoto_recall, "%"
    # Printing total time passed since the beginning of the program.
    print ">>>>>     Total time:", time.time() - start_time, "sec"
    print "--------------------------------------------------------------------------"
# -----------------------------------------------------------------------------------------------------------------------------------------|
# -----------------------------------------------------------------------------------------------------------------------------------------|