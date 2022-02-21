//
//  Input_Logic.cpp
//  Chess
//
//  Created by Colbey Misico on 2/21/22.
//

#include "Input_Logic.h"

void create_piece(Board& board, char ch,
                  const pos_t& x, const pos_t& y)
{
    std::unique_ptr<Piece> mystery_piece;
    
    switch (ch){
        case 'K':
        case 'k':
            mystery_piece = std::make_unique<King>(x, y);
            break;
        case 'Q':
        case 'q':
            mystery_piece = std::make_unique<Queen>(x, y);
            break;
        case 'B':
        case 'b':
            mystery_piece = std::make_unique<Bishop>(x, y);
            break;
        case 'N':
        case 'n':
            mystery_piece = std::make_unique<Knight>(x, y);
            break;
        case 'R':
        case 'r':
            mystery_piece = std::make_unique<Rook>(x, y);
            break;
        case 'P':
        case 'p':
            mystery_piece = std::make_unique<Pawn>(x, y);
            break;
            
        default:
            break;
    }
    
    if (mystery_piece){
        if (std::isupper(ch))
            mystery_piece->set_team(Team::white);
        else
            mystery_piece->set_team(Team::black);
    }
}

void generate_from_FEN(Board& board, std::string FEN) {
    pos_t file{ 0 };
    pos_t rank{ 7 };
    
    for (auto ch : FEN){
        if (isalpha(ch))
            create_piece(board, ch, file, rank);
        else
            if (isnumber(ch)
                && (int(ch) + file) < 8)
                file += ch;
        else
            if (ch == '/')
                --rank;
    }
}
