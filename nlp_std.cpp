#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <ctime>
#include <cstring>
#include <cstdlib>

using namespace std;

map<string, map<string,int> > dict;
map<string, map<string,int> >::iterator mit;

map< pair<string, string>, map<string, int> > model2;
map< pair<string, string>, map<string, int> >::iterator myit;
map<string, int>::iterator cit;

map<string,int> keyboard;


clock_t start, mid, end;

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
	if (s == "ive")
		t = "I've";
	if (s == "ill")
		t = "I'll";
	return t;
}

int editd(string str1, string str2)
{
    int max1 = str1.size();
    int max2 = str2.size();

    int **ptr = new int*[max1 + 1];
    for(int i = 0; i < max1 + 1; i++)
    {
        ptr[i] = new int[max2 + 1];
    }

    for(int i = 0; i < max1 + 1; i++)
    {
        ptr[i][0] = i;
    }

    for(int i = 0; i < max2 + 1; i++)
    {
        ptr[0][i] = i;
    }

    for(int i = 1; i < max1 + 1; i++)
    {
        for(int j = 1; j< max2 + 1; j++)
        {
            int d;
            int temp = min(ptr[i-1][j] + 1, ptr[i][j-1] + 1);
            if (str1[i-1] == str2[j-1])
                d = 0 ;
            else
                d = 1 ;
            ptr[i][j] = min(temp, ptr[i-1][j-1] + d);
        }
    }

    int dis = ptr[max1][max2];

    for (int i = 0; i < max1 + 1; i++)
    {
        delete[] ptr[i];
        ptr[i] = NULL;
    }

    delete[] ptr;
    ptr = NULL;
    return dis;
}

float editd_2(string str1, string str2)
{
	
    int max1 = str1.size();
    int max2 = str2.size();

    float **ptr = new float*[max1 + 1];
    for (int i=0; i<max1+1; i++)
        ptr[i] = new float[max2 + 1];

    for (int i=0 ;i<max1+1; i++)
        ptr[i][0] = i;

    for (int i=0; i<max2+1; i++)
        ptr[0][i] = i;

    for (int i=1; i<max1+1; i++)
        for (int j=1; j<max2+1; j++)
        {
            float d;
            float temp = min(ptr[i-1][j] + 1, ptr[i][j-1] + 1);
            if (str1[i-1] == str2[j-1])
                d = 0;
            else
            {
            	string tmp1 = "ab",tmp2 = "ab";
            	tmp1[0] = str1[i-1], tmp1[1] = str2[j-1];
            	tmp2[0] = str2[j-1], tmp2[1] = str1[i-1];  
            	if (keyboard.count(tmp1)!=0 || keyboard.count(tmp2)!=0)
                	d = 0.3;
                else
                	d = 1;
            }
            ptr[i][j] = min(temp, ptr[i-1][j-1] + d);
        }

    float dis = ptr[max1][max2];

    for (int i=0; i<max1+1; i++)
    {
        delete[] ptr[i];
        ptr[i] = NULL;
    }
    delete[] ptr;
    ptr = NULL;
    return dis;
}

void train_bi()
{
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
}

void train_tri()
{
	fstream x("cootek_sjtu/train.txt");
	string linex;
	
	while (getline(x, linex))
	{
		
		int pos1 = linex.rfind(' ');
		int pos2 = linex.rfind(' ', pos1-1);
		int pos3 = linex.rfind(' ', pos2-1);
		string preword;
		if (pos2 == 0)
			preword = "<ss>";
		else
			preword = linex.substr(pos3+1, pos2-pos3-1);
		string currentword = linex.substr(pos2+1, pos1-pos2-1);
		string trueword = linex.substr(pos1+1);

		pair <string,string> strpair;
		strpair = make_pair(preword, currentword);
		if (model2[strpair].count(trueword) == 0)
			model2[strpair][trueword] = 1;
		else
			model2[strpair][trueword] ++;
	}
	x.close();
}


int main()
{
	cout<< "Training...Please Wait..."<<endl<<endl;
keyboard["qw"] = 1,keyboard["we"] = 1,keyboard["er"] = 1,keyboard["rt"] = 1,keyboard["ty"] = 1,keyboard["yu"] = 1,
keyboard["ui"] = 1,keyboard["io"] = 1,keyboard["op"] = 1,keyboard["as"] = 1,keyboard["sd"] = 1,keyboard["df"] = 1,
keyboard["fg"] = 1,keyboard["gh"] = 1,keyboard["hj"] = 1,keyboard["jk"] = 1,keyboard["kl"] = 1,keyboard["zx"] = 1,
keyboard["xc"] = 1,keyboard["cv"] = 1,keyboard["vb"] = 1,keyboard["bn"] = 1,keyboard["nm"] = 1;
	
	start = clock();

	train_bi();
	train_tri();

	mid = clock();
	/***** testing on the dataset *****/
	string linec;
	int n = 0, n_1 = 0, n_2 = 0, n_3 = 0, n_4 = 0;
	int ncorrect = 0, n_1_c = 0, n_2_c = 0, n_3_c = 0, n_4_c = 0;
	int nspecial = 0;

	cout<<"Start typing now! (Enter * to terminate)"<<endl;
	while (getline(cin, linec))
	{
		if (linec == "*")
			break;
		// cout<<linec<<endl;
		n++;
		int pos1 = linec.rfind(' ');
		int pos2 = linec.rfind(' ', pos1-1);
		string preword;
		if (pos1 == 0)
			preword = "<ss>";
		else
			preword = linec.substr(pos2+1, pos1-pos2-1);
		string currentword = linec.substr(pos1+1);

		string predictword;

		pair <string,string> strpair;
		strpair = make_pair(preword, currentword);



		if (model2.count(strpair) != 0)
		{
			n_1 ++;
			int max_cnt = 0;
			map<string, int> maptmp;
			maptmp = model2[strpair];
			predictword = currentword;
			for (cit = maptmp.begin(); cit != maptmp.end(); ++cit)
			{

				int cnt = cit -> second;
				/* parameter here */
				if (cnt < 1)
					continue;
				if (cnt > max_cnt)
				{
					max_cnt = cnt;
					predictword = cit -> first;
				}
			}
		}
		else
		/* case 3 */
		{
			if (dict.count(currentword) != 0 && dict[preword].count(currentword)!=0)
			{
				n_3++;
				predictword = currentword;
				if (preword == "<s>")
				{
					predictword[0] = toupper(predictword[0]);
				}
				predictword = specialstr(currentword, predictword);

			}
			else
			{
				n_4++;
				predictword = currentword;

				double mind = 1;
				if (dict.count(preword) == 0)
				{
					1;
				}
				else
				{
					for (cit = dict[preword].begin(); cit!= dict[preword].end(); ++cit)
					{
						string ltmp = cit -> first;
						if (cit->second < 3)
							continue;
						double dtmp = editd_2(ltmp, currentword);
						if (dtmp <= mind)
						{
							mind = dtmp;
							predictword = ltmp;
						}
					}
					// cout<<linec<<endl;
				}


				if (preword == "<s>")
				{
					predictword[0] = toupper(predictword[0]);
				}
				predictword = specialstr(currentword, predictword);
	
			}
		}
		cout<<predictword<<endl;
	}
	/***** testing end *****/

	end = clock();

	//cout<<"special characters: "<<nspecial<<endl;
	//cout<<"training time: "<<double(mid - start) / CLOCKS_PER_SEC<<endl<<"testing time: "<<double(end - mid) / CLOCKS_PER_SEC <<endl;

	
	
	return 0;
} 
