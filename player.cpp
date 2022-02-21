#include "Player.h"

void constexpr Player::create_pieces() {
    pos_t y{0}, fr{1};
    
    if (pl_team == Team::black){
        y = 7;
        fr = 6;
    }
    
    pl_pieces.emplace_back(new Rook   ( 0, y ));
    pl_pieces.emplace_back(new Knight ( 1, y ));
    pl_pieces.emplace_back(new Bishop ( 2, y ));
    pl_pieces.emplace_back(new Queen  ( 3, y ));
    pl_pieces.emplace_back(new King   ( 4, y ));
    pl_pieces.emplace_back(new Bishop ( 5, y ));
    pl_pieces.emplace_back(new Knight ( 6, y ));
    pl_pieces.emplace_back(new Rook   ( 7, y ));
    
    for (auto x{0}; x < 8; ++x)
        pl_pieces.emplace_back(new Pawn(x, fr));
    
}

void Player::create_team(){
    for (auto& piece : pl_pieces)
        piece->set_team(pl_team);
}



