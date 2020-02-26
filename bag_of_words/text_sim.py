from nltk.stem.snowball import SnowballStemmer
import os


# retrieve articles
def retrieve_articles():
    strings = []
    for filename in os.listdir('./bestand'):
        path = "./bestand/" + filename
        with open(path, "r") as file:
            my_string = file.read()
            strings.append(my_string)
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
    bella = bella.replace("""  ' """, " ")
    bella = bella.replace("""  " """, " ")
    bella = bella.replace(""" „ """, " ")
    bella = bella.replace("""  “ """, " ")
    return bella


def str_2_vec(input_string):
    # collect stop words after removing whitespaces and /n
    nonowords = []
    with open("stopwords.txt") as stopwords:
        for word in stopwords:
            newword = word.replace(" ", "")
            newword2 = newword.replace("\n", "")
            nonowords.append(newword2)
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


def create_matrix_terms(stemmed_lists):
    matrix_terms = []
    for single_list in stemmed_lists:
        for term in single_list:
            if term not in matrix_terms:
                matrix_terms.append(term)
    return matrix_terms
        
def calculate_matrix(matrix_terms, stemmed_lists):
    matrix = []
    string_vec = []
    for doc in stemmed_lists:
        for single_term in matrix_terms:
            counter = 0
            for term in doc:
                if single_term == term:
                    counter = counter + 1
            string_vec.append(counter)
        matrix.append(string_vec)
    return matrix


def main():
    articles = retrieve_articles()
    cleaned_strs = []
    for element in articles:
        new_str = clean_string(element)
        cleaned_strs.append(new_str)
    
    stemmed_lists = []
    for cleaned_string in cleaned_strs:
        stemmed_lists.append(str_2_vec(cleaned_string))
    
    matrix_terms = create_matrix_terms(stemmed_lists)
    matrix = calculate_matrix(matrix_terms, stemmed_lists)
    
    for line in matrix:
        print(line)
        print()
        print()
        
if __name__ == "__main__":
    main()