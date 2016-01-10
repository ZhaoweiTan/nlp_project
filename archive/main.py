def syn(s, freq):
	return float(freq) / s / s 

import nltk
import time
from nltk import bigrams
from nltk.metrics import *

start = time.clock()


f = open('cootek_sjtu/english.corpus')


# train the bigram model and calculate the frequency
d1 = {}

for line in f:
	if line[-1] == '\n':
		line = line[:-1]
	line = "<s> "+line # add the extra starting symbol
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

mid = time.clock()
print mid - start

# end of the training




# begin testing

n = 0 # n is the total num of the testing data
ncorrect = 0 # corrent returned answer

g = open('cootek_sjtu/train.txt')
for line in g:
	n = n + 1
	if line[-1] == '\n':
		line = line[:-1]
	l = line.split(' ')

	preword = l[-3]
	trueword = l[-1]
	partword = l[-2]
	
	chosen = ""
	if preword in d1:
		candidate_set = d1[preword]
		maxscore = 0
		for key in candidate_set:
			freq = candidate_set[key]
			if freq <= 2:
				continue
			dist = edit_distance(key, partword)
			if dist == 0:
				chosen = key
				break
			score = syn(dist, freq)
			if score > maxscore:
				maxscore = score
				chosen = key
		if chosen == trueword:
			ncorrect = ncorrect + 1
	else:
		chosen = partword
		if chosen == trueword:
			ncorrect = ncorrect + 1
	if n == 500:
		break
print n, ncorrect
g.close()

end = time.clock()
print end - start
