#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
const int N = 6;
const int M = 7;

typedef struct player player;
struct player{
  int symbol;
  int row;
  int col;
  int gameWinner;//<--------------------trying to use this as my counter
  // struct player *right;
  // struct player *down;
  // struct player *rightDown;
  // struct player *rightUp;
};

// typedef struct{
//   int v;
//   struct player *array;
//
// }graph;

void displayBoard(player board[6][7] ){
    printf(" 0 1 2 3 4 5 6\n");
    for(int x = 0; x<N; x++){
        for(int y = 0; y<M; y++){

            printf("|%d", board[x][y].symbol);

        }
        puts("|");
        puts("---------------");

    }
}
void buildGraph(player board[6][7], player player){///<--------------------------need to rename as findWinner
  int symbol = player.symbol;
  struct player playerFound;
  for (int x = 0; x<N; x++){
    for (int y=0; y<M; y++){
      if ((board[x][y+1].symbol == board[x][y].symbol) && (board[x][y].symbol != 0) &&  (y<6) ) {//<----------------right increment
        // player.right=&board[x][y+1];
        playerFound.gameWinner++;
        printf("Game winner is %d\n",player.gameWinner);
        if(playerFound.gameWinner == 4){
          printf("Winner! right\n");
          break;
        }


      }
      else if ((board[x-1][y+1].symbol==board[x][y].symbol) && (board[x][y].symbol != 0) && (y<6) && (x>0)){//<--------------right up increment
        // player.rightUp=&board[x-1][y+1];
        playerFound.gameWinner++;
        if(playerFound.gameWinner == 4){
          printf("Winner! right up\n");
          break;
        }

      }
      else if ((board[x+1][y+1].symbol==board[x][y].symbol) && (board[x][y].symbol != 0) && (y<6) && (x<5)){//<-----------------right down increment
        // player.rightUp=&board[x+1][y+1];
      playerFound.gameWinner++;

        if(playerFound.gameWinner == 4){
          printf("Winner! right down\n");
          break;
        }

      }
      else if ((board[x+1][y].symbol==board[x][y].symbol) && (board[x][y].symbol != 0) && (x<5)){//<---------------------------down increment
        // player.rightUp=&board[x+1][y];
        playerFound.gameWinner++;
        if(playerFound.gameWinner == 4){
          printf("Winner! down\n");
          break;
        }


      }
    }
  }
}




void insert(player board[6][7], player player){//inserting a player into my board or graph
  printf("INSERTING at %d\n", player.col);
  board[player.row][player.col]=player;
  buildGraph(board, player);
  displayBoard(board);
 return;

}


int main(void)
{


    player board[6][7] = { '\0' };
    //player.gameChoice=0;
    int gameChoice;
    int playerTurn = 0;
    int winner = 0;
    printf("******HELLO WELCOME TO CONNECT 4******\n");
    printf("Press 1 for single player or 2 for two player!\n");
    scanf("%d", &gameChoice);
    if(gameChoice==2){
        while(winner != 1){
        int playerSymbol = 0;
        int x = 0;
        int row;
        int rowsOpen[7]={5, 5, 5, 5, 5, 5, 5};
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
                int location;
                 printf("player 1's turn\n");
                 player1:
                 printf("Choose row number where you want to insert (0-6)\n");
                 scanf("%d", &location);
                 if (rowsOpen[location]<0||location>6||location<0){//error message
                   printf("ERROR INVALID INPUT TRY AGAIN\n");
                   goto player1;
                 }
                 row = rowsOpen[location];
                 player new_player;
                 new_player.col = location;
                 new_player.row = row;
                 new_player.symbol = playerSymbol;
                 insert(board, new_player);//<-----watch this line for spontaneos errors
                 rowsOpen[location]--;



                  x=2;
                  goto top;


            }
           else if(x == 2){//if it is player two turn
                playerTurn = 2;
                playerSymbol = 2;
                int location;
                 printf("player 2's turn\n");
                 player2:
                 printf("Choose row number where you want to insert (0-6)\n");
                 scanf("%d", &location);
                 if (rowsOpen[location]<0||location>6||location<0){//error message
                   printf("ERROR INVALID INPUT TRY AGAIN\n");
                   goto player2;
                 }
                 row = rowsOpen[location];
                 player new_player;
                 new_player.col = location;
                 new_player.row = row;
                 new_player.symbol = playerSymbol;
                 insert(board, new_player);
                 rowsOpen[location]--;



                 x=1;
                 goto top;
            }

        }
    }

    return 0;
}
