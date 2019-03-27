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

int findWinner(player** board, int symbol, int *rowsOpen){
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
          //printf("---------------Player %d won! (because of right)----------------\n", symbol);
        	return 1;
          //--------------------------------------------------------------------finish the game
        }
        else{
          counter = 0;//------------------------------------------------------------------if not
        }
        //Check 4-in-a-row (DIRECTION RIGHT-UP)
        for (rightUpCont = 0; rightUpCont < 4; rightUpCont++){//---------------------------------------right up
           // printf("Finding rightUp..\n");
          // printf("")
           if ( x-rightUpCont>=0 && y+rightUpCont<M){
              // printf("player is %d\n",symbol);
              //  printf("x is %d\n", x);
              //  printf("y is %d\n",y);


                 if (board[x-rightUpCont][y+rightUpCont].symbol==symbol) {////watch this i changed y+ to y-
                   //printf("rightUpCont = %d\n",rightUpCont);
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
          //printf("----------------Player %d won! (because RIGHTUP)----------------\n", symbol);
          return 1;
          //-----------------------------------------------------------finish the game
        }
        else{
          //printf("right up counter is %d\n",rightUpCont);
          rightUpCont = 0;//-----------------------------------------------------if not
        }
         for (rightDwnCont = 0; rightDwnCont < 4; rightDwnCont++){//---------------------------------------right down
           // printf("Right down count : %d\n", rightDwnCont);
           // printf("x is  : %d\n", x);
           // printf("CHECK: x:%d + %d is less than %d\n", x, rightDwnCont, M);
           // printf("y is :  %d\n", y);

            if ( ((x+rightDwnCont) < N) && ((y+rightDwnCont)<M) ){
              //printf("made it here!\n");
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
          //printf("---------------Player %d won! (because of rightDOWN)----------------\n", symbol);
           return 1;
          //-----------------------------------------------------finish the game
        }
        else{

          rightDwnCont = 0;//---------------------------------------------------------------if not
        }

        for (dwnCount = 0; dwnCount < 4; dwnCount++){//------------------------------------------down
          //printf("down count : %d\n", dwnCount);
            if (x+dwnCount < N){
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
          //printf("----------------Player %d won! (because of DOWN)----------------\n", symbol);
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
      //printf("just checkin here too..\n");
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
  board[player.row][player.col]=player;
}

int main(void)
{
    char input[1] = "0";
    int gameChoice = 0;
    int playerTurn = 0;
    int winner = 0;
    int P1Wins = 0;
    int P2Wins = 0;
    int rounds = 1;
    printf("**The first player to win a series of 2 games wins overall!\n");
    printf("**At any time if a letter is entered the game will end\n");
    printf("**If user enters a column choice to insert that doesnt exist or is filled they will be asked to pick again\n");
    printf("**Player 1's symbol is 1 and Player 2 (and AI) symbol is 2\n\n\n");
    printf("******HELLO WELCOME TO CONNECT 4******\n");
    printf("Press 1 for single player or 2 for two player!\n");

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
    start://----------------------------------------------------------this is were rounds start
    if (rounds>1){
      printf("****************ROUND %d ****************\n", rounds);
      printf("Player 1 score:  %d\n", P1Wins);
      printf("Player 2 score:  %d\n", P2Wins);
    }
    player **board = malloc(N *  sizeof(player));//--------initialize and allocate space for board
      for(int i = 0; i< N; i++){
        board[i] = malloc(M * sizeof(player));
      }


    for(int x = 0; x<N; x++){
        for(int y = 0; y<M; y++){
          board[x][y].symbol = '\0' ;//---------set everything in board initially to zero
        }
      }


        while(winner != 1){//------------------------------this loop runs game loop
        int playerSymbol = 0;
        int x = 0;//---------------------variable to determine the end of each turn
        int row;
        int *rowsOpen = malloc(M *  sizeof(int));
        for (int i = 0; i<M; i++){
           rowsOpen[i]= N-1 ;

        }

          top:
            if(x == 0){//----------------------------------if no one has gone
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

                 player1:
                 printf("**player 1's turn*\n\n");
                 printf("Choose Column number where you want to insert (0-%d) entering a letter in anyway will cause program to end\n", M-1);
                // scanf("%s", input);
                 input = readInt(stdin);

                 while((input>= M ) || input<0 || rowsOpen[(input)]<0){

                   printf("ERROR: Input out of range\n");
                   printf("Choose Column number where you want to insert (0-%d) entering a letter in anyway will cause program to end\n", M-1);
                   input = readInt(stdin);
                 }

                 location = input;

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
                 printf("Board after Player 1's insert\n\n");
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
           else if(x == 2){//------------------------------------------------------------------------if single player ai turn

             if (gameChoice == 2){//----------------------------------------------if it multi player 2 two turn
                playerTurn = 2;
                playerSymbol = 2;
              //  char input[1] = "0";
                int input;
                int location;
                 printf("**player 2's turn\n\n");
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
                 printf("Board after Player 2's insert\n\n");
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

               //printf("AI's Turn\n\n");
               player player1;
               player1.symbol = 1;
               player player2;
               player2.symbol = 2;
               player reg;//-----------------------reg
               reg.symbol = '\0' ;//------------reg
               int aiInsertLimit = 0;//--------------------------------------------------limits ai to insert only once per round
               int win = 0;
               int block = 0;
               for (int i = 0; i<M; i++){//----this loop basically finds if there is a place for the ai to win
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
                    //printf("Ai's board after insert \n\n");

                    x=1;
                    break;
                  }
                  else if (win == 0){
                    insert(board, reg);
                    rowsOpen[i]++;
                    continue; // ------------------------'continue' means it's going to next column
                  }
               }//-------------------------------------------------------for loop ends
               if(win!=0){///-----------------------------------determine if the ai wins
                 if (win == 1){

                     rounds++;
                     P2Wins++;
                         if(P2Wins==2){//------------------------winner of 2 out 3 rounds
                           goto end;
                         }
                     goto start;
                   }

                   if(win == 2){
                     rounds++;
                     goto start;
                   }
                   x=1;
                   goto top;
                 } //----------------------------end of determine winner

               else{
                 for (int i = 0; i<M; i++){//-----------------determines if there is a sequence for the ai to block
                   reg.col =i;
                   reg.row =rowsOpen[i];
                   if(reg.row<0){
                     continue;
                   }
                    player1.col = i;
                    player1.row = rowsOpen[i];
                    player2.col = i;
                    player2.row = rowsOpen[i];
                    insert(board, player1);
                    rowsOpen[i]--;
                    block = findWinner(board, player1.symbol, rowsOpen);
                    if(block==1){
                      printf("Found block - already inserted\n\n");
                      insert(board, player2);
                        aiInsertLimit++;//ai limiter
                      //  printf("rows open at %d after a block %d\n",i, rowsOpen[i]);
                      displayBoard(board);
                      //printf("Ai's board after insert\n\n");
                      x=1;
                      break;
                    }
                    else if (block == 0){
                      insert(board, reg);
                      rowsOpen[i]++;
                    //  printf("rows open at no %d blocks %d\n", i, rowsOpen[i]);
                      continue; // 'continue' means it's going to next column
                    }
                 }//--------------------------------------------------------------------for loop ends



                 int randomInsert;//---------------------------if there is no winner or sequence to block insert anywhere
                 randomInsert = rand() % M;
                 while(rowsOpen[randomInsert]<0){
                   randomInsert = rand() % M;
                 }
                 player2.col = randomInsert;
                 player2.row = rowsOpen[randomInsert];
                 if(aiInsertLimit==0&&block==0){
                 insert(board, player2);
                 aiInsertLimit++;
                 rowsOpen[randomInsert]--;


                  // printf("rows open at %d after random %d\n", randomInsert,rowsOpen[randomInsert]);
                 displayBoard(board);
                 x=1;
                 //break;
                 //printf("Ai's board after insert \n\n");
               }


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
        end://--------------------------------end of the game
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
