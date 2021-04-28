#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H
#include <iostream>
#include <list>

#include "orderedPair.h"
using namespace std;

#define BOARDSIZE 9
#define SUBBOARDSIZE 3

class SudokuBoard {
  int numMoves=0;
  int nextMoveX;
  int nextMoveY;
  int nextMoveValue;
  list<OrderedPair> nextMoveList;
  list<OrderedPair>::iterator moveIt;
  
public:
  struct Box{
    //each box needs to have 1-9 in it
  public:
    int ** subBoard;
    Box (){
      subBoard = new int * [SUBBOARDSIZE];
      for(int i=0;i<SUBBOARDSIZE;i++){
	subBoard[i] = new int [SUBBOARDSIZE];
      }
    }
    void setBox(int x,int y, int z[][9]){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for (int j=0;j<SUBBOARDSIZE;j++){
	  subBoard[i][j]=z[x+i][y+j];
	}
      }
    }

    int getBlank(int x, int y){
      return subBoard[x][y];
    }

    void setBlank(int x, int y, int value){
      subBoard[x][y]=value;
    }

    void printRow(int x){
      for(int j=0;j<SUBBOARDSIZE;j++){
	cout<<subBoard[x][j]<<" ";
      }
    }

    void printBox(){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  cout<<subBoard[i][j]<<" ";
	}
	cout<<endl;
      }
    }

    bool fullBox(){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  if(subBoard[i][j]==0)
	    return false;
	}
      }
      return true;
    }

    bool validBox(){
      int numbers[]={0,0,0,0,0,0,0,0,0,0};
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  if(subBoard[i][j]==1)numbers[1]++;
	  if(subBoard[i][j]==2)numbers[2]++;
	  if(subBoard[i][j]==3)numbers[3]++;
	  if(subBoard[i][j]==4)numbers[4]++;
	  if(subBoard[i][j]==5)numbers[5]++;
	  if(subBoard[i][j]==6)numbers[6]++;
	  if(subBoard[i][j]==7)numbers[7]++;
	  if(subBoard[i][j]==8)numbers[8]++;
	  if(subBoard[i][j]==9)numbers[9]++;
	}
      }
      for(int i=1;i<9;i++){
	if (numbers[i]>=2)return false;
      }
      return true;
    }

    //arrays are sometimes hard
    //so now im using a string of numbers
    //as the list of numbers in the box
    string getNumbersFromBox(){
      int numbers[]={0,0,0,0,0,0,0,0,0,0};
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  if(subBoard[i][j]==0)numbers[0]++;
	  if(subBoard[i][j]==1)numbers[1]++;
	  if(subBoard[i][j]==2)numbers[2]++;
	  if(subBoard[i][j]==3)numbers[3]++;
	  if(subBoard[i][j]==4)numbers[4]++;
	  if(subBoard[i][j]==5)numbers[5]++;
	  if(subBoard[i][j]==6)numbers[6]++;
	  if(subBoard[i][j]==7)numbers[7]++;
	  if(subBoard[i][j]==8)numbers[8]++;
	  if(subBoard[i][j]==9)numbers[9]++;
	}
      }
      string temp="0000000000";
      for(int i=0;i<10;i++){
	if(numbers[i]>=1)temp[i]='1';
      }
      return temp;
    }

  };

  Box ** board;
  SudokuBoard(int x[][9]){
    board = new Box * [SUBBOARDSIZE];
    for(int i=0;i<SUBBOARDSIZE;i++){
      board[i] = new Box [SUBBOARDSIZE];
    }
    board[0][0].setBox(0,0,x);
    board[1][0].setBox(3,0,x);
    board[2][0].setBox(6,0,x);
    board[0][1].setBox(0,3,x);
    board[1][1].setBox(3,3,x);
    board[2][1].setBox(6,3,x);
    board[0][2].setBox(0,6,x);
    board[1][2].setBox(3,6,x);
    board[2][2].setBox(6,6,x);
  }

  int ** getCurrentState(){
    int ** temp;
    temp= new int * [BOARDSIZE];
    for(int i=0;i<BOARDSIZE;i++){
      temp[i]= new int [BOARDSIZE];
      for(int j=0;j<BOARDSIZE;j++){
	temp[i][j]=getBlock(i,j);
      }
    }
    return temp;
  }

  void printPuzzle(){
    cout<<"====================================="<<endl;
    for(int i=0;i<BOARDSIZE;i++){
      if(i%SUBBOARDSIZE==0)
	cout<<"----------------------"<<endl;
      for(int j=0;j<BOARDSIZE;j++){
	if(j%SUBBOARDSIZE==0)
	  cout<<"|";
        cout<<getBlock(i,j)<<" ";
	if(j==BOARDSIZE-1)
	  cout<<"|";
      }
      cout<<endl;
    }
    cout<<"----------------------"<<endl;
    
  }

  void setBlock(int y,int x,int value){
    //each puzzle has 9 boxes, each box has 9 blocks
    if((y>=0&&y<=2)&&
       (x>=0&&x<=2)){
      //cout<<"00"<<endl;
      board[0][0].setBlank(y,x,value);
    }

    if((y>=3&&y<=5)&&
       (x>=0&&x<=2)){
      //cout<<"10"<<endl;
      board[1][0].setBlank(y-3,x,value);
    }

    if((y>=6&&y<=8)&&
       (x>=0&&x<=2)){
      //cout<<"20"<<endl;
      board[2][0].setBlank(y-6,x,value);
    }

    if((y>=0&&y<=2)&&
       (x>=3&&x<=5)){
      //cout<<"01"<<endl;
      board[0][1].setBlank(y,x-3,value);
    }

    if((y>=0&&y<=2)&&
       (x>=6&&x<=8)){
      //cout<<"02"<<endl;
      board[0][2].setBlank(y,x-6,value);
    }

    if((y>=3&&y<=5)&&
       (x>=3&&x<=5)){
      //cout<<"11"<<endl;
      board[1][1].setBlank(y-3,x-3,value);
    }

    if((y>=3&&y<=5)&&
       (x>=6&&x<=8)){
      //cout<<"12"<<endl;
      board[1][2].setBlank(y-3,x-6,value);
    }

    if((y>=6&&y<=8)&&
       (x>=3&&x<=5)){
      //cout<<"12"<<endl;
      board[2][1].setBlank(y-6,x-3,value);
    }

    if((y>=6&&y<=8)&&
       (x>=6&&x<=8)){
      //cout<<"12"<<endl;
      board[2][2].setBlank(y-6,x-6,value);
    }
    
  }

  int getBlock(int y,int x)const{
    //each puzzle has 9 boxes, each box has 9 blocks
    if((y>=0&&y<=2)&&
       (x>=0&&x<=2)){
      //cout<<"00"<<endl;
      return board[0][0].getBlank(y,x);
    }

    if((y>=3&&y<=5)&&
       (x>=0&&x<=2)){
      //cout<<"10"<<endl;
      return board[1][0].getBlank(y-3,x);
    }

    if((y>=6&&y<=8)&&
       (x>=0&&x<=2)){
      //cout<<"20"<<endl;
      return board[2][0].getBlank(y-6,x);
    }

    if((y>=0&&y<=2)&&
       (x>=3&&x<=5)){
      //cout<<"01"<<endl;
      return board[0][1].getBlank(y,x-3);
    }

    if((y>=0&&y<=2)&&
       (x>=6&&x<=8)){
      //cout<<"02"<<endl;
      return board[0][2].getBlank(y,x-6);
    }

    if((y>=3&&y<=5)&&
       (x>=3&&x<=5)){
      //cout<<"11"<<endl;
      return board[1][1].getBlank(y-3,x-3);
    }

    if((y>=3&&y<=5)&&
       (x>=6&&x<=8)){
      //cout<<"12"<<endl;
      return board[1][2].getBlank(y-3,x-6);
    }

    if((y>=6&&y<=8)&&
       (x>=3&&x<=5)){
      //cout<<"12"<<endl;
      return board[2][1].getBlank(y-6,x-3);
    }

    if((y>=6&&y<=8)&&
       (x>=6&&x<=8)){
      //cout<<"12"<<endl;
      return board[2][2].getBlank(y-6,x-6);
    }
    
    return 100;
  }

  //y is the row we are checking(0-9)
  bool fullRow(int y){
    int numbers[]={0,0,0,0,0,0,0,0,0,0};
    
    //find what box y is in
    if(y>=0&&y<=2){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the row
	  if(board[0][i].getBlank(y,j)==1)numbers[1]++;
	  if(board[0][i].getBlank(y,j)==2)numbers[2]++;
	  if(board[0][i].getBlank(y,j)==3)numbers[3]++;
	  if(board[0][i].getBlank(y,j)==4)numbers[4]++;
	  if(board[0][i].getBlank(y,j)==5)numbers[5]++;
	  if(board[0][i].getBlank(y,j)==6)numbers[6]++;
	  if(board[0][i].getBlank(y,j)==7)numbers[7]++;
	  if(board[0][i].getBlank(y,j)==8)numbers[8]++;
	  if(board[0][i].getBlank(y,j)==9)numbers[9]++;
	}
      }
    }
    if(y>=3&&y<=5){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the row
	  if(board[1][i].getBlank(y-3,j)==1)numbers[1]++;
	  if(board[1][i].getBlank(y-3,j)==2)numbers[2]++;
	  if(board[1][i].getBlank(y-3,j)==3)numbers[3]++;
	  if(board[1][i].getBlank(y-3,j)==4)numbers[4]++;
	  if(board[1][i].getBlank(y-3,j)==5)numbers[5]++;
	  if(board[1][i].getBlank(y-3,j)==6)numbers[6]++;
	  if(board[1][i].getBlank(y-3,j)==7)numbers[7]++;
	  if(board[1][i].getBlank(y-3,j)==8)numbers[8]++;
	  if(board[1][i].getBlank(y-3,j)==9)numbers[9]++;
	}
      }
    }
    if(y>=6&&y<=8){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the row
	  if(board[2][i].getBlank(y-6,j)==1)numbers[1]++;
	  if(board[2][i].getBlank(y-6,j)==2)numbers[2]++;
	  if(board[2][i].getBlank(y-6,j)==3)numbers[3]++;
	  if(board[2][i].getBlank(y-6,j)==4)numbers[4]++;
	  if(board[2][i].getBlank(y-6,j)==5)numbers[5]++;
	  if(board[2][i].getBlank(y-6,j)==6)numbers[6]++;
	  if(board[2][i].getBlank(y-6,j)==7)numbers[7]++;
	  if(board[2][i].getBlank(y-6,j)==8)numbers[8]++;
	  if(board[2][i].getBlank(y-6,j)==9)numbers[9]++;
	}
      }
    }
    for(int i=1;i<9;i++){
      //if there are more than one of the same number
      //in the row, the row is not valid
      if(numbers[i]>=2)return false;
    }
    return true;
  }

  bool fullColumn(int x){
    int numbers[]={0,0,0,0,0,0,0,0,0,0};
    
    //find what box y is in
    if(x>=0&&x<=2){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the column
	  if(board[i][0].getBlank(j,x)==1)numbers[1]++;
	  if(board[i][0].getBlank(j,x)==2)numbers[2]++;
	  if(board[i][0].getBlank(j,x)==3)numbers[3]++;
	  if(board[i][0].getBlank(j,x)==4)numbers[4]++;
	  if(board[i][0].getBlank(j,x)==5)numbers[5]++;
	  if(board[i][0].getBlank(j,x)==6)numbers[6]++;
	  if(board[i][0].getBlank(j,x)==7)numbers[7]++;
	  if(board[i][0].getBlank(j,x)==8)numbers[8]++;
	  if(board[i][0].getBlank(j,x)==9)numbers[9]++;
	}
      }
    }

    if(x>=3&&x<=5){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the column
	  if(board[i][1].getBlank(j,x-3)==1)numbers[1]++;
	  if(board[i][1].getBlank(j,x-3)==2)numbers[2]++;
	  if(board[i][1].getBlank(j,x-3)==3)numbers[3]++;
	  if(board[i][1].getBlank(j,x-3)==4)numbers[4]++;
	  if(board[i][1].getBlank(j,x-3)==5)numbers[5]++;
	  if(board[i][1].getBlank(j,x-3)==6)numbers[6]++;
	  if(board[i][1].getBlank(j,x-3)==7)numbers[7]++;
	  if(board[i][1].getBlank(j,x-3)==8)numbers[8]++;
	  if(board[i][1].getBlank(j,x-3)==9)numbers[9]++;
	}
      }
    }

    if(x>=6&&x<=8){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the column
	  if(board[i][2].getBlank(j,x-6)==1)numbers[1]++;
	  if(board[i][2].getBlank(j,x-6)==2)numbers[2]++;
	  if(board[i][2].getBlank(j,x-6)==3)numbers[3]++;
	  if(board[i][2].getBlank(j,x-6)==4)numbers[4]++;
	  if(board[i][2].getBlank(j,x-6)==5)numbers[5]++;
	  if(board[i][2].getBlank(j,x-6)==6)numbers[6]++;
	  if(board[i][2].getBlank(j,x-6)==7)numbers[7]++;
	  if(board[i][2].getBlank(j,x-6)==8)numbers[8]++;
	  if(board[i][2].getBlank(j,x-6)==9)numbers[9]++;
	}
      }
    }

    for(int i=1;i<9;i++){
      //if there are more than one of the same number
      //in the column, the row is not valid
      if(numbers[i]>=2)return false;
    }

    return true;
  }

  //check to see if the board is in a winning state
  //all rows and columns and boxes need to have
  //1-9 in them
  bool isWinningState(){
    bool win=false;
    for(int i=0;i<BOARDSIZE;i++){
      for(int j=0;j<BOARDSIZE;j++){
	if (getBlock(i,j)==0)return false;
      }
    }
    for(int i=0;i<BOARDSIZE;i++){
      if(fullColumn(i))
	win=true;
      else
	return false;
      if(fullRow(i))
        win=true;
      else
        return false;
      if(board[0][0].validBox())
	win=true;
      else
        return false;
      if(board[0][1].validBox())
        win=true;
      else
        return false;
      if(board[0][2].validBox())
        win=true;
      else
        return false;
      if(board[1][0].validBox())
        win=true;
      else
        return false;
      if(board[1][1].validBox())
        win=true;
      else
        return false;
      if(board[1][2].validBox())
        win=true;
      else
        return false;
      if(board[2][0].validBox())
        win=true;
      else
        return false;
      if(board[2][1].validBox())
        win=true;
      else
        return false;
      if(board[2][2].validBox())
        win=true;
      else
        return false;
    }
    return win;
  }

  bool operator==(const SudokuBoard &b)const{
    for(int i=0;i<BOARDSIZE;i++){
      for(int j=0;j<BOARDSIZE;j++){
	if(getBlock(i,j)!=b.getBlock(i,j))
	  return false;
      }
    }
     return true;
  }

  //returns an string of length 10
  //the index of chars of value 0
  //are numbers you can curently place in the blank
  string getValidMoves(int x,int y){
    int numbers[]={0,0,0,0,0,0,0,0,0,0};
    string temp;
    
    //find what box y is in
    if(x>=0&&x<=2){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the column
	  if(board[i][0].getBlank(j,x)==1)numbers[0]++;
	  if(board[i][0].getBlank(j,x)==1)numbers[1]++;
	  if(board[i][0].getBlank(j,x)==2)numbers[2]++;
	  if(board[i][0].getBlank(j,x)==3)numbers[3]++;
	  if(board[i][0].getBlank(j,x)==4)numbers[4]++;
	  if(board[i][0].getBlank(j,x)==5)numbers[5]++;
	  if(board[i][0].getBlank(j,x)==6)numbers[6]++;
	  if(board[i][0].getBlank(j,x)==7)numbers[7]++;
	  if(board[i][0].getBlank(j,x)==8)numbers[8]++;
	  if(board[i][0].getBlank(j,x)==9)numbers[9]++;
	}
      }
    }

    if(x>=3&&x<=5){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the column
	  if(board[i][1].getBlank(j,x-3)==1)numbers[0]++;
	  if(board[i][1].getBlank(j,x-3)==1)numbers[1]++;
	  if(board[i][1].getBlank(j,x-3)==2)numbers[2]++;
	  if(board[i][1].getBlank(j,x-3)==3)numbers[3]++;
	  if(board[i][1].getBlank(j,x-3)==4)numbers[4]++;
	  if(board[i][1].getBlank(j,x-3)==5)numbers[5]++;
	  if(board[i][1].getBlank(j,x-3)==6)numbers[6]++;
	  if(board[i][1].getBlank(j,x-3)==7)numbers[7]++;
	  if(board[i][1].getBlank(j,x-3)==8)numbers[8]++;
	  if(board[i][1].getBlank(j,x-3)==9)numbers[9]++;

	}
      }
    }

    if(x>=6&&x<=8){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the column
	  if(board[i][2].getBlank(j,x-6)==1)numbers[0]++;
	  if(board[i][2].getBlank(j,x-6)==2)numbers[2]++;
	  if(board[i][2].getBlank(j,x-6)==3)numbers[3]++;
	  if(board[i][2].getBlank(j,x-6)==4)numbers[4]++;
	  if(board[i][2].getBlank(j,x-6)==5)numbers[5]++;
	  if(board[i][2].getBlank(j,x-6)==6)numbers[6]++;
	  if(board[i][2].getBlank(j,x-6)==7)numbers[7]++;
	  if(board[i][2].getBlank(j,x-6)==8)numbers[8]++;
	  if(board[i][2].getBlank(j,x-6)==9)numbers[9]++;
	}
      }
    }

    //find what box y is in
    if(y>=0&&y<=2){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the row
	  if(board[0][i].getBlank(y,j)==1)numbers[0]++;
	  if(board[0][i].getBlank(y,j)==1)numbers[1]++;
	  if(board[0][i].getBlank(y,j)==2)numbers[2]++;
	  if(board[0][i].getBlank(y,j)==3)numbers[3]++;
	  if(board[0][i].getBlank(y,j)==4)numbers[4]++;
	  if(board[0][i].getBlank(y,j)==5)numbers[5]++;
	  if(board[0][i].getBlank(y,j)==6)numbers[6]++;
	  if(board[0][i].getBlank(y,j)==7)numbers[7]++;
	  if(board[0][i].getBlank(y,j)==8)numbers[8]++;
	  if(board[0][i].getBlank(y,j)==9)numbers[9]++;
	}
      }
    }
    if(y>=3&&y<=5){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the row
	  if(board[1][i].getBlank(y-3,j)==1)numbers[0]++;
	  if(board[1][i].getBlank(y-3,j)==1)numbers[1]++;
	  if(board[1][i].getBlank(y-3,j)==2)numbers[2]++;
	  if(board[1][i].getBlank(y-3,j)==3)numbers[3]++;
	  if(board[1][i].getBlank(y-3,j)==4)numbers[4]++;
	  if(board[1][i].getBlank(y-3,j)==5)numbers[5]++;
	  if(board[1][i].getBlank(y-3,j)==6)numbers[6]++;
	  if(board[1][i].getBlank(y-3,j)==7)numbers[7]++;
	  if(board[1][i].getBlank(y-3,j)==8)numbers[8]++;
	  if(board[1][i].getBlank(y-3,j)==9)numbers[9]++;
	}
      }
    }
    if(y>=6&&y<=8){
      for(int i=0;i<SUBBOARDSIZE;i++){
	for(int j=0;j<SUBBOARDSIZE;j++){
	  //check what numbers are in the row
	  if(board[2][i].getBlank(y-6,j)==1)numbers[0]++;
	  if(board[2][i].getBlank(y-6,j)==1)numbers[1]++;
	  if(board[2][i].getBlank(y-6,j)==2)numbers[2]++;
	  if(board[2][i].getBlank(y-6,j)==3)numbers[3]++;
	  if(board[2][i].getBlank(y-6,j)==4)numbers[4]++;
	  if(board[2][i].getBlank(y-6,j)==5)numbers[5]++;
	  if(board[2][i].getBlank(y-6,j)==6)numbers[6]++;
	  if(board[2][i].getBlank(y-6,j)==7)numbers[7]++;
	  if(board[2][i].getBlank(y-6,j)==8)numbers[8]++;
	  if(board[2][i].getBlank(y-6,j)==9)numbers[9]++;
	}
      }
    }

    //finding what box x,y are in
    //i also use it to talk to chat OkayChamping
    if((y>=0&&y<=2)&&
       (x>=0&&x<=2)){
      //cout<<"00"<<endl;
      temp=board[0][0].getNumbersFromBox();
      //cout<<temp<<endl;
    }

    if((y>=3&&y<=5)&&
       (x>=0&&x<=2)){
      //cout<<"10"<<endl;
      temp=board[1][0].getNumbersFromBox();
      //cout<<temp<<endl;
    }

    if((y>=6&&y<=8)&&
       (x>=0&&x<=2)){
      //cout<<"20"<<endl;
      temp=board[2][0].getNumbersFromBox();
      //cout<<temp<<endl;
    }

    if((y>=0&&y<=2)&&
       (x>=3&&x<=5)){
      //cout<<"01"<<endl;
      temp=board[0][1].getNumbersFromBox();
      //cout<<temp<<endl;
    }

    if((y>=0&&y<=2)&&
       (x>=6&&x<=8)){
      //cout<<"02"<<endl;
      temp=board[0][2].getNumbersFromBox();
      //cout<<temp<<endl;
    }

    if((y>=3&&y<=5)&&
       (x>=3&&x<=5)){
      //cout<<"11"<<endl;
      temp=board[1][1].getNumbersFromBox();
      //cout<<temp<<endl;
    }

    if((y>=3&&y<=5)&&
       (x>=6&&x<=8)){
      //cout<<"12"<<endl;
      temp=board[1][2].getNumbersFromBox();
      //thanks pb you foud a bug :)
      //cout<<temp<<endl;
    }

    if((y>=6&&y<=8)&&
       (x>=3&&x<=5)){
      //i hate past lamp
      temp=board[2][1].getNumbersFromBox();
      //cout<<temp<<endl;

    }

    if((y>=6&&y<=8)&&
       (x>=6&&x<=8)){
      temp=board[2][2].getNumbersFromBox();
      //cout<<temp<<endl;

    }

    //after getting all the numbers in the current box
    //this is adding them to the numbers found in
    //the rows and columns
    for(int i=0;i<10;i++){
      //since I am looking a chars I need to convert
      //the ascii code of that char into an int
      //49 is the ascii code for '1'
      //1 is the ascii code for the number 1
      if(((int)temp[i]-48)>=1)numbers[i]++;
    }

    string returnString="0000000000";
      for(int i=0;i<10;i++){
	if(numbers[i]>=1)returnString[i]='1';
      }
      return returnString;
  }

  bool isValidState(){
    for(int i=0;i<BOARDSIZE;i++){
      if(!fullColumn(i))return false;
      if(!fullRow(i))return false;
    }
    for(int i=0;i<SUBBOARDSIZE;i++){
      for(int j=0;j<SUBBOARDSIZE;j++){
	if(!board[i][j].validBox()){	
	  board[i][j].printBox();
	  return false;
	}
      }
    }
    return true;
  }

  int getNumberOfMoves(){return numMoves ;}
  void setNumberOfMoves(int n){numMoves=n;}

  void addNewMove(int x,int y,int v){
    OrderedPair temp(x,y,v);
    nextMoveList.push_back(temp);
  }

  //if there are more than 1 item in the list
  //we need to make sure we pick the one that leaves
  //the most room for other numbers
  //Ie. pick the number that has the least constraining it
  //it might not be the first one in the list

  void findLeastConstraining(){
    int n=0;
    int least=0;
    int smallestX=0;
    int smallestY=0;
    int smallestValue=0;
    for(moveIt=nextMoveList.begin();moveIt!=nextMoveList.end();moveIt++){
      int x=(*moveIt).getX();
      int y=(*moveIt).getY();
      int value=(*moveIt).getValue();
      int ** copy=getCurrentState();
      int copyB[9][9];
      for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
	  copyB[i][j]=copy[i][j];
	}
      }
      SudokuBoard copyBoard(copyB);
      copyBoard.setBlock(x,y,value);
      list<OrderedPair> blankList;
      list<OrderedPair>::iterator blankIt;
      for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
	  if(getBlock(i,j)==0){
	    OrderedPair tempPair(i,j);
	    blankList.push_front(tempPair);
	  }
	}
      }
      for(blankIt=blankList.begin();blankIt!=blankList.end();blankIt++){
	string moves = getValidMoves((*blankIt).getY(),(*blankIt).getX());
	for(int k=0;k<10;k++){
	  if(moves[k]-48==0){
	    n++;
	  }
	}
      }
      if(n>=least){
	least=n;
	smallestX=x;
	smallestY=y;
	smallestValue=value;  
      }
    }
    nextMoveX=smallestX;
    nextMoveY=smallestY;
    nextMoveValue=smallestValue;
    cout<<least<<"("<<smallestX<<","<<smallestY<<")=>"<<smallestValue<<endl;
  }
  int getNextMoveX(){return nextMoveX;}
  int getNextMoveY(){return nextMoveY;}
  int getNextMoveValue(){return nextMoveValue;}

  //int getNextMoveX(){return nextMoveList.front().getX();}
  //int getNextMoveY(){return nextMoveList.front().getY();}
  //int getNextMoveValue(){return nextMoveList.front().getValue();}

  


  
  
};

#endif 
