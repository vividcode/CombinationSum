// onedollar.cpp : Defines the entry point for the console application.

#define DO_LOG		//comment this out to turn off result log

#include <ctime>
#include <iostream> 
#include<fstream>
#include <iomanip> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <map>
#include <deque> 
#include <set> 
#include <map> 
#include <bitset> 
#include <valarray> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <complex> 
#include <utility> 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cctype> 
#include <cmath> 
#include <queue> 
#include <iosfwd>
#include <conio.h>
using namespace std;

int a[] = {1,5,25,50};

void printvect(vector <map<int, int> > &vect)
{
	for (int i=0; i<vect.size(); i++)
	{
           map<int, int>::const_iterator iter;           

           
	   for(iter = vect[i].begin(); iter != vect[i].end(); iter++)        
               cout << (*iter).first << " : " << (*iter).second <<"  ";                           

           cout<<endl;
	}       
        
        cout<<"\r\nTotal No of combinations:"<<vect.size()<<endl; 
}

void logvect(vector <map<int, int> > &vect, const char * filename)
{
	ofstream outfile(filename, ios_base::app);
        
	for (int i=0; i<vect.size(); i++)   
	{          
	   map<int, int>::const_iterator iter;      

           for(iter = vect[i].begin(); iter != vect[i].end(); iter++)     		
	       outfile<<(*iter).first << " : " << (*iter).second <<"  ";
		
	   outfile<<"\r\n"<<endl;
	}
	outfile<<"\r\nTotal No of combinations:"<<vect.size()<<endl;
        outfile.close ();
}

void logtext(const char * message, const char * filename)
{
      ofstream outfile(filename);

      outfile<<message<<endl;

      outfile.close ();
}

void appendvect(vector <map<int, int> > &dest, vector <map<int, int> > &src)
{
	for (int i=0; i<src.size(); i++)
		dest.push_back (src[i]);
}

vector<map<int, int> > BruteForceTest(int a, int b, int c, int d, int S)
{
	vector<map<int, int> > retVect;
	int w, x, y, z;
	int count = 0;	
        
        for (w=0; w<=S/c; w++) 	
        {		
      	    for (x=0; x<=S/c; x++) 
      	    {		
		for (y=0; y<=S/b; y++) 
		{
		     for (z=0; z<=S/a; z++) 
			   {
		     	      int val= w*d + x*c + y*b + z*a;
		     	      if (val == 100)
		     	      {		
		     	      	   map<int, int> temp;
                                   temp[a] = z;
                                   temp[b] = y;
                                   temp[c] = x;
                                   temp[d] = w;      	
		     	      	   retVect.push_back(temp);
		     	      }
		     }
		}	
	    }
        }	    
	return retVect;	
}


vector<map<int, int> > Comb1(int a, int S)
{
	vector<map<int, int> > retVect;
	map<int, int> temp;

        temp[a] = (int)S/a;
	retVect.push_back (temp);

	return retVect;
}

vector<map<int, int> > Comb2(int a, int b, int S)
{
	int divisorA = (S-b)/a;		//for 5, 25 and Sum = 100, we take at least 1 25 and rest of 5s...
	int divisorB = (S-a)/b;
	vector<map<int, int> > retVect;	
	
	for (int i=1; i<= divisorA; i++)
	{		
		for (int j=1; j<= divisorB; j++)
		{
			int val = a*i + b*j;
			if (val == S)
			{		
				map<int, int> temp;
				temp[a] = i;				
				temp[b] = j;			

				retVect.push_back (temp);
				break;
			}
		}
	}	

	return retVect;
}

vector<map<int, int> > Comb3(int a, int b, int c, int S)
{
	vector<map<int, int> > retVect;	
        int count=0;

	for (count=1; count<(S/c); count++)
	{
		vector<map<int, int> > temp1 = Comb2(a, b, S-(count*c)); 
		//for temp1, append c count
		for (int i=0; i<temp1.size(); i++)		
                    temp1[i] [c] = count;                
              	
		appendvect(retVect, temp1);
	}

	for (count=1; count<(S/c); count++)
	{
		vector<map<int, int> > temp2 = Comb2(b, c, S-(count*a)); 
		//for temp2, append a count	
		for (int i=0; i<temp2.size(); i++)	
                     temp2[i][a] = count;                
               	
                appendvect(retVect, temp2);
	}

	
	for (count=1; count<(S/c); count++)
	{
		vector<map<int, int> > temp3 = Comb2(c, a, S-(count*b)); 
                //for temp3, append b count
		for (int i=0; i<temp3.size(); i++)	
                  temp3[i][b] = count;                
             
		appendvect(retVect, temp3);
	}

	//now remove duplicates from the resultant vector.
	std::sort(retVect.begin(), retVect.end());
        retVect.erase(std::unique(retVect.begin(), retVect.end()), retVect.end());

	return retVect;
}

vector<map<int, int> > Comb4(int a, int b, int c, int d, int S)
{
	vector<map<int, int> > retVect;	
        int count=0;

	for (count=1; count<(S/d); count++)
	{
		vector<map<int, int> > temp1 = Comb3(a, b, c, S-(count*d)); 
		//for temp1, append d count
		for (int i=0; i<temp1.size(); i++)		
                    temp1[i] [d] = count;                
              	
		appendvect(retVect, temp1);
	}

	for (count=1; count<(S/a); count++)
	{
		vector<map<int, int> > temp2 = Comb3(b, c, d, S-(count*a)); 
		//for temp2, append a count
		for (int i=0; i<temp2.size(); i++)		
                    temp2[i] [a] = count;                
              	
		appendvect(retVect, temp2);
	}

	
	for (count=1; count<(S/b); count++)
	{
		vector<map<int, int> > temp3 = Comb3(c, d, a, S-(count*b)); 
		//for temp3, append b count
		for (int i=0; i<temp3.size(); i++)		
                    temp3[i] [b] = count;                
              	
		appendvect(retVect, temp3);
	}

        for (count=1; count<(S/c); count++)
	{
		vector<map<int, int> > temp4 = Comb3(d, a, b, S-(count*c)); 
		//for temp4, append c count
		for (int i=0; i<temp4.size(); i++)		
                    temp4[i] [c] = count;                
              	
		appendvect(retVect, temp4);
	}



	//now remove duplicates from the resultant vector.
	std::sort(retVect.begin(), retVect.end());
        retVect.erase(std::unique(retVect.begin(), retVect.end()), retVect.end());

	return retVect;
}


int main()
{
	clock_t start,finish;
	double time;       
	
	start = clock();
        
        vector <map<int, int> > v1 = Comb4(1, 5, 25, 50, 100);	

	vector <map<int, int> > v2 = Comb3(1, 5, 25, 100);
        vector <map<int, int> > v3 = Comb3(5, 25, 50, 100);
        vector <map<int, int> > v4 = Comb3(25, 50, 1, 100);
        vector <map<int, int> > v5 = Comb3(50, 1, 5, 100);
	
	vector <map<int, int> > v6 = Comb2(1, 5, 100);
	vector <map<int, int> > v7 = Comb2(1, 25, 100);
	vector <map<int, int> > v8 = Comb2(1, 50, 100);	

        vector <map<int, int> > v9 = Comb2(5, 25, 100);
	vector <map<int, int> > v10 = Comb2(5, 50, 100);	
        vector <map<int, int> > v11 = Comb2(25, 50, 100);	

	vector <map<int, int> > v12 = Comb1(1, 100);
	vector <map<int, int> > v13 = Comb1(5, 100);
	vector <map<int, int> > v14 = Comb1(25, 100);     
        vector <map<int, int> > v15 = Comb1(50, 100);     
	
	vector <map<int, int> > v;
	
	appendvect(v, v1);
	appendvect(v, v2);
	appendvect(v, v3);
	appendvect(v, v4);
	appendvect(v, v5);
	appendvect(v, v6);
	appendvect(v, v7);   
        appendvect(v, v8);
	appendvect(v, v9);
	appendvect(v, v10);
	appendvect(v, v11);
	appendvect(v, v12);
	appendvect(v, v13);
	appendvect(v, v14);        
        appendvect(v, v15);        
	
        finish = clock();

	time = (double(finish)-double(start));

	cout<<"Through Combination algorithm, the result is: \r\n"<<endl;
	cout<<"Total Time taken: "<<time<<" ms. Press any key to view the result...\r\n"<<endl;
	getch();

	printvect (v);


#ifdef DO_LOG	
        logtext("By Combination Algorithm, the result is:\r\n", "logresult.txt");
        logvect(v, "logresult.txt");
#endif	

	//Applying Brute Force Approach to verify the result and compare the time.
        cout<<"Press B or b to try BFS...\r\n"<<endl;

        int c = getch();

	if ('b' != c && 'B' != c)
            return 0;

	cout<<"By Brute Force technique, the result is: \r\n"<<endl;
	
	vector <map<int, int> > vBruteForce;
	start = finish = 0;
	start = clock();
	vBruteForce = BruteForceTest(1, 5, 25, 50, 100);	
	finish = clock();
	time = (double(finish)-double(start));

	cout<<"Total Time taken for BFS: "<<time<<" ms. Press any key to view the result...\r\n"<<endl;
	getch();

	printvect(vBruteForce);

	cout<<"\r\nTotal No of combinations through BFS:"<<vBruteForce.size()<<"\r\n"<<endl;
	cout<<"Press any key to end..."<<endl;

#ifdef DO_LOG	
	logtext("By Brute Force technique, the result is:\r\n", "BFSLogresult.txt");
	logvect(vBruteForce, "BFSLogresult.txt");    	
#endif

	getch();	
	return 0;
}

