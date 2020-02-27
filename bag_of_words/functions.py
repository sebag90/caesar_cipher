#!/usr/bin/python3

import cistem as cistem
import os
import math          
# from nltk.stem.snowball import SnowballStemmer


# retrieve articles
def retrieve_articles():
    strings = {}
    for filename in os.listdir('./bestand'):
        path = "./bestand/" + filename
        with open(path, "r") as file:
            my_string = file.read()
            strings[filename] = my_string
    return strings


# manual string manipulation
def clean_string(input_str):
    cln_str = input_str.replace("[", " ")
    cln_str = cln_str.replace("]", " ")
    cln_str = cln_str.replace("(", " ")
    cln_str = cln_str.replace(")", " ")
    cln_str = cln_str.replace(", ", " ")
    cln_str = cln_str.replace(". ", " ")
    cln_str = cln_str.replace("; ", " ")
    cln_str = cln_str.replace(": ", " ")
    cln_str = cln_str.replace("?", " ")
    cln_str = cln_str.replace("!", " ")
    cln_str = cln_str.replace("""'""", " ")
    cln_str = cln_str.replace('"', " ")
    cln_str = cln_str.replace("""„""", " ")
    cln_str = cln_str.replace("""“""", " ")
    return cln_str


# collect stop words after removing whitespaces and /n
def collect_stopwords():
    nonowords = []
    with open("stopwords.txt") as stopwords:
        for word in stopwords:
            newword = word.replace(" ", "")
            newword2 = newword.replace("\n", "")
            nonowords.append(newword2)
    return nonowords


# remove stopwords and stem a string
def str_2_vec(input_string, nonowords):
    # extract single words
    splits = input_string.split()
    cleaned = []
    stemmed = []
    # if word is not a stop word, save it in a new list (vector)
    for something in splits:
        if something.lower() not in nonowords:
            cleaned.append(something)
    # stem
    # stemmer = SnowballStemmer("german")
    for element in cleaned:
        # stemmed.append(stemmer.stem(element))
        stemmed.append(cistem.stem(element))
    return stemmed


# create matrix term list
def create_matrix_terms(_articles):
    matrix_terms = []
    for key in _articles:
        for term in _articles[key]:
            if term not in matrix_terms:
                matrix_terms.append(term)
    return matrix_terms
        

# calculate TF vector for every stemmed document
def calculate_vec(matrix_terms, stemmed_list):
    string_vec = []
    for single_term in matrix_terms:
        counter = 0 
        for term in stemmed_list:
            if single_term == term:
                counter = counter + 1
        string_vec.append(counter)
    return string_vec


# calculate the number of document in which every term is present
def calc_freq(_articles, matrix_terms):
    counters = []
    for term in matrix_terms:
        counter = 0
        for key in _articles:
            if term in _articles[key]:
                counter = counter + 1
        counters.append(counter)
    return counters


# calculate TF * IDF (1 + log(n/nj))
def calc_tf_idf (_articles, freq_list):
    n = len(_articles)
    for key in _articles:
        for i in range(len(freq_list)):
            _articles[key][i] = _articles[key][i] * (1 + math.log(n/freq_list[i]))
    return _articles


# calculate cos similarity
def find_best_match(_articles):
    results = {}
    for key in _articles:
        if key != "query":
            # point product, length vector query, length vector n
            pprod = 0
            len_q = 0
            len_n = 0
            for i in range(len(_articles[key])):
                pprod = pprod + _articles[key][i] * _articles["query"][i] 
                len_n = len_n + ((_articles[key][i])**2)
                len_q = len_q + ((_articles["query"][i])**2)
            cos = pprod / math.sqrt(len_n * len_q)
            results[key] = cos
    return results