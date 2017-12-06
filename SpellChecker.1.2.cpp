//Copyright 2014 © All rights reserved. Written and developed by Daniel Peters and Allen Vaisman

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <locale>
#include <sstream>

#define ALPHA 26

using namespace std;

class Tree;
class TreeNodes;

typedef TreeNodes* Node;

class Tree{
public:
	void buildTree(void);
	string getInput(void);
	void check(string input);
	bool isWord(string input);
	void switchletters(string input);
    void addletters(string input);
    void dropletters(string input);
    void swapletters(string input);
private:
	Node Root;
};

class TreeNodes{
public:
	TreeNodes();
	Node nextNodes[ALPHA];
	char letter;
	bool mark;
private:

};

TreeNodes::TreeNodes(){
	for (int i = 0; i < ALPHA; i++)
		nextNodes[i] = NULL;
	return;
}

void Tree::check(string input){
if(isWord(input))
{
cout << input << " is a word!" << endl << endl;
}
else
{
cout << input << " is not a word!" << endl << endl;
switchletters(input);
dropletters(input);
addletters(input);
swapletters(input);
}
return;
}

void Tree::switchletters(string input)
{
string testWord;
for (int j=0; j<input.size(); j++){
testWord=input;
for (int i = 0; i < ALPHA; i++){
 testWord[j] = 'a'+i;
 if (isWord(testWord))
 cout << testWord << endl;
 }
}
}



string charToString(char in){
stringstream ss;
string out;
ss << in;
ss >> out;
return out;
}

void Tree::addletters(string input)
{
string testWord,before,after;

for(int j=0;j<=input.size();j++){
for(int k=0; k<ALPHA; k++){
before="";
after="";
for(int i=0; i<j;i++){
before+=charToString(input[i]);
}
for(int i=j; i<input.size();i++){
after+=charToString(input[i]);
}
testWord=before+charToString('a'+k)+after;
//cout << testWord << endl;
if(isWord(testWord))
    cout << testWord << endl;
}
}

}



void Tree::dropletters(string input){
string testWord,before,after;

for(int j=0;j<=input.size();j++){
before="";
after="";
for(int i=0; i<j-1;i++){
before+=charToString(input[i]);
}
for(int i=j; i<input.size();i++){
after+=charToString(input[i]);
}
testWord=before+after;
//cout << testWord << endl;
if(isWord(testWord))
    cout << testWord << endl;
}

}


void Tree::swapletters(string input){
char tempChar;
string testWord;
for(int i = 0; i+1<input.size();i++){
testWord=input;
tempChar=input[i+1];
testWord[i+1]=input[i];
testWord[i]=tempChar;
if(isWord(testWord))
cout<<testWord<<endl;
}
return;
}



bool Tree::isWord(string inputWord)
{
Node Current=Root->nextNodes[inputWord[0]-'a'];
for(int i=1; i<=inputWord.size(); i++){
    if(Current==NULL){
        return false;
    }
    if(i!=inputWord.size())
    Current=Current->nextNodes[inputWord[i]-'a'];
}

if(Current->mark){
return true;
}
else{
return false;
}
}


string Tree::getInput(void){
cout << "What is the word you would like to check?" << endl;
string input;
cin >> input;
for(int i=0;i<input.size();i++)
input[i]=tolower(input[i]);
return  input;
}


void Tree::buildTree(void){
	ifstream database;
	database.open("words.txt");

	Node Ptr = new TreeNodes;  //Creates a new node for the root. <--ROOT
	Root = Ptr;                  //Assigns the pointer value to the Tree's root.

	Node Current = Root;

	string tempString;

	while (!database.eof()){ //Whole File
		Current = Root;
		database >> tempString;
		for (int i = 0; i < tempString.size(); i++){ //Each word
			if (Current->nextNodes[tempString[i] - 'a'] == NULL){  //If that letter hasn't been created yet
				Node tempPtr = new TreeNodes;			//Each Letter
				tempPtr->letter = tempString[i];
				Current->nextNodes[tempString[i] - 'a']=tempPtr;
				Current = tempPtr;
			}
			else{
				Current = Current->nextNodes[tempString[i] - 'a'];
			}
		}
		Current->mark=true;
	}
	database.close();
	return;
}


int main(){

	Tree wordTree;
	wordTree.buildTree();

	ifstream file;
	string tempString;
	file.open("file.txt");
	while(!file.eof()){
    file >> tempString;
    //cout << tempString;
    wordTree.check(tempString);
	}
    file.close();

	while(true){
	wordTree.check(wordTree.getInput());
	}
	return 0;

}

//Multiple types of checks
//frequency analysis
//weighting of possibilites
//letter localization

