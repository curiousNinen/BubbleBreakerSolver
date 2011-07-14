/************************************************************
 *		Bubble Break Program			- Justin Waugh		*
 *															*
 *	Mostly a simple engine that runs the game.				*
 *															*
 *	To do: Add solving engines and test/compare them		*
 *															*
 ************************************************************/

#include <iostream>
#include "BubbleBreak.h"

using namespace std;

int main(int argc, char *argv[])
{
	srand(0); // seed goes here. For now, set to 0. 
	
	int bubbleBoard[HEIGHT][WIDTH]; // The board.
	initBoard(bubbleBoard,DIFFPIECE); // Initailize the board. 
	
	int score=0; // Start with 0 score... obviously
	
	while(!gameOver(bubbleBoard)) // this code is just to "play" the game. should be obvious on reading.
	{
		printBoard(bubbleBoard);
		int x,y;
		cout<<"x:";
		cin>>x;
		cout<<"y:";
		cin>>y;
		score+=removeBlock(bubbleBoard,x,y);
		cout<<"Score:"<<score<<endl;
	}
}

void initBoard(int board[HEIGHT][WIDTH], int options) 
{
	for(int i=0; i<HEIGHT; i++)
		for(int j=0; j<WIDTH; j++)
			board[i][j] = (options>=1)?rand()%options+1:0; /// intialzie to random%option or 0 depending on option.
}

void copyBoard(int newBoard[HEIGHT][WIDTH], int copyMe[HEIGHT][WIDTH])
{
	for(int i=0; i<HEIGHT; i++)
		for(int j=0; j<WIDTH; j++)
			newBoard[i][j] = copyMe[i][j];
}

void printBoard(int board[HEIGHT][WIDTH])
{
	for(int i=0; (i<HEIGHT)&&(cout<<"\n"); i++)
		for(int j=0; j<WIDTH; j++)
			cout<<board[i][j]<<"\t";
	cout<<endl;
}

int removeBlock(int board[HEIGHT][WIDTH], int x, int y)
{
	if(x<0 || y<0 || x>=WIDTH || y >= HEIGHT) // check for valid x, y.
		return 0;
	
	int goalShape = board[y][x];
	
	if(goalShape ==0) // 0's are empty pieces, return imediately.
		return 0;
	
	int mask[HEIGHT][WIDTH]; // Maybe update mask with binary operations?
	int value =0, pointAmount = 0;
	
	initBoard(mask,0); // set up a mask of 0s.
	
	value = reCalcMask(board, x, y, mask, goalShape); // caculate neighbors.
	
	pointAmount = value * (value - 1); // formula to calculate score from "value" number of touching pieces.
	
	if(pointAmount ==0)
		return 0;
	
	for(int i=0; (i<HEIGHT); i++)
		for(int j=0; j<WIDTH; j++)
			if(mask[i][j]==1)
				board[i][j]=0;    // remove pieces.
	
	cleanBoard(board); // update the board by cleaning it.
	
	return pointAmount;
	
}

// simple check to see if there are any neighboring pieces that are the same.
// could probably speed up the process assuming the board is cleaned, so if you run into 0s, just skip that row
//     (Added!)

bool gameOver(int board[HEIGHT][WIDTH]) 
{
	for(int j=WIDTH-1; j>0; j--)
		for(int i=HEIGHT-1; i>0; i--)
		{
			if(i==(HEIGHT-1)&&board[i][j]==0) // all 0s left.
				j=0;
			else if(board[i][j]==0)  // all 0's above it.
				i=0;
			else if(board[i-1][j] == board[i][j] || board[i][j-1] == board[i][j])
				return false;
		}
			   
	return true;
}

// calculate points (mostly used as a header to call reCalcMask without calling it with wrong values)
int points(int board[HEIGHT][WIDTH], int x, int y) 
{
	if(x<0 || y<0 || x>=WIDTH || y >= HEIGHT)
		return 0;
	
	int goalShape = board[y][x];
	
	if(goalShape ==0)
		return 0;
	
	int mask[HEIGHT][WIDTH];
	
	int value =0;
	
	initBoard(mask,0);
	value=reCalcMask(board, x, y, mask, goalShape);
	
	return value*(value-1);
}

int reCalcMask(int board[HEIGHT][WIDTH], int x, int y, int mask[HEIGHT][WIDTH], int goal)
{
	int value = 0;
	
	if(x<0 || y<0 || x>=WIDTH || y >= HEIGHT)
		return 0;
	if(mask[y][x] == 1)
		return 0;
	
	if(board[y][x] == goal)
	{
		mask[y][x] = 1;
		value++;
		
		value+=reCalcMask(board, x-1, y, mask, goal); // check the 4 directions. 
		value+=reCalcMask(board, x+1, y, mask, goal);
		value+=reCalcMask(board, x, y+1, mask, goal);
		value+=reCalcMask(board, x, y-1, mask, goal);
	}

	return value;
}

int cleanBoard(int board[HEIGHT][WIDTH])
{
	for(int j=0; j<WIDTH; j++)
		for(int i=HEIGHT-1; i>=0; i--)
			if(board[i][j] == 0)
			{
				int lookAt;
				for(lookAt = i-1; lookAt>=0; lookAt--)
					if(board[lookAt][j] != 0)
					{
						board[i][j] = board[lookAt][j];
						board[lookAt][j] = 0; 
						lookAt = -2;			// This line helps break out of loop, dunno if break; goes too deep?
					}
				if(lookAt==-1)
					i=-1; // also equivilant to a break;, but im scared about it going too far. / not far enough sometimes.
			}

	for(int j=WIDTH-1; j>=0; j--)  // essentailly the same loop as above.
		if(board[HEIGHT-1][j]==0)
		{
			int lookAt;
			for(lookAt = j-1; lookAt >=0; lookAt--)
				if(board[HEIGHT-1][lookAt] !=0)
				{
					for(int i=0; i<HEIGHT; i++)
					{
						board[i][j] = board[i][lookAt];
						board[i][lookAt] = 0;
					}
					lookAt = -2;
				}
			if(lookAt==-1)
				j=-1;
		}
}
