#include <iostream>

using namespace std;

/* we need:
1. Write code that will use cin.get() to read characters in one by one until a newline is encountered. 
Report how many words there were in the input, how long the longest word was, and the largest number of vowels in a word (work on one of these at a time!). You may not store any of the characters but you can have other variables that store information about them as you go along.
 * 
 */



int main(int argc, char** argv) {
  
    
    int numWords;
    int longest = 0;
    int largestVowels;
    char currentChar;

    cout << "Type a random load of nonsense right here:" << endl << endl;

        currentChar = cin.get();
        while (currentChar != '\n'){ //how we know to stop

        int currentCharCount;
        int currentVowelCount;

          while(currentChar != ' ' && currentChar != '\n'){ //how we know we've got to the end of the word

            if(isalpha(currentChar)){ //we're only interested in counting words, not numbers, punctuation etc
              currentCharCount++;
            }
            if(currentChar == 'a' || currentChar == 'e' || currentChar == 'i' || currentChar == 'o' || currentChar == 'u'){
              currentVowelCount++;
            }
              currentChar = cin.get();
          }
          if(currentCharCount != 0){ //only increment numWords if we read a word (not a space, number, punctuation etc)
            numWords++;
          }
          if(currentCharCount > longest){longest = currentCharCount;}
          currentCharCount = 0; //reset char count for next word
          if(currentVowelCount > largestVowels){largestVowels = currentVowelCount;}
          currentVowelCount = 0; //reset vowel count for next word


          if(currentChar != '\n'){
            currentChar = cin.get(); //the current character is either a space or a newline. Don't get next char if it's a newline otherwise we'll inifinite loop
          }
 
    }

    
      cout << endl << "**************************************************************" << endl << endl;

      if(numWords == 0){
        cout << "You didn't enter anything at all! Please try again!" << endl;
      }
      else{
        cout << "The longest word you entered was: " << longest << endl;
        cout << "You entered this many words: " << numWords << endl;
        cout << "The largest number of vowels in a word was: " << largestVowels << endl;
      }
    
      cout << endl << "**************************************************************" << endl << endl;

  return 0;
}

