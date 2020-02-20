#include <sstream>
#include <cstdio>
#include <cctype>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <array>
#include <locale>
#include <string>

using namespace std;


string removePunctuation(string su) {
    for (int i = 0, len = su.size(); i < len; i++) {
        if (ispunct(su[i])) {
            su.erase(i--, 1);
            len = su.size();
        }
    }
    return su;
}

string lowerCase(string sl) {
    transform(sl.begin(), sl.end(), sl.begin(), [](unsigned char c){ return tolower(c); });
    return sl;
}

vector<string> split(string s, char delimiter) {
    vector<string> separatedStrings;
    stringstream ss(s);
    string word;
 
    while(getline(ss, word, delimiter)) {
        separatedStrings.push_back(removePunctuation(lowerCase(word)));
    }
 
    return separatedStrings;
}


void test(string file_no1, string file_no2){

fstream keyword_file;
string keyLine;
string keyLineNew;
keyword_file.open(file_no1);
unordered_map<string, int> umap;

   if (keyword_file.is_open()) {
       while (getline(keyword_file, keyLine)) {
           
           stringstream keyLineS(keyLine);
           
           while (getline(keyLineS, keyLineNew, '#')) { //just for handling comments, sets your comment delimiter to #
               
           if (any_of(keyLineNew.begin(), keyLineNew.end(), [](char c){ return ispunct(c); })) {
               cerr << "no punctuation in key words stupid" << endl;
               
           }
           else if (any_of(keyLineNew.begin(), keyLineNew.end(), [](char c){ return isspace(c); })) {
               cerr << "one word per line you trog" << endl;
           }
           else if (keyLineNew.size() > 0) {
               umap[keyLineNew] = 0;
           }
               break;
       }
   }
   }
       else {
           cerr << "filestream can't be made" << endl;
           
       }
   
    keyword_file.close();

   vector<string> parsed;

   int words = 0;
   int keyWords = 0;
   int lines = 0;

   string line;
   fstream file;
   file.open(file_no2);
   if (file.is_open()) {
       while (getline(file, line)) {
           parsed = split(line, ' ');
           
           words = words + parsed.size();
           
           unordered_map<string, int>:: iterator itrtr;
               
           for (int i = 0; i < parsed.size(); i++) {
               for (itrtr = umap.begin(); itrtr != umap.end(); itrtr++) {
                   if (itrtr -> first == parsed[i]) {
                       itrtr -> second ++;
                   }
               }
           }
           lines++;
       }
       file.close();
   } else {
       cerr << "no" << endl;
   }

   unordered_map<string, int>:: iterator itrtr;


   cout << "KEY WORDS" << endl;
   cout << "+-+-+-+-+-+-+" << endl;

   for (itrtr = umap.begin(); itrtr != umap.end(); itrtr++) {
       keyWords = keyWords + itrtr -> second;
       
       cout << left << setw(10) << itrtr -> first
                << right << setw(15) << itrtr -> second <<endl;
   }

   cout << "total found: " << keyWords << endl << endl;

}



int main (int argc, char* argv[]) {
    
    test(argv[1], argv[2]);
    
    return 0;
}
