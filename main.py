import nltk
from nltk import bigrams

f = open('cootek_sjtu/train.txt')

d1 = {}

testnum = 0
for line in f:
	if line[-1] == '\n':
		line = line[:-1]
	l = line.split(' ')
	del(l[-2])
	string_bigrams = bigrams(l)
	for grams in string_bigrams:
		if not grams[0] in d1:
			d1[grams[0]] = {}
		d2 = d1[grams[0]]
		if not grams[1] in d2:
			d2[grams[1]] = 0
		d2[grams[1]] = d2[grams[1]] + 1