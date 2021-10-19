#include <iostream>

using namespace std;

/*
 * 
 */
string doSomethingInteresting(string word);

string doSomethingInteresting(string word){
    if(word.length() > 10){
        return "Your thoughts are very intriguing. I beg thee please tell more.";
    }
    else{
        return "Not interesting sorry. Please try again.";
    }
}

int main(int argc, char** argv) {
    string word;
    cout << "Type a random word - first one that you think of:";
    cin >> word;
    word = doSomethingInteresting(word);
    cout << word << endl;
  return 0;
}

