#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NO_WINPATTERNS 8

// This is not entirely serious. : ) The datamodel is built in two integers and bit operations.

// BUGS: Scanf still have stuff in input buffer if you accidentaly press wrong key (like a letter).

void render_board(uint16_t O, uint16_t X){
  int mask;
  printf("\n\t");
  for(int i = 8; i >= 0 ; --i){
    mask = 1 << i;
    if(O & mask){
      printf("O ");
    } else if(X & mask) {
      printf("X ");
    } else {
      printf("%d ", i + 1);
    }
    if ((i % 3) == 0 ) printf("\n\t");
  }
  printf("\n");
}

const char *legal_move(uint16_t O, uint16_t X, short input){
  short mask = 1 << (input - 1);
  if( (O | X) & mask ){
   return "Illegal move: Space occupied.\n";
  } else {
    return NULL;
  }
}

const char *check_input(short input){
  if ( 1 > input || input > 9)
    {
      return "Illegal move: Write input as 1-9.\n";
    }
  return 0;
}

int get_player_input(uint16_t O, uint16_t X ,char *player){
  short input;
  short legal = 0;

  while ( !legal ) {
    printf("Play as %s: ", player);
    scanf("%hd", &input);
    
    const char *error_i = check_input(input);
    if (error_i != NULL){
      printf("%s", error_i);
      continue;
    }

    const char *error_l = legal_move(O, X, input);
    if (error_l != NULL){
      printf("%s", error_l);
      continue;
    }
    
    legal = 1;
  }
  return input;
}

void apply_move(uint16_t *current,int played){
  // Mask the current board with the new move. 
  *current |= 1 << (played - 1);
}

void check_win(uint16_t *O, uint16_t *X, uint16_t win_pattern[8]){
  for (int i = 0; i < NO_WINPATTERNS ; ++i ){
    
    if ( (*O & win_pattern[i]) == win_pattern[i] ){
      printf("NOUGHT WINS!\n");
      exit(0);
    }

    if ( (*X & win_pattern[i]) == win_pattern[i] ){
      printf("CROSSES WINS!\n");
      exit(0);
    }
  }

  // A full board gives the value 2^9 and we exit as draw.
  if( (*O | *X) == 0b111111111){
    printf("Full board. DRAW!\n");
    exit(0);
  }

}

int main(){

  // Player state struct
  struct game_state {  
    uint16_t O;
    uint16_t X;
  };

  // The eight win patterns for tic tac toe.
  // we are only using the 9 least significant bits of the 16-bit unsigned integer.
uint16_t win_pattern[8] = {
    0b0000000111,
    0b000111000,
    0b111000000,
    0b100100100,   
    0b010010010,
    0b001001001,
    0b001010100,
    0b100010001 
    };

 struct game_state player = { 0, 0 };

 short played; 
 // Game loop

 while ( 1 ) { // should be until win. We look at the winning patterns.
   render_board(player.O, player.X);
   check_win(&player.O, &player.X, win_pattern);

   // Player 1 NAUGHTS
   played = get_player_input(player.O, player.X,"O");
   apply_move(&player.O,played);

   render_board(player.O, player.X);
   check_win(&player.O, &player.X, win_pattern);

   // Player 2 CROSSES
   played = get_player_input(player.X, player.O,"X");
   apply_move(&player.X,played);
 }
}

