import nltk
from nltk import bigrams

f = open('cootek_sjtu/train.txt')

d1 = {}

testnum = 0
for line in f:
	if line[-1] == '\n':
		line = line[:-1]
	l = line.split(' ')
	string_bigrams = bigrams(l)
	for grams in string_bigrams:
		if not grams[0] in d1:
			d1[grams[0]] = {}
		d2 = d1[grams[0]]
		if not grams[1] in d2:
			d2[grams[1]] = 0
		d2[grams[1]] = d2[grams[1]] + 1
f.close()

print "train_close"


n = 0
ncorrect = 0


f = open('cootek_sjtu/english.corpus.txt')
for line in f:
	n = n + 1
	if line[-1] == '\n':
		line = line[:-1]
	l = line.split(' ')
	preword = l[-3]
	trueword = l[-1]
	partword = l[-2]
	if preword in d1:
		candi = d1[preword]
		maxn = 0
		for key in candi:
			if candi[key] > maxn:
				maxn = candi[key]
				chosen = key
		if chosen == trueword:
			ncorrect = ncorrect + 1

print n, ncorrect
f.close()