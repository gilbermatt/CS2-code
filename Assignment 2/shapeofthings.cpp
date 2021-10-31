#include <iostream>

using namespace std;



int main(int argc, char** argv) {
  
  for (int row = 1; row <= 5; row++){
      for (int hashnum = 1; hashnum <= row; hashnum++){
        cout << ' ';
      } 
      for (int hashnum = 1; hashnum <= row; hashnum++){
          cout << '#';  
      }
      if(row == 5){
          cout << "#";
      }
      if(row != 5){
        for (int hashnum = 1; hashnum <= 17-((row-1)*4); hashnum++){
          cout << ' ';
        } 
      }
      for (int hashnum = row; hashnum < row*2; hashnum++){
        cout << '#';    
      }
      cout << endl;
  }
    for (int row = 5; row >= 0; row--){
      for (int hashnum = 1; hashnum <= row; hashnum++){
        cout << ' ';
      } 
      for (int hashnum = 1; hashnum <= row; hashnum++){
        cout << '#';    
      }
      if(row == 5){
          cout << "#";
      }
      if(row != 5){
        for (int hashnum = 1; hashnum <= 17-((row-1)*4); hashnum++){
          cout << ' ';
        } 
      }
      for (int hashnum = row; hashnum < row*2; hashnum++){
        cout << '#';    
      }

      cout << endl;
  }
  return 0;
}

