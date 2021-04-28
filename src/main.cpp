#include <iostream>
#include <fstream>
#include <list>
#include "../include/sudokuBoard.h"
#include "../include/sudokuSolver.h"
#include "../include/orderedPair.h"
using namespace std;

#define BOARDSIZE 9
#define SUBBOARDSIZE 3

int main(){
  string temp;
  fstream fin;

  //fin.open("inputFile",ios::in); //does not have a solution 
  //fin.open("test",ios::in); //easy puzzle found goal
  fin.open("medium",ios::in); //found a goal
  //fin.open("hard",ios::in);
  //fin.open("evil",ios::in);
  

  int board[BOARDSIZE][BOARDSIZE];
  
  //import data from inputFile
  for(int i=0;i<BOARDSIZE;i++){
    fin>>temp;
    for(int j=0;j<BOARDSIZE;j++){
      //cout<<temp[j]<<" ";
      board[i][j]=temp[j]-48;
    }
    //cout<<endl;
  }

  SudokuBoard myBoard(board);
    
  

  myBoard.printPuzzle();
 

  SudokuSolver g(&myBoard);

  g.LCV();
  //g.NBA();

  


}
