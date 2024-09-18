#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0


#define BLACK_KING 'E'
#define BLACK_QUEEN 'Q'
#define BLACK_BISHOP 'B'
#define BLACK_KNIGHT 'K'
#define BLACK_TOWER 'T'
#define BLACK_PAWN 'P'

#define NO_PIECE '#'

#define WHITE_KING 'e'
#define WHITE_QUEEN 'q'
#define WHITE_BISHOP 'b'
#define WHITE_KNIGHT 'k'
#define WHITE_TOWER 't'
#define WHITE_PAWN 'p'

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

#define WHITES_TURN 1
#define BLACKS_TURN 0


typedef struct _PlayingField_ {

    char pieces[8][8];
    char current_turn;

}PlayingField;

void printPlayingField(PlayingField* field);
void generateStartingMap(PlayingField* field);
char move(PlayingField* field);
int turnCharIntoLocation(char c);
char checkIfWhitePiece(char i);
char isMovePossible(char piece, char startpoint[2], char destination[2], PlayingField* field);

int main(void) {

    /*
        set playing Field
        white pieces = lowercase
        black pieces = uppercase

        E/e = Emperor (King)
        Q/q = Queen
        B/b = Bishop
        K/k = Knight
        T/t = Tower
        P/p = Pawn

    */
    PlayingField* field = (PlayingField*) calloc(1, sizeof(PlayingField));
    field->current_turn = WHITES_TURN;


    generateStartingMap(field);
    printPlayingField(field);
 
    while(!move(field)) {
        printPlayingField(field);
    }
}

void printPlayingField(PlayingField* field) {

    printf("  A B C D E F G H \n");
    for(int i = 0; i < 8; i++) {
        printf("%d ", (i+1)); 

        for(int j = 0; j < 8; j++) {
            printf("%c ", field->pieces[i][j]);
        }

        printf("%d\n", (i+1));
    }
    
    printf("  A B C D E F G H \n");
}

void generateStartingMap(PlayingField* field) {

    //Towers
    field->pieces[0][A] = WHITE_TOWER;
    field->pieces[0][H] = WHITE_TOWER;
    field->pieces[7][A] = BLACK_TOWER;
    field->pieces[7][H] = BLACK_TOWER;
    
    //Knights
    field->pieces[0][B] = WHITE_KNIGHT;
    field->pieces[0][G] = WHITE_KNIGHT;
    field->pieces[7][B] = BLACK_KNIGHT;
    field->pieces[7][G] = BLACK_KNIGHT;

    //bishops
    field->pieces[0][C] = WHITE_BISHOP;
    field->pieces[0][F] = WHITE_BISHOP;
    field->pieces[7][C] = BLACK_BISHOP;
    field->pieces[7][F] = BLACK_BISHOP;

    //Kings
    field->pieces[0][E] = WHITE_KING;
    field->pieces[7][E] = BLACK_KING;

    //Queens
    field->pieces[0][D] = WHITE_QUEEN;
    field->pieces[7][D] = BLACK_QUEEN;

    
    //Pawns
    char pawn = WHITE_PAWN;
    for(int row = 1; row < 7;)  {
        for(int i = 0; i < 8; i++) {

            field->pieces[row][i] = NO_PIECE; // ! change this to pawn later
            
        }
        if(row == 1) {
            row = 6;
            pawn = BLACK_PAWN;
        }else{
            row++;
        }
    }
    

    for(int i = 2; i < 6; i++) {
        for(int j = 0; j < 8; j++) {
            field->pieces[i][j] = NO_PIECE;
        }
    }


}

char move(PlayingField* field) {

    printf("What's your move? (Starting point - Destination): ");
    char startpoint[2];
    char destination[2];
    char input_buffer[50];
    scanf("%s", input_buffer);
    
    int seperationlocation = 51;

    int cursor = 0;

    for(int i = 0; i < 50; i++) {
        if(input_buffer[i] == '\0') {
            break;
        }else{
            if(input_buffer[i] != ' ') {
                if(input_buffer[i] == '-') {
                    seperationlocation = i;
                    
                }else if(i < seperationlocation) {
                    startpoint[cursor] = input_buffer[i];
                    cursor++;
                }else{ // its bigger than the minus
                    destination[i - (seperationlocation + 1)] = input_buffer[i];
                    if(i - (seperationlocation + 1) > 1) {
                        break;
                    }
                }   
                
            }
        }
    }

    if(field->current_turn == WHITES_TURN) {

        
        char piece = field->pieces[(startpoint[1]-'0')-1][turnCharIntoLocation(startpoint[0])];
        if(piece == -1) {
            printf("FUUUUCK %d\n", __LINE__);
            return false;
        }

        printf("Chosen Piece %c on %c%c\n", piece, startpoint[0], startpoint[1]);
        if(checkIfWhitePiece(piece)) {
            
            //if move is possible change turn if not reask
            if(isMovePossible(piece, startpoint, destination, field)) {
                printf("move valid\n");

                char destination_piece = field->pieces[(destination[1] - '0') -1][turnCharIntoLocation(destination[0])];

                if(destination_piece == BLACK_KING) {

                    printf("White has Won the game! \n");
                    
                    return true;
                }else if(checkIfWhitePiece(destination_piece)){
                    
                    printf("Please try not to kill your own Piece next time <3\n");

                    return false;

                }else{

                    //in the array it's Row | collumn
                    field->pieces[(destination[1] - '0') - 1][turnCharIntoLocation(destination[0])] = piece;
                    field->pieces[(startpoint[1] - '0') - 1][turnCharIntoLocation(startpoint[0])] = NO_PIECE;


                    //field->current_turn = BLACKS_TURN;

                    return  false;
                }

            }else{
                printf("Move invalid, please enter a valid move!\n");
                return false;
            }





            
        }else{
            printf("not your piece!\n");
            return false;
        }

    }else{ // Blacks Turn

    }

    

    return true;

}

int turnCharIntoLocation(char c) {

    switch (c)
    {
    case 'A':
        return A;
    case 'B':
        return B;
    case 'C':
        return C;
    case 'D':
        return D;
    case 'E':
        return E;
    case 'F':
        return F;
    case 'G':
        return G;
    case 'H':
        return H;
    default:
        return -1;

    }
}

char checkIfWhitePiece(char i) {

    switch (i)
    {
    case WHITE_BISHOP:
    case WHITE_KING:
    case WHITE_KNIGHT:
    case WHITE_PAWN:
    case WHITE_QUEEN:
    case WHITE_TOWER:
        return true;
        break;
    
    default:
        return false;
        break;
    }


}

/*
    give the numbers as a decimal.
*/
char isMovePossible(char piece, char startpoint[2], char destination[2], PlayingField* field) {
    if(piece == WHITE_TOWER || piece == BLACK_TOWER) { // TOWER
        //one position has to be ident - Style: A1 {0, 1}
        char verticalmove = 2;
        printf("Tower Defense\n");
        if(startpoint[0] == destination[0] && startpoint[1] != destination[1]) {
            verticalmove = false;
        }else if(startpoint[1] == destination[1] && startpoint[0] != destination[0]){
            verticalmove = true;
        }else{
            return false;
        }
        //                                            Horizontal | Vertical
        // it is saved in the char array of the Field as { Number | Letter } and in the char array as Letter | Number
        if(verticalmove) { // Numbers stay constant

            if(destination[0] > startpoint[0]) { //going right (comparing the letters)

                //it checks the way until the piece on the destination, you have to check that one later
                for(int i = 1; i < (destination[0]-startpoint[0]); i++) {

                    if(field->pieces[(startpoint[0]-'0') + i][turnCharIntoLocation(startpoint[1])] != NO_PIECE) {
                        return false;
                    }

                }

            }else{ //going left

                for(int i = 1; i < (startpoint[0]-destination[0]); i++) {

                    if(field->pieces[(startpoint[0]-'0') - i][turnCharIntoLocation(startpoint[1])] != NO_PIECE) {
                        return false;
                    }

                }

            }

        }else{ // Letters stay constant (comparing)

            if(destination[1] > startpoint[1]) {

                for(int i = 1; i <(destination[1]-startpoint[1]); i++) {

                     if(field->pieces[turnCharIntoLocation(startpoint[1]) + i][(startpoint[0]-'0')] != NO_PIECE) {
                        return false;
                    }

                }

            }else{

                for(int i = 1; i < (startpoint[1]-destination[1]); i++) {
 
                    if(field->pieces[turnCharIntoLocation(startpoint[1]) - i][(startpoint[0]-'0')] != NO_PIECE) {
                        return false;
                    }

                }

            }

        }



        return true;
    }else if(piece == WHITE_KNIGHT || piece == BLACK_KNIGHT) { // Knight

    }else if(piece == WHITE_BISHOP || piece == BLACK_BISHOP) {

    }

    //this is a test

    return false;

}