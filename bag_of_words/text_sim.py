from nltk.stem.snowball import SnowballStemmer
import os
import math
import operator


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
def clean_string(stringa):
    bella = stringa.replace("[", " ")
    bella = bella.replace("]", " ")
    bella = bella.replace("(", " ")
    bella = bella.replace(")", " ")
    bella = bella.replace(", ", " ")
    bella = bella.replace(". ", " ")
    bella = bella.replace("; ", " ")
    bella = bella.replace(": ", " ")
    bella = bella.replace("?", " ")
    bella = bella.replace("!", " ")
    bella = bella.replace("""'""", " ")
    bella = bella.replace('"', " ")
    bella = bella.replace("""„""", " ")
    bella = bella.replace("""“""", " ")
    return bella


def collect_stopwords():
    # collect stop words after removing whitespaces and /n
    nonowords = []
    with open("stopwords.txt") as stopwords:
        for word in stopwords:
            newword = word.replace(" ", "")
            newword2 = newword.replace("\n", "")
            nonowords.append(newword2)
    return nonowords


def str_2_vec(input_string, nonowords):
    # extract single words
    splits = input_string.split()
    cleaned = []
    stemmed = []
    # if word is not a stop word, save it in a new list (vector)
    for something in splits:
        if something.lower() not in nonowords:
            cleaned.append(something)
    # stem and create matrix
    stemmer = SnowballStemmer("german")
    for element in cleaned:
        stemmed.append(stemmer.stem(element))
    return stemmed


def create_matrix_terms(_articles):
    matrix_terms = []
    for key in _articles:
        for term in _articles[key]:
            if term not in matrix_terms:
                matrix_terms.append(term)
    return matrix_terms
        

def calculate_vec(matrix_terms, stemmed_list):
    string_vec = []
    for single_term in matrix_terms:
        counter = 0 
        for term in stemmed_list:
            if single_term == term:
                counter = counter + 1
        string_vec.append(counter)
    return string_vec


def calc_freq(_articles, matrix_terms):
    counters = []
    for term in matrix_terms:
        counter = 0
        for key in _articles:
            if term in _articles[key]:
                counter = counter + 1
        counters.append(counter)
    return counters


def calc_tf_idf (_articles, freq_list):
    n = len(_articles)
    for key in _articles:
        for i in range(len(freq_list)):
            _articles[key][i] = _articles[key][i] * math.log(n/freq_list[i])
    return _articles
            

def find_best_match(_articles):
    results = {}
    for key in _articles:
        if key != "query":
            pprod = 0
            lq = 0
            ln = 0
            for i in range(len(_articles[key])):
                pprod = pprod + _articles[key][i] * _articles["query"][i] 
                ln = ln + ((_articles[key][i])**2)
                lq = lq + ((_articles["query"][i])**2)
            cos = pprod / (1 + math.sqrt(ln * lq))
            results[key] = cos
    return results
            
            
def main():
    articles = retrieve_articles()
    stopwords = collect_stopwords()
    articles["query"] =  input("Enter data query:\n> ")
    
    for element in articles:
        new_str = clean_string(articles[element])
        articles[element] = new_str
     
    for key in articles:
        articles[key] = str_2_vec(articles[key], stopwords)
    
    matrix_terms = create_matrix_terms(articles)

    freq_list = calc_freq(articles, matrix_terms)
     
    for key in articles:
        vec = calculate_vec(matrix_terms, articles[key])
        articles[key] = vec


    articles = calc_tf_idf(articles, freq_list)


    # print (matrix_terms)
    # for key in articles:
    #     print(key, "\t",  articles[key])
    

    results = find_best_match(articles)
    print(max(results.items(), key=operator.itemgetter(1))[0])
    

if __name__ == "__main__":
    main()