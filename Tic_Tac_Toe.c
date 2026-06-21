#include<stdio.h>
#include<stdlib.h>

#define EMPTY 2
#define X 3
#define O 5

int board[3][3];

int gameMenu()
{
    int choice;
    //system("cls"); // Windows (use "clear" for Linux/Mac)
    printf("\n1. Two Player Game");
    printf("\n2. Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d",&choice);
    return choice;
}

void resetGame()
{
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            board[i][j]=EMPTY;
}

void displayBoard()
{
    int i,j,k=1;
    printf("\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j]==EMPTY)
                printf("%3d",k);
            else if(board[i][j]==X)
                printf("%3c",'X');
            else
                printf("%3c",'O');
            k++;
        }
        printf("\n\n");
    }
}

int isMoveValid(int move)
{
    if(move < 1 || move > 9)
        return 0;

    int row = (move-1)/3;
    int col = (move-1)%3;

    return (board[row][col] == EMPTY);
}

int inputMove(int player)
{
    int move;
    while(1)
    {
        printf("Player %d (Enter position 1-9): ",player);
        scanf("%d",&move);

        if(isMoveValid(move))
            return move;
        else
            printf("Invalid move! Try again.\n");
    }
}

void makeMove(int player,int move)
{
    int row = (move-1)/3;
    int col = (move-1)%3;

    board[row][col] = (player==1) ? X : O;
}

int checkWin(int player)
{
    int i;
    int val = (player==1) ? 27 : 125;

    // Rows & Columns
    for(i=0;i<3;i++)
    {
        if(board[i][0]*board[i][1]*board[i][2] == val)
            return 1;
        if(board[0][i]*board[1][i]*board[2][i] == val)
            return 1;
    }

    // Diagonals
    if(board[0][0]*board[1][1]*board[2][2] == val)
        return 1;
    if(board[0][2]*board[1][1]*board[2][0] == val)
        return 1;

    return 0;
}

int main()
{
    int turn,player,move;

    while(1)
    {
        switch(gameMenu())
        {
            case 1:
                resetGame();
                player = 1;

                for(turn=1; turn<=9; turn++)
                {
                    displayBoard();
                    move = inputMove(player);
                    makeMove(player,move);

                    //system("cls"); // change to "clear" for Linux

                    if(checkWin(player))
                    {
                        displayBoard();
                        printf("\nPlayer %d wins!\n",player);
                        break;
                    }

                    player = (player==1) ? 2 : 1;
                }

                if(turn > 9)
                {
                    displayBoard();
                    printf("\nGame is a draw!\n");
                }
                break;

            case 2:
                exit(0);

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
