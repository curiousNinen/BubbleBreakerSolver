/************************************************************
 *		Bubble Break Program	(header)     Justin Waugh	*
 *															*
 *	Mostly a simple engine that runs the game.				*
 *															*
 ************************************************************/

// Width and Height of the board are defined here. Not the most elegant solution
// But it works.

static const int WIDTH = 10;
static const int HEIGHT = 10;
static const int DIFFPIECE = 2;


// This function calculates and returns the points that would be earned
// if you were to remove point x, y from the board.
int points(int board[HEIGHT][WIDTH],int x, int y);

// This function is used to calculate (recursively), the blocks that would be removed
// given a specific input and goal piece. (It will update the mask array with 1's
// in the location that match goal. Also, it ultimately returns the number of 1's in mask array)
int reCalcMask(int board[HEIGHT][WIDTH], int x, int y, int mask[HEIGHT][WIDTH], int goal);

// This function "plays" a move, and removes the chunk at x,y assuming it is a valid choice
// and then it cleans up the board afterward. It returns the points earned from doing the move.
int removeBlock(int board[HEIGHT][WIDTH], int x, int y);

// This function will clean the board (sliding the pieces down and to the side) after a move.
int cleanBoard(int board[HEIGHT][WIDTH]);

// This function simply prints the board out to the terminal.
void printBoard(int board[HEIGHT][WIDTH]);

// This function will initialize a board. There will be "options" number of pieces. 
// eg:     initBoard(board, 5);   will initialize a board with values 1-5 randomly placed.
// If it is called with "0" or any negative number, it will return board filled with all 0s.
void initBoard(int board[HEIGHT][WIDTH], int options);

// This function tests whether or not there are available moves left to be played.
// Will return true when there are no more moves (eg. Game is over).
bool gameOver(int board[HEIGHT][WIDTH]);

// This function copies the board in "copyMe" into "newBoard". Will be useful when writing
// game engines that solve and you need a "master" original board.
void copyBoard(int newBoard[HEIGHT][WIDTH], int copyMe[HEIGHT][WIDTH]);
