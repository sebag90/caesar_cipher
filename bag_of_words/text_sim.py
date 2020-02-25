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
def clean_string(ciao):
    cleaned_strings = []
    for stringa in ciao:
        bella = stringa.replace(", ", " ")
        bella = bella.replace(". ", " ")
        bella = bella.replace("; ", " ")
        bella = bella.replace(": ", " ")
        bella = bella.replace("?", " ")
        bella = bella.replace("!", " ")
        cleaned_strings.append(bella)
    return cleaned_strings


def str_2_vec(input_string):
    # extract single words
    splits = input_string.split()
    cleaned = []
    nonowords = []
    stemmed = []
    # collect stop words after removing whitespaces and /n
   with open("stopwords.txt") as stopwords:
        for word in stopwords:
            newword = word.replace(" ", "")
            newword2 = newword.replace("\n", "")
            nonowords.append(newword2)
    # if word is not a stop word, save it in a new list (vector)
    for something in splits:
        if something.lower() not in nonowords:
            cleaned.append(something)
    # stem
    stemmer = SnowballStemmer("german")
    for element in cleaned:
        stemmed.append(stemmer.stem(element))
    return stemmed


print(clean_string(retrieve_articles()))
