//
//  Input_Logic.h
//  Chess
//
//  Created by Colbey Misico on 2/21/22.
//

#ifndef Input_Logic_h
#define Input_Logic_h

#include "includes.h"
#include "Move_Logic.h"
#include "Player.h"

constexpr int num_of(char ch);

void create_piece(Board&, char, pos_t const&, pos_t const&);

void generate_from_FEN(Board&, std::string&);

std::string get_input();

#endif /* Input_Logic_h */
