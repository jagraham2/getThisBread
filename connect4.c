#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "scanner.c"
#include "scanner.h"
int N;//-------------------------------------------------rows
int M;//------------------------------------------------columns
typedef struct player player;
struct player{
  int symbol;
  int row;
  int col;
};

void displayBoard(player** board){

  printf("\n");
  printf("\n");

        for(int x = -1; x<N; x++){//-------------------printing table
            for(int y = 0; y<M; y++){
                if (x==-1) {
                  if(y<9){
                  printf("| %d ", y);
                  }
                  if(y>=9){
                    if(y>=99){
                      printf("|%d", y);
                    }
                    else
                    printf("| %d", y);

                  }


                }
                 else
                  printf("| %d ", board[x][y].symbol);
                  //printf("| %d ", y);
            }
            puts("|");
            printf("_");
            if(N==M){
              for (int i = 0; i<N+N; i++){
                    printf("__");
               }
           }
           else if (N>M||N<M){
             for (int i = 0; i<M+M; i++){
                   printf("__");
              }
           }
             printf("\n");
        }//-----------------------------------------printing table
}

int findWinner(player** board, int symbol, int *rowsOpen){//<---------make dynamic
  int counter = 0;
  int rightUpCont = 0;
  int rightDwnCont = 0;
  int dwnCount = 0;
 //Loop through entire table
  for (int x = 0; x<N; x++){
    for (int y=0; y<M; y++){
      //If current player symbol is the same as the one in the table..
      if (board[x][y].symbol == symbol){
        //Check 4-in-a-row (DIRECTION RIGHT)
          for (counter = 0; counter < 4; counter++){//-----------------------------------------right
            //  printf("Right count : %d\n", counter);
               if ( y+counter<M ){
                   if (board[x][y+counter].symbol==symbol) {
                     continue;
                   }
                   else{
                     break;
                   }
               }
               else{
                 break;
               }

        }
        if (counter == 4){//------------------------------------------------------------if 4 right
          printf("---------------Player %d won! (because of right)----------------\n", symbol);
        	return 1;
          //--------------------------------------------------------------------finish the game
        }
        else{
          counter = 0;//------------------------------------------------------------------if not
        }
        //Check 4-in-a-row (DIRECTION RIGHT-UP)
        for (rightUpCont = 0; rightUpCont < 4; rightUpCont++){//---------------------------------------right up
           if ( x-rightUpCont>=0 && y+rightUpCont<N){
             //printf("did i get here..?");
               if (board[x-rightUpCont][y+rightUpCont].symbol==symbol) {
                // printf("This is 1\n");
                 continue;
               }
               else{
                // printf("This is  2\n");
                 break;
               }
           }
           else{
             break;
           }

        }
        if (rightUpCont == 4){//------------------------------------------------if 4 right up
          printf("----------------Player %d won! (because RIGHTUP)----------------\n", symbol);
           return 1;
          //-----------------------------------------------------------finish the game
        }
        else{
          rightUpCont = 0;//-----------------------------------------------------if not
        }
         for (rightDwnCont = 0; rightDwnCont < 4; rightDwnCont++){//---------------------------------------right down
           //printf("Right down count : %d\n", rightDwnCont);
            if ( x+rightDwnCont<M && y+rightDwnCont<N){
                if (board[x+rightDwnCont][y+rightDwnCont].symbol==symbol) {
                  continue;

                }
                else{
                  break;
                }
            }
            else{
              break;
            }


        }
        if (rightDwnCont == 4){//--------------------------------------------------------if 4 right down
          printf("---------------Player %d won! (because of rightDOWN)----------------\n", symbol);
           return 1;
          //-----------------------------------------------------finish the game
        }
        else{

          rightDwnCont = 0;//---------------------------------------------------------------if not
        }

        for (dwnCount = 0; dwnCount < 4; dwnCount++){//------------------------------------------down
        //  printf("down count : %d\n", dwnCount);
          if (x+dwnCount < M){
            if (board[x+dwnCount][y].symbol==symbol) {
              continue;

            }
            else{
              break;
            }
          }
          else{
            break;
          }

        }
        if (dwnCount == 4){//---------------------------------------------------------if 4 down
          printf("----------------Player %d won! (because of DOWN)----------------\n", symbol);
           return 1;
          //-------------------------------------------------------finish the game
        }
        else{
          dwnCount = 0;//-------------------------------------------------------------if not
        }
      }
    }
  }
  int tieChecker = 1;
  for (int i = 0; i<M; i++){
    if(rowsOpen[i] < 0 ){
      continue;
    }
    else{
      //printf("We found a %d at index %d in rowOpen..\n", rowsOpen[i], i);
      tieChecker = 0;
      break;
    }
  }//tie
  if (tieChecker == 1){
    printf("------------------------ITS A TIE--------------------------\n");
    return 2;//------------------------------------------------------------there is a tie
  }
  //  else{
  //
  // //   //----------------------------------------------------------not a tie, and no 4-in-a-row yet
  // }

  return 0;
}

void insert(player** board, player player){
//printf("HEYYYYYYYYYYYYYYYYYYYYYYYYYY 111111\n");
//printf("Row is %d \n", player.row);
//printf("Col is %d \n", player.col);
  board[player.row][player.col]=player;
}

int main(void)
{
    char input[1] = "0";
    //int test;
    int gameChoice = 0;
    int playerTurn = 0;
    int winner = 0;
    int P1Wins = 0;
    int P2Wins = 0;
    int rounds = 1;

    printf("******HELLO WELCOME TO CONNECT 4******\n");
    printf("Press 1 for single player or 2 for two player!(incorrect input will cause the program to exit)\n");
    gameChoice = readInt(stdin);
  if (gameChoice < 1 || gameChoice>2){//--------------------------------error message protocol game mode this is good make sure user knows what is going on
      printf("ERROR: Invalid input\n");
      return 0;//-------------------------------------------------------------error message protocol game mode this is good make sure user knows whats going on
    }

  if(gameChoice==2 || gameChoice ==1){//--------------------------------------------------------------------------------------------------two player
    printf("Choose number of rows and colums(rows and columns cannot be below 4) incorret input will exit the game\n");
    N = readInt(stdin);//---------------------------------------------------error message protocol invalid rows and col
    M = readInt(stdin);

    while(N<4||M<4){
      printf("ERROR: Invalid input\n");
      return 0;
    }

     printf("THIS IS N %d\n", N);
     printf("THIS IS M %d\n", M);
    start://keep this here so it re ints the board
    if (rounds>1){
      printf("****************ROUND %d ****************\n", rounds);
      printf("Player 1 score:  %d\n", P1Wins);
      printf("Player 2 score:  %d\n", P2Wins);
    }
    player **board = malloc(N *  sizeof(player));
      for(int i = 0; i< N; i++){
        board[i] = malloc(M * sizeof(player));
      }

    //player board[N][M];//-------------------------------------------------------board init

    for(int x = 0; x<N; x++){
        for(int y = 0; y<M; y++){
          board[x][y].symbol = '\0' ;
        }
      }


        while(winner != 1){
        int playerSymbol = 0;
        int x = 0;
        int row;

        //int rowsOpen[M];//----------------malloc
        int *rowsOpen = malloc(M *  sizeof(int));

        for (int i = 0; i<M; i++){
           rowsOpen[i]= N-1 ;

        }

          top:
            if(x == 0){//----------------------------------if no one has gone
             //playerSymbol = 0;

              displayBoard(board);
              x=1;
             goto top;
            }
           else if(x == 1){//---------------------------------if it is player 1's turn
                playerTurn = 1;
                playerSymbol = 1;
              //  char input[1] = "0";//
                int input;
                int location;
                 printf("player 1's turn\n");
                 player1:
                 printf("Choose Column number where you want to insert (0-%d) entering a letter in anyway will cause program to end\n", M-1);
                // scanf("%s", input);
                 input = readInt(stdin);
                 while((input>= M ) || input<0 || rowsOpen[(input)]<0){
                   printf("ERROR: Input out of range\n");
                   printf("Choose Column number where you want to insert (0-%d) entering a letter in anyway will cause program to end\n", M-1);
                   input = readInt(stdin);
                 }
                 location = (input);
                // printf("location %d\n ", location);//-------------------------------------part of insertion protocol
                 row = rowsOpen[location];
                 player new_player;
                 new_player.col = location;
                 new_player.row = row;//----------------------maybe
                 new_player.symbol = playerSymbol;

                 // int win = insert(board, new_player,rowsOpen);
                 // //printf("HEYYYYYYYYYYYYYYYYYYYYYYYYYY 111111\n");
             		 // rowsOpen[location]--;//-------------------------------------part of insertion protocol
                 insert(board, new_player);
                 rowsOpen[location]--;
                 int win = findWinner(board, new_player.symbol, rowsOpen);
                 //printf("WINN IS %d\n", win);
                 displayBoard(board);
                 //here is where you would displayBoard
                  if (win == 1){//-----------------------------------------------------end of round
                    rounds++;
                    P1Wins++;
                        if(P1Wins==2){//------------------------winner of 2 out 3 rounds
                          goto end;
                        }
                    goto start;
                  }
                  if(win == 2){//------------------------------------------
                    rounds++;
                    goto start;
                  }
                  x=2;
                  goto top;
            }
           else if(x == 2){

             if (gameChoice == 2){//----------------------------------------------if it is player two turn
                playerTurn = 2;
                playerSymbol = 2;
              //  char input[1] = "0";
                int input;
                int location;
                 printf("player 2's turn\n");
                 player2:
                 printf("Choose Column number where you want to insert (0-%d) entering a letter in anyway will cause program to end\n", M-1);
                 input = readInt(stdin);
                 while( ((input) >= M ) || (input)<0 || rowsOpen[(input)]<0){//-------------------------------------error protocol
                   printf("ERROR: input out of range\n");
                   printf("Choose Column number where you want to insert (0-%d) entering a letter in anyway will cause program to end\n", M-1);
                   input = readInt(stdin);
                 }
                 location = (input);//-----------------------------------------------------------error protol

                 row = rowsOpen[location];//-------------------------------------part of insertion protocol
                 player new_player;
                 new_player.col = location;
                 new_player.row = row;
                 new_player.symbol = playerSymbol;

                 insert(board, new_player);
                 rowsOpen[location]--;
                 int win = findWinner(board, new_player.symbol, rowsOpen);
                 //printf("WINN IS %d\n", win);
                 displayBoard(board);//-------------------------------------part of insertion protocol
             			if (win == 1){//-------------------------------------------------------------------------------------end of round
                    rounds++;
                    P2Wins++;
                    if(P2Wins==2){
                      goto end;
                    }
                    goto start;
                  }
                  if(win == 2){//------------------------------------------
                    rounds++;
                    goto start;
                  }
                 x=1;
                 goto top;
               }
               //------------------------------------------------------------------------do not go above this line for AI
               printf("AI Time\n");
               //playerSymbol = 1;

               player player1;
               player1.symbol = 1;
               player player2;
               player2.symbol = 2;
               player reg;//-----------------------reg
               reg.symbol = '\0' ;//------------reg
               //search for win loop
               int win = 0;
               for (int i = 0; i<M; i++){
                 reg.col =i;
                 reg.row =rowsOpen[i];
                 if(reg.row<0){
                   continue;
                 }
                  player2.col = i;
                  player2.row = rowsOpen[i];
                  insert(board, player2);
                  rowsOpen[i]--;
                  win = findWinner(board, player2.symbol, rowsOpen);
                  if(win==1){
                    printf("Found winner - already inserted\n");
                    displayBoard(board);
                    rounds++;
                    x=1;
                    break;
                  }
                  else if (win == 0){
                    printf("Found no winners\n");
                    insert(board, reg);
                    printf("Player 2 tried to insert at [%d][%d]\n", reg.col, reg.row);
                    rowsOpen[i]++;
                    continue; // 'continue' means it's going to next column
                  }
               }
               if(win!=0){
                 if (win == 1){///not working right
                   //next person's turn
                  //-----------------------------------------------------end of round
                     rounds++;
                     P2Wins++;
                         if(P2Wins==2){//------------------------winner of 2 out 3 rounds
                           goto end;
                         }
                     goto start;
                   }

                   if(win == 2){//------------------------------------------
                     rounds++;
                     goto start;
                   }
                   x=1;
                   goto top;
                 } //----------------------------need to



               else{
                 int randomInsert;
                 randomInsert = rand() % M;
                 while(rowsOpen[randomInsert]<0){
                   randomInsert = rand() % M;
                 }
                 player2.col = randomInsert;
                 player2.row = rowsOpen[randomInsert];
                 insert(board, player2);
                 rowsOpen[randomInsert]--;
                 displayBoard(board);
                 //rounds++;
                 x=1;
                 goto player1;
                 //pick a random spot (later on, we'll work on blocking instead)
               }
                //add if winn stuff/------------------------------------------AI stuff goes here
               return 0;
            }
            //here
        }
        end:
        printf("Player 1 score:  %d\n", P1Wins);
        printf("Player 2 score:  %d\n", P2Wins);
        if(P1Wins>P2Wins){
          printf("Player 1 Wins the GAME!\n");
        }
        else printf("Player 2 Wins the GAME!\n");
        printf("Thank you for Playing....Goodbye!");//-------------------------------end of game
        return 0;
    }

}
