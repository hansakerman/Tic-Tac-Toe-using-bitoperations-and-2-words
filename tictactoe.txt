This is just loose ideas : D THe implemention became something else.

// Computer player that searches for solution. There is a 
/* Let's play a game of tic tac toe? Pen and paper you say? Nah.
   Before we play we need to programme and compile it on your
   favourite micro computer!

   Let' store the tic tac toe board in two 16-bit integers.
   Because why not.

   We will only use the most right-most part of the word.
   9 bits will give the maximum value of 511 (512 combinatons)

   We need to display the board and the binary value of the word and
   in hex/octal *of course*.  We need a game loop for everyting. We
   need user input.

   To be extremely user friendly input might be a position of 0-8 that is
   the power of binery number. 

   Perhaps we could use the 7 other bites for other stuff.

   If needed we could mask the uppermost 7 bits to ensure we are only using
   the significant lower 9 bits. Masking could be made by anding ( & ).
   Mask: binary: 00000001 1111 1111  hex: 0x01FF

   Later on we might check how the compiler translates this to machine code on different
   architectures like x86_64, arm64e, 6502 and Z80.

   we are trading clarity with a dose of insanity.
   what we could have done very easy we are doing this way.
*/

int display_board();
/*
-------
|X|O| |
| |X| |
|O|O|X|
-------
   XO  X OOX
X: 100010001
O: 010000110

Could we store it in octal values? We copy the bits to a transform pattern?
Or we do it momentarily?

are_you_winning() son!? That will be a fun function.
the golden octet!

Write corrensponding numbers to enter: This will also be the bit-"index".
8 7 6
5 4 3
2 1 0
Player NAUGHT: 0 
so either do a 2^(index number) or a right shift of a one?
*/

int main(){

  // we create a struct on the stack with the 16-bit integers.
  // O is naughts
  // X is crosses
  
  struct game_state {  
    uint16_t O;
    uint16_t X;
  };

struct game_state player = {0,0};

// test
printf("%d", player.O);


uint16_t win_pattern[8] = {
    0b00000000000000111,
    0b0000000000111000,
    0b0000000111000000,
    0b0000000100100100,   
    0b0000000010010010,
    0b0000000001001001,
    0b0000000001010100,
    0b0000000100010001 
    };
    // remember to add if the game is a draw game mechanics.
    
    /* Now let's think. Perhaps introduce the Golden Octet.  And map a
       frame (bit pattern) into the Golde Octet and when the Golden
       Octet is 0x111 = 07 (octal) then we we are winning son! Nah. Perhaps have
       just some winning values?

       Let's have think about the board

       Winning: 
       Board config:
       000 000 111
       000 111 000
       111 000 000
       
       Then the "word" is 00000000 00000111

       We could check by masking and chipping away the other bits.
       Or just compare?

       Winning horizontal combinations:

       0000000 000000111
       0000000 000111000    
       0000000 111000000

       Winning vertical combinations:

       Board config:
       100 010 001
       100 010 001
       100 010 001

       0000000 100100100
       0000000 010010010
       0000000 001001001

       Winning diagonal combinations:
       001 100
       010 010
       100 001

       0000000 001010100
       0000000 100010001

       So if any players have these values they have won!

       We should be able to and & this and make it true and that is a win?
       NAND with placement and O and X. NAND that together?

       So let's make an array of these eight 16 bits int array.

       Type           Binary               Dec  Oct   Hex
       Horizontal_0   0000000000000111     7    07    0x7
       Horizontal_1   0000000000111000     56   070   0x38
       Horizontal_2   0000000111000000     448  0700  0x1C0
       Vertical_0     0000000100100100     292  0444  0x124
       Vertical_1     0000000010010010     146  0222  0x92
       Vertical_2     0000000001001001     73   0111  0x49
       Diagonal_0     0000000001010100     84   0124  0x54
       Diagonal_1     0000000100010001     273  0421  0x111
    */

}
