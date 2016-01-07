import nltk
from nltk import bigrams
s = "I really like python, it's pretty awesome.".split(" ")
string_bigrams = bigrams(s)
for grams in string_bigrams:
	print grams