#include "Player.h"

Player::Player(Team team) : pl_team{ team } {
    int y{ 0 }, fr{ 1 }, spr_y{ 1 };

    if (team == Team::black) {
        y = 7;
        fr = 6;
        spr_y = 0;
    }

    for (int x{ 0 }; x < 8; ++x) {
        if
            ((x == 0) || (x == 7))
            pl_pieces.push_back(std::make_shared<Rook>(x, y));
        else if
            ((x == 1) || (x == 6))
            pl_pieces.push_back(std::make_shared<Knight>(x, y));
        else if
            ((x == 2) || (x == 5))
            pl_pieces.push_back(std::make_shared<Bishop>(x, y));
        else if
            (x == 4)
            pl_pieces.push_back(std::make_shared<Queen>(x, y));
        else if
            (x == 3)
            pl_pieces.push_back(std::make_shared<King>(x, y));

        pl_pieces.push_back(std::make_shared<Pawn>(x, fr));

    }

    for (auto& piece : pl_pieces) {

        piece->set_team(pl_team);
        piece->get_sprite_pos().y = spr_y;

        if (piece->type == Type::king)
            crux = piece.get();
    }

}
