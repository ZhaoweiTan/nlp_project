The structure of this folder:


|-folder
|
|---archive (old versions of my work)
|   |---main.py
|   |---test.cpp
|   |---nlp.cpp 
|
|---nlp_train.cpp (Final version, using "g++ -O3 -Wno-write-strings nlp_train.cpp -o train" to compile.)
|
|---nlp_std.cpp (Final std in/out version, using "g++ -O3 -Wno-write-strings nlp_train.cpp -o train" to compile.)
|
|---res (Executable file to generate the final answer. Need corpus file.)
|
|---std (Executable file to std input and output. Need corpus file.)
|
|---nlp_project_report_tanzhaowei.pdf
|
|---ans.txt (output of the data)
|
|---readme.txt


(The estimated accuracy should be around 72%. If the result is dramatically below this, there might be a c++ formatting problem. Please let me know.)

May you have any question, please contact tanzw94@gmail.com. 

Zhaowei