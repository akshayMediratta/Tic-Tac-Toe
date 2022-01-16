#include "given.h"

int main()
{
    int userRow, userCol, computerRow, computerCol;
    int taken;
    int count = 1;
    int stepsWon = 0;

    char board[N][N];
    char winner = 'N';

    srand((int)time(0));

    printf("This tic-tac-toe board is of size %d by %d\n", N, N);

    printf("You are using symbol X and the computer program is using symbol O\n");

    printf("Here is the board - spaces are indicated by a ?\n");

    createInitialBoard(board);

    while ((winner != 'Y') && !(isBoardFull(board)))
    {
        taken = 0;
        while (!(taken))
        {
            readUserMove(&userRow, &userCol, &stepsWon);
            printf("You chose row %d and column %d \n", userRow, userCol);

            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))
            {
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol, &stepsWon);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }

            if (board[userRow - 1][userCol - 1] == '?')
            {
                board[userRow - 1][userCol - 1] = 'X';
                taken = 1;
                count++;
            }
            else
            {
                taken = 0;
                printf("That spot is taken - please try another one\n");
            }
        }

        if (gameWon(board, 'X'))   //user won
        {
            printf("Congrats - you won against the computer :) in %d steps\n", stepsWon);
            winner = 'Y';
        }

        else  if (!(isBoardFull(board)))            //check computer's move if the board is not yet full
        {
            taken = 0;

            while (!(taken))
            {
                taken = getComputerMove(board, &computerRow, &computerCol, userRow - 1, userCol - 1);

                if (taken) {

                    break;
                }

                if (board[computerRow][computerCol] == '?')
                {
                    board[computerRow][computerCol] = 'O';
                    taken = 1;

                }
                else
                {
                    taken = 0;
                    //printf("That spot is taken - computer - try another one\n");
                }
            }
            printf("Computer chose row %d and column %d \n", computerRow + 1, computerCol + 1);
            if (gameWon(board, 'O'))
            {
                printf("Oh the computer won this time :(( think hard next time\n");
                winner = 'Y';
            }
        }

        printCurrentBoard(board);

        if (winner != 'Y') {

        }



    } //end of while

    if (winner != 'Y') {
        printf("Game was a tie - no winner!\n\n");
    }

    return 0;
}


int  getComputerMove(char board[N][N], int* computerRow, int* computerCol, int userRow, int userCol) {

    int winningSpot = 0;

    winningSpot = computerPlaysToWin(board, computerRow, computerCol);


     //if the computer does not find a winning spot, then it either play randomly or blocks


    if (!winningSpot)
    {
        // comment the next line if you are attempting the 2% functionality
        //computerPlaysRandom(computerRow, computerCol);

        // uncomment the next few  lines if you are attempting the 2% functionality
        int blocked = 0;

        blocked = computerPlaysToBlock(board, computerRow, computerCol);
        if (blocked == 0) {
           computerPlaysRandom(computerRow, computerCol);
        }
        return blocked;
    }

    return winningSpot;
}

void createInitialBoard(char board[N][N])
{
    int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            board[i][j] = '?';
        }
    }
    printCurrentBoard(board);
}

void printCurrentBoard(char board[N][N])
{
    printf("Current board now is:\n\n");
    printf("    1   2   3\n\n");
        for (int i = 0; i < 3; i++)
        {
          printf("%d  ", i+1);
          for (int j = 0; j < 2; j++)
          {
            printf(" %c |",board[i][j]);
          }
          if(i<2)
          {
            printf(" %c\n   -----------\n", board[i][2]);
          }
          else
          {
            printf(" %c\n",board[2][2]);
          }
        }
    printf("\n");
}

int isBoardFull(char board[N][N])
{
    int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (board[i][j]=='?')
            {
                return 0;
            }
        }
    }
    return 1;
}

int isInputValid(int entered, int minimum, int maximum)
{
    if(entered>=minimum && entered<=maximum)
    {
       return 1;
    }
    else
    {
       return 0;
    }
}

void readUserMove(int* userRow, int* userCol, int* stepsWon)
{
    printf("Your move - enter numbers between 1 and 3\n");
    printf("\nEnter row number: ");
    scanf("%d",userRow);
    printf("Enter column number: ");
    scanf("%d",userCol);
    int ans1=isInputValid(*userRow, 1,3);
    int ans2=isInputValid(*userCol, 1,3);
    if(ans1 && ans2 )
    {
      *stepsWon += 1;
     }
}

void all_sums(char board[N][N], int sumR[N], int sumC[N], int *sumLD, int *sumRD)
{
    *sumLD = 0;
    *sumRD = 0;
    for (int i = 0; i<N; i++)
    {
       sumR[i] = 0;
       sumC[i] = 0;
    }

    for(int i = 0;i<3;i++)
    {
       for(int j = 0; j<3; j++)
       {
          if(i==j)
          {
             if(board[i][j]=='X')
             {
                *sumLD += 1;
             }
             if(board[i][j]=='O')
             {
                *sumLD += 4;
             }
          }
          if(i+j==2)
          {
             if(board[i][j]=='X')
             {
                *sumRD += 1;
             }
             if(board[i][j]=='O')
             {
                *sumRD += 4;
             }
          }
          if(board[i][j]=='X')
          {
             sumR[i] += 1;
          }
          if(board[i][j]=='O')
          {
             sumR[i] += 4;
          }
          if(board[i][j]=='X')
          {
             sumC[j] += 1;
          }
          if(board[i][j]=='O')
          {
             sumC[j] += 4;
          }
      }
   }
}

int gameWon(char board [N][N], char symbol)
{
    int sumR[3];
    int sumC[3], sumLD, sumRD;
    all_sums(board,sumR,sumC,&sumLD,&sumRD);
    if(sumLD==12 || sumLD==3)
    {
       return 1;
    }
    if(sumRD==12 || sumRD==3)
    {
       return 1;
    }
    for (int i =0; i<N; i++)
    {
       if(sumR[i]==12 || sumR[i]==3)
       {
          return 1;
       }
       if (sumC[i]==12 || sumC[i]==3)
       {
          return 1;
       }
    }
    return 0;
}

int computerPlaysToWin(char board[N][N], int* computerRow, int* computerCol)
{
    int sumR[N];
    int sumC[N];
    int sumLD = 0, sumRD = 0;
    all_sums(board, sumR, sumC, &sumLD, &sumRD);

    for (int i = 0; i < N; i++)
    {
        if (sumR[i] == 8)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i ;
                    *computerCol = j ;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (sumC[j] == 8)
        {
            for (int i = 0; i < N; i++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i ;
                    *computerCol = j ;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    if (sumLD == 8)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][i] == '?')
            {
                *computerRow = i ;
                *computerCol = i ;
                board[i][i] = 'O';
                return 1;
            }
        }
    }

    if (sumRD == 8)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][N-1-i] == '?')
            {
                *computerRow = i ;
                *computerCol = N-i-1;
                board[i][N-i-1] = 'O';
                return 1;
            }
        }
    }
    return 0;
}

int computerPlaysToBlock(char board[N][N], int* computerRow, int* computerCol)
{
    int sumR[N];
    int sumC[N];
    int sumLD = 0, sumRD = 0;
    all_sums(board, sumR, sumC, &sumLD, &sumRD);

    for (int i = 0; i < N; i++)
    {
        if (sumR[i] == 2)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i;
                    *computerCol = j;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (sumC[j] == 2)
        {
            for (int i = 0; i < N; i++)
            {
                if (board[i][j] == '?')
                {
                    *computerRow = i;
                    *computerCol = j;
                    board[i][j] = 'O';
                    return 1;
                }
            }
        }
    }

    if (sumLD == 2)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][i] == '?')
            {
                *computerRow = i;
                *computerCol = i;
                board[i][i] = 'O';
                return 1;
            }
        }
    }

    if (sumRD == 2)
    {
        for (int i = 0; i < N; i++)
        {
            if (board[i][N - 1 - i] == '?')
            {
                *computerRow = i;
                *computerCol = N - i - 1;
                board[i][N-i-1] = 'O';
                return 1;
            }
        }
    }
    return 0;
}

void computerPlaysRandom(int* computerRow, int* computerCol)
{
    *computerRow = (rand()) % 3;
    *computerCol = (rand()) % 3;
}

int memberOf(int value, int someArray[N])
{
    for (int i = 0; i < N; i++)
    {
        if (someArray[i] == value)
        {
           return 1;
        }
    }
    return 0;
}
