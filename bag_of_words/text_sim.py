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
    # stem and create matrix
    stemmer = SnowballStemmer("german")
    for element in cleaned:
        stemmed.append(stemmer.stem(element))
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
            pprod = 0
            lq = 0
            ln = 0
            for i in range(len(_articles[key])):
                pprod = pprod + _articles[key][i] * _articles["query"][i] 
                ln = ln + ((_articles[key][i])**2)
                lq = lq + ((_articles["query"][i])**2)
            cos = pprod / math.sqrt(ln * lq)
            results[key] = cos
    return results
            
            
def main():
    # TODO
    # add support for ENG/ITA
    
    # retrieve all articles from folder bestand and stopwords
    articles_org = retrieve_articles()
    stopwords = collect_stopwords()

    # clean the articles
    for element in articles_org:
        new_str = clean_string(articles_org[element])
        articles_org[element] = new_str

    # stem the articles
    for key in articles_org:
        articles_org[key] = str_2_vec(articles_org[key], stopwords)
    
    while True:
        user_input =  input("Enter data query or enter '...' to exit:\n> ")
        if user_input == "...":
            break
        # create a local copy of the cleaned and stemmed dict
        articles = articles_org.copy()

        # clean and stem user input
        cleaned_input = clean_string(user_input)
        stemmed_input = str_2_vec(cleaned_input, stopwords)
        articles["query"] = stemmed_input

        # create document matrix terms
        matrix_terms = create_matrix_terms(articles)

        # calculate frequency list for every term 
        freq_list = calc_freq(articles, matrix_terms)
        for key in articles:
            vec = calculate_vec(matrix_terms, articles[key])
            articles[key] = vec

        # calculate TF * IFD (1 - log(n/nj))
        articles = calc_tf_idf(articles, freq_list)   

        # calculate vector cos similarity and print out the best result
        results = find_best_match(articles)
        print(max(results.items(), key=operator.itemgetter(1))[0])
    

if __name__ == "__main__":
    main()