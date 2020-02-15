import nltk
from nltk import Tree


grammar = nltk.CFG.fromstring("""

S -> NP VP
PP -> P NP
NP -> Det N | Det Adj N
VP -> V | VP NP | VP S 
Det -> 'der' | 'die'
Adj -> 'dumme'
N -> 'hund' | 'katze'
V -> 'sieht' | 'rennt'

""")

sent = ['die', 'dumme', 'katze', 'sieht', 'die', 'hund', 'die', 'dumme', 'katze', 'sieht', 'die', 'hund']
parser = nltk.ChartParser(grammar)
for tree in parser.parse(sent):
    print (tree)
    #tree.draw()
