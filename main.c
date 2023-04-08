#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>     // for malloc
#include "raylib.h"

/*
    Asthetic variables
*/
#define SQ_SIZE 100
#define BD_SIZE (SQ_SIZE * 8)

/*
    Variables for the Rules of Chess
    unlikly to change... for NOW.
*/
#define NUM_CHESS_PIECE (16 + 16)




typedef struct{
    char type;  //K for king, Q for queen, R for rook, B for bishop, and N for knight, _ for pawn
    // will add image later, posibly just emoji
    char color;
    int x;
    int y;  
    bool moved;
    bool dead;
} Piece;

Color colorer(char c)
{
    Color result = BLACK;
    if (c == 'w')
        result = WHITE;
    
    return result;
}

Piece* get_pieces(void);

void chess_board(Color white, Color black, Piece* chess_set);



int main(void)
{
    
	// Initialize the window and background colour
	InitWindow(BD_SIZE, BD_SIZE, "Chess game");
	// SetConfigFlags(FLAG_VSYNC_HINT);
	SetTargetFPS(1);
	//SetBackgroundColor(BLACK);
	ClearBackground(PINK);
 
    Piece* current_board = get_pieces();

	while (!WindowShouldClose())
	{
        
        // Draw the chess board
		BeginDrawing();
		ClearBackground(BLACK);
		chess_board(BEIGE, BROWN, current_board);
		// DrawText(w_pawn.sym, 0, 0, 100, BLACK);
        // DrawFPS(0,0);



		// Draw the chess pieces
		// ...

		EndDrawing();

	}

	CloseWindow();
	return 0;
}

Piece* get_pieces() 
{
    Piece* chess_set = malloc(NUM_CHESS_PIECE * sizeof(Piece));

    int king_offset    = 4;
    int queen_offset   = 3;
    int bishop_offset  = 2;
    int knight_offset  = 1;
    int rook_offset    = 0;


    // Kings (0-1)
    Piece w_King = {'K', 'w', king_offset, 0};
    chess_set[0] = w_King;

    Piece b_King = {'K', 'b', king_offset, 7}; 
    chess_set[1] = b_King;

    // Queens (2-3)
    Piece w_Queen = {'Q', 'w', queen_offset, 0};
    chess_set[2] = w_Queen;
      
    Piece b_Queen = {'Q', 'b', queen_offset, 7};
    chess_set[3] = b_Queen;
    
    // Bishops (4-7)
    Piece wr_Bishop = {'B', 'w', (7 - bishop_offset), 0};
    chess_set[4] = wr_Bishop;

    Piece wl_Bishop = {'B', 'w', (0 + bishop_offset), 0};
    chess_set[5] = wl_Bishop;

    Piece br_Bishop = {'B', 'b', (7 - bishop_offset), 7};
    chess_set[6] = br_Bishop;

    Piece bl_Bishop = {'B', 'b', (0 + bishop_offset), 7};
    chess_set[7] = bl_Bishop;

    // kNights (8-11)
    Piece wr_Knight = {'N', 'w', (7 - knight_offset), 0};
    chess_set[8] = wr_Knight;

    Piece wl_Knight = {'N', 'w', (0 + knight_offset), 0};
    chess_set[9] = wl_Knight;

    Piece br_Knight = {'N', 'b', (7 - knight_offset), 7};
    chess_set[10] = br_Knight;

    Piece bl_Knight = {'B', 'b', (0 + knight_offset), 7};
    chess_set[11] = bl_Knight;

    // Rooks(12-15)
    Piece wr_Rook = {'R', 'w', (7 - rook_offset), 0};
    chess_set[12] = wr_Rook;

    Piece wl_Rook = {'R', 'w', (0 + rook_offset), 0};
    chess_set[13] = wl_Rook;

    Piece br_Rook = {'R', 'b', (7 - rook_offset), 7};
    chess_set[14] = br_Rook;

    Piece bl_Rook = {'R', 'b', (0 + rook_offset), 7};
    chess_set[15] = bl_Rook;
    
    // White's Pawns (16-23)
    for (int i = 16; i < (16 + 8); i++)
    {
        Piece pawn = {'P', 'w', (i - 16), 1};
        chess_set[i] = pawn;
    }

    // Black's Pawns (24-32)
    for (int i = 24; i < (24 + 8); i++)
    {
        Piece pawn = {'P', 'b', (i - 24), 6};
        chess_set[i] = pawn;
    }
    
    return chess_set;
}



void chess_board(Color white, Color black, Piece* chess_set)
{
    //Piece* chess_set = get_pieces();
    for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
                // these make the square black or white
				if((y + x) % 2 == 0)
					DrawRectangle(x * SQ_SIZE, y * SQ_SIZE, SQ_SIZE, SQ_SIZE, white);
				else
					DrawRectangle(x * SQ_SIZE, y * SQ_SIZE , SQ_SIZE, SQ_SIZE, black);

                for (int i = 0; i < NUM_CHESS_PIECE; i++)
                {
                    if (chess_set[i].x == x && chess_set[i].y == y && chess_set[i].dead == false)
				        DrawText(
                            TextFormat("%c", chess_set[i].type), // TextFormat converts char into string for the fx
                            x * SQ_SIZE, 
                            y * SQ_SIZE, 
                            SQ_SIZE, 
                            colorer(chess_set[i].color)
                        );
                }

			}
		}
}