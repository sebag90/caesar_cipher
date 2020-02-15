from nltk.stem.snowball import SnowballStemmer


#take input sentence and remove punctuation
ciao = input("Sentence Pleeeeeeease:\n> ")
bella = ciao.replace(", ", " ")
bella = bella.replace(". ", " ")
bella = bella.replace("; ", " ")
bella = bella.replace(": ", " ")
bella = bella.replace("?", " ")
bella = bella.replace("!", " ")


#extract single words
splits = bella.split()
cleaned = []
nonowords = []


#collect stop words
with open ("stopwords.txt") as stopwords:
    for word in stopwords:
        newword = word.replace(" ", "")
        newword2 = newword.replace("\n", "")
        nonowords.append(newword2)


#save non stop words in clean list
for something in splits:
    if something.lower() not in nonowords:
        cleaned.append(something)


#stem
stemmer = SnowballStemmer("german")


#print out stems
print()
for element in cleaned:
    print(stemmer.stem(element))
print()