//
//  Input_Logic.cpp
//  Chess
//
//  Created by Colbey Misico on 2/21/22.
//

#include "Input_Logic.h"

constexpr int num_of(char ch){ // utility function for readability
    return int(ch - '0');
}
constexpr pos_t to_file(char ch){
    return pos_t(ch - 'a');
}
constexpr pos_t to_rank(char ch){
    return pos_t(num_of(ch));
}

void constexpr Player::assimilate_pieces(const Board& board){
    
    // get all of our team on the board
    
    for (auto& cell : board.b_space)
        if (cell.piece->team == pl_team)
            pl_pieces.push_back(cell.piece);
}


void create_piece(Board& board, char ch,
                  pos_t const& x, pos_t const& y)
{
    // create a pointer referring to a shared dynamic object
    
    std::shared_ptr<Piece> mystery_piece;
    
    // if our input is valid,
    // mystery_piece should be substantiated
    
    switch (ch){ // to avoid repeat lines of code,
                // we'll set the team later
        case 'K':
        case 'k':
            mystery_piece = std::make_shared<King>(x,y);
            break;
        case 'Q':
        case 'q':
            mystery_piece = std::make_shared<Queen>(x,y);
            break;
        case 'B':
        case 'b':
            mystery_piece = std::make_shared<Bishop>(x,y);
            break;
        case 'N':
        case 'n':
            mystery_piece = std::make_shared<Knight>(x,y);
            break;
        case 'R':
        case 'r':
            mystery_piece = std::make_shared<Rook>(x,y);
            break;
        case 'P':
        case 'p':
            mystery_piece = std::make_shared<Pawn>(x,y);
            break;
            
        default:
            break;
    }
    
    // safety check: do nothing if invalid input
    
    if (mystery_piece){
        
        if (std::isupper(ch)) // clever case check here,
                             // avoiding repetitive code
            mystery_piece->set_team(Team::white);
        else
            mystery_piece->set_team(Team::black);
        
          // move mystery_piece
         // from current scope,
        // to board scope
        board.get_cell_at(x,y).piece = std::move(mystery_piece);
    }
}

void generate_from_FEN(Board& board, std::string& FEN) {
    
    int file{ 0 }; // we start at the beginning of the row
    int rank{ 7 }; // climb down from the top of the board
    
    for (auto ch : FEN){
        
        if (isalpha(ch))
        { // create the piece based on character input
            create_piece(board, ch, file, rank);
            ++file; // we probably put a piece down, go to next in line
        } else
            
        if (isnumber(ch)
        && (num_of(ch) + file) < 8)
        {
          // we don't want to overflow our row,
         // there are only 8 squares after all...
        // skip X spaces for X input
            file += num_of(ch);
        } else
            
        if (ch == '/')
        {               // FEN column break,
            --rank;    // go down a row
            file = 0; // reset to first of row,
                     // like a type writer
        }
    }
}

void Make_Move(Board& board, Piece* piece, const char x, const char y, Piece* crux){

}
