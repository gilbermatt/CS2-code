#include <iostream>

using namespace std;


string decideIfInteresting(string word);

/* This function acts as a black box as it obscures what it is doing to decide whether a word is interesting. 
 * The main function doesn't need to know this - it just needs to know there is a function with this name, what input it requires and what it returns.
 */
string decideIfInteresting(string word){
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
    word = decideIfInteresting(word);
    cout << word << endl;
  return 0;
}

