# NLP Assignment #

## Objective ##

To build an English IME engine.

## Resource ##

A training set containing a million cases is provided. A small, optional English corpus of the size 380MB is also provided but you are free to use any other corpora to build the language model.

### Training set ###

The training set has a million lines, each of which is a case in the following format:

> {history1} {history2} ... {input keys} {desired result}

For example, if the line is:

> I'm looking forw forward

It means the history words are "I'm" and "looking", and the user's input keys are "f", "o", "r", and "w", while the desired result is "forward".

### Test set ###

The format of the test set is the same of the training set except that we remove the final part, the desired word result. Your program will read the file of test set and print the predicted words. We'll then compare your output with the desired word results of the test set, and report the correction rate.

### Corpus ###

The 380MB corpus contains about six million "English" sentences. You can use it to train your language model.

### Notes ###

* "<s>" is the Beginning of Sentence mark.
* Not all the data in the files are perfectly formatted, as in the real world. For example, there are leading spaces, capitalized or uncapitalized words after "<s>", and multiple, consecutive "<s>" occurrences. There were even non-English words in the corpus.

## Evaluation ##

* You must submit your code and your programs as well as Makefiles if applicable.
* The program must read from stdin and write to stdout:

> Sample Input:
>
> <s> I'm looking forw
> want waht
>
> Sample Output:
>
> forward
> what

* We also provide demo.c and demo.py to demonstrate the I/O format.
* We'll run your program against our test set and report the correction rate.
* We'll score by your ranking in the class.
