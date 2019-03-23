
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
int N;
int M;
typedef struct player player;
struct player{
  int symbol;
  int row;
  int col;
};


void displayBoard(player board[N][M]){
    for (int i = 1; i<=N; i++){
          printf(" %d", i);
     }
        printf("\n");
        for(int x = 0; x<N; x++){
            for(int y = 0; y<M; y++){
                printf("|%d", board[x][y].symbol);
            }
            puts("|");
            printf("_");
            for (int i = 0; i<N; i++){
                  printf("__");
             }
             printf("\n");
        }
}

bool findWinner(player board[N][M], int symbol){//<---------make dynamic
  int counter = 0;
  for (int x = 0; x<N; x++){
    for (int y=0; y<M; y++){
      if (board[x][y].symbol == symbol){
          for (counter = 0; counter < 4; counter++){//right

            if (board[x][y+1+counter].symbol == symbol && (y<=N)) {//<---------make dynamic

              continue;
            }
            else{
              break;
            }
        }
        if (counter == 3){
          printf("Player %d won!\n", symbol);
        	return 1;
          //finish the game
        }
        else{
          counter = 0;
        }

        for (counter = 0; counter < 4; counter++){//---------right up
            if (board[x-1-counter][y+1+counter].symbol==symbol && (x>=0) && (y<=N)) {//<---------make dynamic
              continue;
            }
            else{
              break;
            }
        }
    /*
           0     1     2     3
      0  _____|__*__|_____|_____
      1  _____|_____|_____|_____
      2  _____|_____|_____|_____
      3  _____|_____|_____|_____|*/
        if (counter == 3){
          printf("Player %d won!\n", symbol);
           return 1;
          //finish the game
        }
        else{
          counter = 0;
        }
         for (counter = 0; counter < 4; counter++){//---------right down
            if (board[x+1+counter][y+1+counter].symbol==symbol && (x<=M) && (y<=N)) {
              continue;
            }
            else{
              break;
            }
        }
        if (counter == 3){
          printf("Player %d won!\n", symbol);
           return 1;
          //finish the game
        }
        else{
          counter = 0;
        }
        for (counter = 0; counter < 4; counter++){//---------down

            if (board[x+1+counter][y].symbol==symbol && (x<=M)) {

              continue;
            }
            else{
              break;
            }
        }
        if (counter == 3){
          printf("Player %d won!\n", symbol);
           return 1;
          //finish the game
        }
        else{
          counter = 0;
        }

      }
    }
  }
  return 0;
}




bool insert(player board[N][M], player player){////<---------make dynamic
  board[player.row][player.col]=player;
  bool win = findWinner(board, player.symbol);
  displayBoard(board);
  return win;
}


int main(void)
{
    char input[1] = "0";
    int gameChoice = 0;
    int playerTurn = 0;
    int winner = 0;
    int P1Wins = 0;
    int P2Wins = 0;
    int rounds = 0;
    printf("******HELLO WELCOME TO CONNECT 4******\n");

    printf("Press 1 for single player or 2 for two player!\n");
    scanf(" %s", input);

    while( (atoi(input) != 1) && (atoi(input) !=2) ){
      printf("ERROR: Invalid input\n");
      printf("Press 1 for single player or 2 for two player!\n");
      scanf("%s", input);
    }

    gameChoice = atoi(input);
    printf("choose your board size!\n");
    scanf("%d %d", &N, &M);//------------------------------------------------------make error message
    start:
    if (rounds>0){
      printf("*****ROUND %d *****\n ", rounds);
    }
    player board[N][M];
    for(int x = 0; x<N; x++){
        for(int y = 0; y<M; y++){
          board[x][y].symbol = '\0' ;
        }
      }

    if(gameChoice==2){

        while(winner != 1){

        int playerSymbol = 0;
        int x = 0;
        int row;
        int rowsOpen[N];
        for (int i = 0; i<N; i++){
           rowsOpen[N]= 'M' ;
        }
          top:
            if(x == 0){//if no one has gone
             playerSymbol = 0;
              displayBoard(board);
              x=1;
             goto top;
            }

           else if(x == 1){//if it is player 1's turn
                playerTurn = 1;
                playerSymbol = 1;
                char input[1] = "0";
                int location;
                 printf("player 1's turn\n");
                 player1:
                 printf("Choose row number where you want to insert (1-%d)\n", N);
                 scanf("%s", input);
                 while( (atoi(input) > N ) || atoi(input)<=0 ){
                   printf("ERROR: Invalid input\n");
                   printf("Choose row number where you want to insert (1-%d)\n", N);
                   scanf("%s", input);
                 }
                 location = atoi(input)-1;
                 row = rowsOpen[location];
                 player new_player;
                 new_player.col = location;
                 new_player.row = row;
                 new_player.symbol = playerSymbol;
                 bool win = insert(board, new_player);
             		 rowsOpen[location]--;
             			if (win == 1){//-----------------------------------------------------end of round
                    rounds++;
                    P1Wins++;
                        if(P1Wins==2){//------------------------winner of 2 out 3 rounds
                          goto end;
                        }
                    goto start;
                  }

                  x=2;
                  goto top;

            }
           else if(x == 2){//if it is player two turn
                playerTurn = 2;
                playerSymbol = 2;
                char input[1] = "0";
                int location;
                 printf("player 2's turn\n");
                 player2:
                 printf("Choose row number where you want to insert (0-6)\n");
                 scanf("%s", input);
                 while( (atoi(input) > N ) || atoi(input)<=0 ){
                   printf("ERROR: Invalid input\n");
                   printf("Choose row number where you want to insert (1-%d)\n", N);
                   scanf("%s", input);
                 }
                 location = atoi(input)-1;

                 row = rowsOpen[location];
                 player new_player;
                 new_player.col = location;
                 new_player.row = row;
                 new_player.symbol = playerSymbol;
             		 bool win = insert(board, new_player);
                 rowsOpen[location]--;
             			if (win == 1){//-------------------------------------------------------------------------------------end of round
                    rounds++;
                    P2Wins++;
                    if(P2Wins==2){
                      goto end;
                    }
                    goto start;

                  }

                 x=1;
                 goto top;
            }

        }
        end:
        printf("Thank you for Playing....Goodbye!");
        return 0;
    }

    return 0;
}
