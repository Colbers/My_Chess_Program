//
//  Input_Logic.h
//  Chess
//
//  Created by Colbey Misico on 2/21/22.
//

#ifndef Input_Logic_h
#define Input_Logic_h

#include "includes.h"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

int num_of(char ch);

void create_piece(Board&, char, const pos_t&, const pos_t&);

void generate_from_FEN(Board&, std::string&);

#endif /* Input_Logic_h */
