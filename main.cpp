#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Removing espaces from a string
vector<string> RemoveDupWord(string s){
    vector<string> words;
    string word ;
    int k = 0;
    while ( k < s.size())
    {
    
        while (k < s.size() && s[k] == ' ' )
        {
            k++;
        }
        while (k < s.size() && s[k] != ' ')
        {
            word.push_back(s[k]);    
            k++;
        }
        if(word.empty()==false){
            words.push_back(word);
        }
        word.clear();
        

    }
    return words ; 
}

// read a txt path file and return vector of string 
// every line of the text is a string element in this vector
vector<string> readFromFile(string filePath){

    vector<string> fileLines;
    string line ; 

    ifstream myFile(filePath);
    if (myFile.is_open()){
        while (getline(myFile,line)){
            fileLines.push_back(line);
        }
    }else{
           cout<< "File name is wrong ! \n ";
    }

    return fileLines;
}

// take a string as an argument and return a LowerCase of it 
string LowerCase(string s){
    for (int i=0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}

// take a vector has lines as an argument and return a vector every element in the new vector is a word !
vector<string> linesToWords(vector<string> lines){
    vector <string> words;
    for( auto line = lines.begin() ; line != lines.end(); line ++ ){
            for ( auto word :RemoveDupWord(*line) ) {
                words.push_back(LowerCase(word));
            }
        }

    return words;

}

// take a vector of strings and return a new pair vector has the word and the number of repetition in this text
vector<pair<string, int>> iteractionCount(vector <string> wordsfile){
    bool addToList = false;
    vector<pair<string, int>> dataFile;

    for(auto word: wordsfile){
        if(dataFile.empty()==true){
            dataFile.emplace_back(word,1);
        }else{
            for(int i = 0 ; i<=dataFile.size();i++ ){

                if(word == dataFile[i].first){
                    dataFile[i].second++;
                    addToList = true;
                    break;
                }

            }
            if (addToList==false){
                dataFile.emplace_back(word,1);
            }
            addToList=false;
        }
    }
    return dataFile;
}

// Main function
int main () {

    // read the path of two files from the user :
    string pathFile1 , pathFile2;
    cout << "============================ " << endl;
    cout << "============================ " << endl;
    cout << "|||| Comparing Two File |||| " << endl ; 
    cout << "============================ " << endl;
    cout << "============================ " << endl;
    cout << "\n \n ";
    
    cout << "Put the path of the first txt file :  " << endl ; 
    cin >> pathFile1;  
    cout << "\n " << endl ;
    cout << "Put the path of the secende txt file :  " << endl ; 
    cin >> pathFile2;  
    cout << "\n " << endl ;


    // text file => vector of words 
        //first file 
    vector<string> fileLines1 = readFromFile(pathFile1);
    vector<string> wordsfile1 = linesToWords(fileLines1);
        //secend file 
    vector<string> fileLines2 = readFromFile(pathFile2);
    vector<string> wordsfile2 = linesToWords(fileLines2);



    // count the iteration of every string in the vector of words that we got from the text file    
        //first file 
    vector<pair<string, int>> dataFile1 = iteractionCount(wordsfile1);
        //secend file 
    vector<pair<string, int>> dataFile2 = iteractionCount(wordsfile2);


    // Calc the Similarity ( Cosin Similarity )
    // please check it in the link : https://en.wikipedia.org/wiki/Cosine_similarity
    double up = 0.0 ; 
    double downA, downB;
    for(auto data1 : dataFile1){
        for(auto data2 : dataFile2){
            if (data1.first == data2.first){
                
                up += data1.second * data2.second;

            }
        }
    }
    for(auto data1:dataFile1){
         downA += data1.second * data1.second;
    }
    for(auto data2:dataFile2){
         downB += data2.second * data2.second;
    }

    // output the result : 
    cout << " the silimarity between this two files is :  " << round((up / (sqrt(downA) * sqrt(downB)))*100)<< "%" << endl ;


    return 0 ; 
}