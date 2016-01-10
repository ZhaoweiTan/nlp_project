#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <ctime>
#include <cstring>

using namespace std;
map<string,int> namelist;

clock_t start, mid, end;

int editd(string str1, string str2)
{
    int max1 = str1.size();
    int max2 = str2.size();

    int **ptr = new int*[max1 + 1];
    for(int i = 0; i < max1 + 1 ;i++)
    {
        ptr[i] = new int[max2 + 1];
    }

    for(int i = 0 ;i < max1 + 1 ;i++)
    {
        ptr[i][0] = i;
    }

    for(int i = 0 ;i < max2 + 1;i++)
    {
        ptr[0][i] = i;
    }

    for(int i = 1 ;i < max1 + 1 ;i++)
    {
        for(int j = 1 ;j< max2 + 1; j++)
        {
            int d;
            int temp = min(ptr[i-1][j] + 1, ptr[i][j-1] + 1);
            if(str1[i-1] == str2[j-1])
            {
                d = 0 ;
            }
            else
            {
                d = 1 ;
            }
            ptr[i][j] = min(temp, ptr[i-1][j-1] + d);
        }
    }

    int dis = ptr[max1][max2];

    for(int i = 0; i < max1 + 1; i++)
    {
        delete[] ptr[i];
        ptr[i] = NULL;
    }

    delete[] ptr;
    ptr = NULL;
    return dis;
}


string specialstr(string s, string t)
{
	if (s == "i")
		t = "I";
	if (s == "dont")
		t = "don't";
	if (s == "its")
		t = "it's";
	if (s == "cant")
		t = "can't";
	if (s == "im")
		t = "I'm";
	
	if (s == "ill" || s == "i'll")
		t = "I'll";
	
	if (s == "wasnt")
		t = "wasn't";
	
	if (s == "thats")
		t = "that's";
	
	if (s == "sunday" || s == "monday" || 
		s == "tuesday" || s == "wednesday" || 
		s == "thursday" || s == "friday" || s == "saturday")
	{
		t = s;
		t[0] = toupper(t[0]);
	}
	if (namelist.count(s) != 0)
	{
		t = s;
		t[0] = toupper(t[0]);
		// cout<< s<<" ";
	}

	return t;
}



int main()
{
	start = clock();


	fstream name1("special_word.txt");
	string anewname;
	while (getline(name1, anewname))
	{
		anewname[0] = tolower(anewname[0]);
		namelist[anewname] = 0;
	}
	name1.close();


	/***** training the model *****/
	map<string, map<string,int> > dict;
	map<string, map<string,int> >::iterator mit;
	map<string,int> mydict;
	map<string,int>::iterator cit;

	fstream g("cootek_sjtu/english.corpus");
	string linet;
	int m = 0;
	while (getline(g, linet))
	{
		int pos_a = 0, pos_b;
		string pre = "<s>";
		while (true)
		{
			pos_b = linet.find(' ', pos_a);
			string word;
			if (pos_b == -1)
			{
				word = linet.substr(pos_a);
				// cout<<"*"<<word<<"*"<<endl;
				if (dict[pre].count(word) == 0)
					dict[pre][word] = 1;
				else
					dict[pre][word]++;
				break;
			}
			word = linet.substr(pos_a, pos_b-pos_a);
			// cout<<"*"<<word<<"*"<<endl;
			if (dict[pre].count(word) == 0)
				dict[pre][word] = 1;
			else
				dict[pre][word]++;
			pre = word;
			pos_a = pos_b + 1; 
		}
		// cout<<linet<<endl;
		m = m + 1;
		if (m == 100000)
			break;
	}
	g.close();
	cout<<"the size of the dictionary is "<<dict.size()<<endl;
	// cout<<dict["<s>"].size()<<endl;

	mid = clock();
	/***** training end *****/









	/***** testing on the dataset *****/
	fstream f("cootek_sjtu/train.txt");
	string linec;
	int n = 0, n_1 = 0, n_2_1 = 0, n_2_2 = 0, n_3 = 0;
	int ncorrect = 0, n_1_c = 0, n_2_1_c = 0, n_2_2_c = 0, n_3_c = 0;
	int nspecial = 0;


	fstream h("ans.txt");

	while (getline(f, linec))
	{
		int pos1 = linec.rfind(' ');
		int pos2 = linec.rfind(' ', pos1-1);
		int pos3 = linec.rfind(' ', pos2-1);
		string preword;
		if (pos2 == 0)
			preword = "<ss>";
		else
			preword = linec.substr(pos3+1, pos2-pos3-1);
		string currentword = linec.substr(pos2+1, pos1-pos2-1);
		string trueword = linec.substr(pos1+1);
		// cout<<preword<<' '<<currentword<<' '<<trueword<<endl;

		string predictword;
		if (preword == "a" || preword == "an" || preword == "the")
			nspecial++;
		mit = dict.find(preword);
		if (mit != dict.end())
		{
			mydict = mit->second;
			cit = mydict.find(currentword);
			

			/***** the combo has occurs *****/
			if (cit != mydict.end())
			{
				n_1++;
				predictword = currentword;
				if (cit -> second >= 1)
				{	

					predictword = specialstr(currentword, predictword);

					if (preword == "<s>")
						predictword[0] = toupper(predictword[0]);
					

					if (predictword == trueword)
						ncorrect++, n_1_c++;
				}
				// else
				// {
				// 	int maxc = 0;
				// 	for (cit = mydict.begin(); cit != mydict.end(); ++cit)
				// 	{
				// 		if (cit -> second <= 1000)
				// 			continue;
				// 		string dictword = cit -> first;
				// 		int d = editd(dictword, currentword);
				// 		if (d <= 2 && cit -> second > maxc)
				// 		{
				// 			predictword = dictword;
				// 			maxc = cit -> second;
				// 		}
				// 	}
				// 	if (preword == "<s>")
				// 		predictword[0] = toupper(predictword[0]);
				// 	if (predictword == trueword)
				// 		ncorrect++,n_1_c++;
				// }
			}


			/***** previous word is in but the combo is not *****/
			else
			{
				/***** and this word is not in the dictionary (probably misspell, currently worst dealed) *****/
				// best parameter by far: mind = 2, maxs = 0
				if (dict.count(currentword) == 0)
				{
					predictword = currentword;
					static double mind = 2;
					float maxs = 0;
					n_2_1++;
					for (cit = mydict.begin(); cit != mydict.end(); ++cit)
					{
						string dictword = cit -> first;
						int d = editd(dictword, currentword);
						if (d < mind && double(cit -> second)/d/d > maxs)
						{
							predictword = dictword;
							maxs = double(cit -> second)/d/d;
						}
					}
					predictword = specialstr(currentword, predictword);
					if (preword == "<s>")
						predictword[0] = toupper(predictword[0]);
					if (predictword == trueword)
						ncorrect++,n_2_1_c++;
				}
				/***** the case ends *****/


				/***** this word is in the dictionary *****/
				// best parameters: /d/d, maxs = 0, mind2 = 2, second < 10
				else
				{
					predictword = currentword;
					static double mind2 = 2;
					float maxs = 0;
					for (cit = mydict.begin(); cit != mydict.end(); ++cit)
					{
						if (cit -> second < 10)
							continue;
						string dictword = cit -> first;
						int d = editd(dictword, currentword);
						if (d < mind2 && double(cit -> second)/d/d > maxs)
						{
							predictword = dictword;
							maxs = double(cit -> second)/d/d;
						}
					}
					n_2_2++;
					predictword = specialstr(currentword, predictword);
					if (preword == "<s>")
						predictword[0] = toupper(predictword[0]);
					if (predictword == trueword)
						ncorrect++,n_2_2_c++;
				}
				/***** the case ends *****/
				
			}
		}
		/***** the case ends *****/

		//if (predictword ==)

		/***** the previous word does not occur (probably a misspell, rare case, 2%) *****/
		else
		{
			// 去查字典
			n_3++;
			predictword = currentword;
			predictword = specialstr(currentword, predictword);
			if (predictword == trueword)
				ncorrect++,n_3_c++;		
		}
		/***** this case ends *****/


		/***** write the file *****/
		// h<<preword<<" "<<currentword<<" "<<trueword<<" *"<<predictword<<"*"<<endl;
		/***** writing end *****/


		n++;
		if (n == 10000) 
			break;
	}
	/***** testing end *****/



	/****** outputs *****/
	cout<<"category 1: "<<n_1_c<<"/"<<n_1<<endl;
	cout<<"category 2_1: "<<n_2_1_c<<"/"<<n_2_1<<endl;
	cout<<"category 2_2: "<<n_2_2_c<<"/"<<n_2_2<<endl;
	cout<<"category 3: "<<n_3_c<<"/"<<n_3<<endl;
	cout<<ncorrect<<" corrects out of "<<n<<endl;
	/***** output end *****/


	f.close();
	h.close();

	//cout<<"special characters: "<<nspecial<<endl;
	end = clock();
	cout<<"training time: "<<double(mid - start) / CLOCKS_PER_SEC<<endl<<"testing time: "<<double(end - mid) / CLOCKS_PER_SEC <<endl;

	
	
	return 0;
}