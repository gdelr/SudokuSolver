#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <stack>
#include <stdlib.h>
#include <time.h>
#include <list>

#include <iostream>

#include "sudokuBoard.h"
#include "orderedPair.h"

using namespace std;
//comparator to sort nodes by the number of moves they have
bool compare_Puzzle (SudokuBoard& first, SudokuBoard& second){
    return(first.getNumberOfMoves() < second.getNumberOfMoves());
  }

class SudokuSolver {
public:
  stack<SudokuBoard*> S;
  list<SudokuBoard*> foundStates;
  list<SudokuBoard*>::iterator it;

  //s is the starting node
  SudokuSolver(SudokuBoard *s){
    S.push(s);
    foundStates.push_front(s);
  }
  //builds a tree of posible states
  //all posible moves will branch
  //from its parent

  //if a leaf is not valid
  //it will not have new leafs
  //and searching will start again
  //from the next valid leaf in the
  //stack

  //using minimum remaining values and least constraining values

  //somehow I need to order posible nodes by the number of 0s they have
  int LCV(){
    //expand tree
    while(S.size()!=0){
      //if top is a goal state quit
      if((*S.top()).isWinningState()){
	cout<<"Goal state found"<<endl;
	(*S.top()).printPuzzle();
	return 0;
      }
      else{
	int ** copyTempA=(*S.top()).getCurrentState();
	int copyTempB[9][9];
	for(int i=0;i<9;i++){
	  for(int j=0;j<9;j++){
	    copyTempB[i][j]=copyTempA[i][j];
	  }
	}
	//set current state to be the top of the stack
	SudokuBoard currentState(copyTempB);
	cout<<"curent node:"<<endl;
	currentState.printPuzzle();

	//make a list of where the 0s are
	list<OrderedPair> blankList;
	list<OrderedPair>::iterator blankIt;

	list<SudokuBoard> posibleMoves;
	list<SudokuBoard>::iterator movesIt;
	for(int i=0;i<9;i++){
	  for(int j=0;j<9;j++){
	    if(currentState.getBlock(i,j)==0){
	      OrderedPair tempPair(i,j);
	      blankList.push_front(tempPair);
	    }
	  }
	}
	
	//find where posible nodes might be
	cout<<"The current board has "<<blankList.size()<<" zeros"<<endl;
	for(blankIt=blankList.begin();blankIt!=blankList.end();blankIt++){
	  int x=(*blankIt).getX();
	  int y=(*blankIt).getY();
	  string moves = currentState.getValidMoves(y,x);
	  //if there are more than one valid moves
	  //make a new node for each valid move
	  for(int k=0;k<10;k++){
	    if(moves[k]-48==0){
	      int ** copyTempA=currentState.getCurrentState();
	      int copyTempB[9][9];
	      for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
		  copyTempB[i][j]=copyTempA[i][j];
		}
	      }
	      //copyBoard is a posible node
	      SudokuBoard copyBoard(copyTempB);
	      //found a  new node
	      copyBoard.setBlock(x,y,k);
	      //make a list of where the 0s are for the newly found node
	      list<OrderedPair> zerosList;
	      list<OrderedPair>::iterator zerosListIt;
	      int tempNumberOfMoves=0;
	      for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
		  if(copyBoard.getBlock(i,j)==0){
		    OrderedPair tempPair(i,j);
		    zerosList.push_front(tempPair);
		  }
		}
	      }
	      //pointers just point to an object 4Head
	      for(zerosListIt=zerosList.begin();zerosListIt!=zerosList.end();zerosListIt++){
		//doing the same thing as in line 79 to get the number of moves this node has
		string newNodeMoves=copyBoard.getValidMoves(y,x);
		for(int l=0;l<10;l++){
		  if(newNodeMoves[l]-48==0)
		    tempNumberOfMoves++;
		}
	      }	   
	      copyBoard.setNumberOfMoves(tempNumberOfMoves);

	      //forward checking
	      copyBoard.addNewMove(x,y,k);

	      //all the newly found nodes have a value with them
	      //with that value we can sort them
	      //the one with the fewest posible moves need to be explored first
	      posibleMoves.push_back(copyBoard);
	      //cout<<"The new Node has "<<copyBoard.getNumberOfMoves()<<endl;
	    }
	  }
	}
	cout<<"the number of posible moves is "<<posibleMoves.size()<<endl;
	if(posibleMoves.size()==0){
	  S.pop();
	  continue;
	}
	
	//compare_Puzzle is a comparator to sort nodes by number of edges 
	posibleMoves.sort(compare_Puzzle);
	cout<<"The next node to check has "<<posibleMoves.front().getNumberOfMoves()<<endl;
	int ** copyTempC=posibleMoves.front().getCurrentState();
	int copyTempD[9][9];
	for(int i=0;i<9;i++){
	  for(int j=0;j<9;j++){
	    copyTempD[i][j]=copyTempC[i][j];
	  }
	}
	//This node is next to be expored 
	SudokuBoard copyBoard(copyTempD);
	for(movesIt=posibleMoves.begin();movesIt!=posibleMoves.end();movesIt++){
	  posibleMoves.front().findLeastConstraining();
	  OrderedPair tempOrderedPair(posibleMoves.front().getNextMoveX(),posibleMoves.front().getNextMoveY(),posibleMoves.front().getNextMoveValue());
	  copyBoard.setBlock(tempOrderedPair.getX(),tempOrderedPair.getY(),tempOrderedPair.getValue());
	  cout<<"Next node:"<<endl;
	  cout<<"("<<tempOrderedPair.getX()<<","<<tempOrderedPair.getY()<<") => "<<tempOrderedPair.getValue()<<endl;
	  copyBoard.printPuzzle();
	
	  if(copyBoard.isValidState()){
	    if(copyBoard.isWinningState()){
	      cout<<"goal state found"<<endl;
	      copyBoard.printPuzzle();
	      return 0;
	    }
	  //copyBoard.printPuzzle();
	  //look if the new node has already been found
	    bool alreadyFound=false;
	    cout<<"List  Size: "<<foundStates.size()<<endl;
	    for(it=foundStates.begin();it!=foundStates.end();it++){
	      if(*(*it)==copyBoard){
		//cout<<"found state"<<endl;
		//(**it).printPuzzle();
		//copyBoard.printPuzzle();
		alreadyFound=true;
	      }
	    }
	    //if new node is not in the found list
	    //add it to the list
	    if(!alreadyFound)
	      S.push(&copyBoard);
	  }
	}

	//current node is fully discovered
	//add it to the list of discovered nodes
	foundStates.push_back(&copyBoard);
	S.pop();
	cout<<"Stack Size: "<<S.size()<<endl;
      }
    }
    return 0;
  }

  //this "works" it just takes too long to find a solution
  //
  int NBA(){
    //expand tree
    while(S.size()!=0){
      //if top is a goal state quit
      if((*S.top()).isWinningState()){
	cout<<"Goal state found"<<endl;
	(*S.top()).printPuzzle();
	return 0;
      }
      else{
	int ** copyTempA=(*S.top()).getCurrentState();
	int copyTempB[9][9];
	for(int i=0;i<9;i++){
	  for(int j=0;j<9;j++){
	    copyTempB[i][j]=copyTempA[i][j];
	  }
	}
	//set current state to be the top of the stack
	SudokuBoard currentState(copyTempB);
	cout<<"curent node:"<<endl;
	currentState.printPuzzle();

	//make a list of where the 0s are
	list<OrderedPair> blankList;
	list<OrderedPair>::iterator blankIt;
	for(int i=0;i<9;i++){
	  for(int j=0;j<9;j++){
	    if(currentState.getBlock(i,j)==0){
	      OrderedPair tempPair(i,j);
	      blankList.push_front(tempPair);
	    }
	  }
	}
	
	//checking what numbers will fit in the blank space
	cout<<"Number of zeros on board:"<<blankList.size()<<endl;
	for(blankIt=blankList.begin();blankIt!=blankList.end();blankIt++){
	  int x=(*blankIt).getX();
	  int y=(*blankIt).getY();
	  string moves = currentState.getValidMoves(y,x);
	  //if there are more than one valid moves
	  //make a new node for each valid move
	  for(int k=0;k<10;k++){
	    if(moves[k]-48==0){
	      int ** copyTempA=currentState.getCurrentState();
	      int copyTempB[9][9];
	      for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
		  copyTempB[i][j]=copyTempA[i][j];
		}
	      }
	      SudokuBoard copyBoard(copyTempB);
	      //find new node
	      copyBoard.setBlock(x,y,k);
	      cout<<"("<<x<<","<<y<<") => "<<k<<endl;
	      //if new nodee is a goal state quit
	      if(copyBoard.isValidState()){
		if(copyBoard.isWinningState()){
		  cout<<"goal state found"<<endl;
		  copyBoard.printPuzzle();
		  return 0;
		}
		//copyBoard.printPuzzle();
		//look if the new node has already been found
		bool alreadyFound=false;
		for(it=foundStates.begin();it!=foundStates.end();it++){
		  if(*(*it)==copyBoard){
		    cout<<"found state"<<endl;
		    //(**it).printPuzzle();
		    //copyBoard.printPuzzle();
		    alreadyFound=true;
		  }
		}
		//if new node is not in the found list
		//add it to the list
		if(!alreadyFound){
		  cout<<"Adding to list"<<endl;
		  cout<<"("<<x<<","<<y<<") => "<<k<<endl;
		  //copyBoard.printPuzzle();
		  S.push(&copyBoard);
		}
	      }
	    }
	  }
	}
	//current node is fully discovered
	//add it to the list of discovered nodes
	foundStates.push_back(&currentState);
	S.pop();
	cout<<"Stack Size: "<<S.size()<<endl;
	cout<<"List  Size: "<<foundStates.size()<<endl;
      }
    }
    return 0;
  }
  
  
};

#endif 
