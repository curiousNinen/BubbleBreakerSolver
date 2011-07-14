#include <iostream>

using namespace std;

#define	WIDTH	10
#define	HEIGHT	10

int points(int board[HEIGHT][WIDTH],int x, int y);
int reCalcMask(int board[HEIGHT][WIDTH], int x, int y, int mask[HEIGHT][WIDTH], int goal);
int removeBlock(int board[HEIGHT][WIDTH], int x, int y);
int cleanBoard(int board[HEIGHT][WIDTH]);
void printBoard(int board[HEIGHT][WIDTH]);
void initBoard(int board[HEIGHT][WIDTH], int options);
bool gameOver(int board[HEIGHT][WIDTH]);
void copyBoard(int newBoard[HEIGHT][WIDTH], int copyMe[HEIGHT][WIDTH]);

int main(int argc, char *argv[])
{
	srand(0); // seed goes here.
	
	int bubbleBoard[HEIGHT][WIDTH];

	initBoard(bubbleBoard,5);
	
	
	int score=0;
	
	while(!gameOver(bubbleBoard))
	{
		printBoard(bubbleBoard);
		int x,y;
		cout<<"x:";
		cin>>x;
		cout<<"y:";
		cin>>y;
		score+=removeBlock(bubbleBoard,x,y);
		cout<<"Score:"<<score;
	}
}

void initBoard(int board[HEIGHT][WIDTH], int options)
{
	for(int i=0; i<HEIGHT; i++)
		for(int j=0; j<WIDTH; j++)
			board[i][j] = (options>=1)?rand()%options+1:0;
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
	
	if(goalShape ==0)
		return 0;
	
	int mask[HEIGHT][WIDTH]; // Maybe update mask with binary operations?
	int value =0, pointAmount = 0;
	
	initBoard(mask,0);
	
	value = reCalcMask(board, x, y, mask, goalShape);
	
	pointAmount = value * (value - 1);
	
	if(pointAmount ==0)
		return 0;
	
	for(int i=0; (i<HEIGHT); i++)
		for(int j=0; j<WIDTH; j++)
			if(mask[i][j]==1)
				board[i][j]=0;
	
	cleanBoard(board);
	
	return pointAmount;
	
}

bool gameOver(int board[HEIGHT][WIDTH])
{
	for(int j=WIDTH-1; j>0; j--)
		for(int i=HEIGHT-1; i>0; i--)
			if((board[i-1][j] == board[i][j] || board[i][j-1] == board[i][j] )&&board[i][j]!=0)
				return false;
			   
	return true;
}

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
		
		value+=reCalcMask(board, x-1, y, mask, goal);
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
						lookAt = -2;
					}
				if(lookAt==-1)
					i=-1;
			}

	for(int j=WIDTH-1; j>=0; j--)
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
