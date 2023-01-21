#ifndef PIECE_H
#define PIECE_H

#include "includes.h"

inline pos_t file(pos2d_t const& pPos) { return pPos.x; }
inline pos_t rank(pos2d_t const& pPos) { return pPos.y; }

enum class Team { null = 0, white = 1, black = 2 };
enum class Type { null = 0, king, queen, bishop, knight, rook, pawn };

inline std::ostream& operator<<(std::ostream& out, Team t) {
    const char* team{};
    switch (t) {
    case Team::white: team = "white";
        break;
    case Team::black: team = "black";
        break;
    default: team = "???";
    }
    out << team;
    return out;
}

namespace sprite {
    inline vi32_t king     { 7, 0 };
    inline vi32_t queen    { 6, 0 };
    inline vi32_t bishop   { 5, 0 };
    inline vi32_t knight   { 4, 0 };
    inline vi32_t rook     { 3, 0 };
    inline vi32_t pawn     { 2, 0 };
}

class Piece {
public:
	Piece() = default;
	Piece(pos_t const& x, pos_t const& y);
	Piece(pos2d_t const&);

    /*
     Dev Philosophy:
        I decided that Pieces should generally calculate
        the math of the move, the idea
        being that we validate the move using logic
    */
    
            /* various checks */
    
	bool initial_position() const { return initPos; }
    virtual bool canMove(pos2d_t const& position);
    virtual bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }

    pos2d_t& get_pos() { return atPos; }
    void set_team(Team t) { p_team = t; }
    void set_direction(cardinal dir) { facing = dir; }
    vi32_t& get_sprite_pos() { return spr_pos; }
    void has_moved() { initPos = false; }

            /* const references */
    pos2d_t const& pos{ atPos };
    Type const& type{ p_type };
	Team const& team{ p_team };
    char const& note{ p_token };
    vi32_t const& sprite_locale{ spr_pos };
        
            /* the innate properties of a Piece */
protected:

    char p_token{ '?' };
    vi32_t spr_pos{};

	pos2d_t atPos{};
	Direction facing{ cardinal::null };
	Team p_team{ Team::null };
	Type p_type{ Type::null };
	bool initPos{ true };
};

using piece_ptr = std::shared_ptr<Piece>;

 // simple utility function to (loudly)
// grab the position of a piece
inline pos2d_t const& position_of(Piece* piece) { return piece->pos; }

        /* each Piece type is its own class */
class King : public Piece {
public:
	King(pos_t const& x, pos_t const& y) :
        King()
    {
        atPos = { x,y };
    }

	King(pos2d_t const& pos) :
        King(pos.x, pos.y) {}
    
    King()
    {
        p_type = Type::king;
        p_token = 'K';
        spr_pos = sprite::king;
    }

	bool canMove(pos2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Queen : public Piece {
public:
    Queen(pos_t const& x, pos_t const& y) :
        Queen()
    {
        atPos = { x,y };
    }
	Queen(pos2d_t const& pos) :
		Queen(pos.x, pos.y) {}
    
    Queen() {
        p_type = Type::queen;
        p_token = 'Q';
        spr_pos = sprite::queen;
    }

	bool canMove(pos2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Bishop : public Piece {
public:
	Bishop(pos_t const& x, pos_t const& y) :
        Bishop()
    {
        atPos = { x,y };
    }

	Bishop(pos2d_t const& pos) :
		Bishop(pos.x, pos.y) {}
    
    Bishop() { 
        p_type = Type::bishop;
        p_token = 'B';
        spr_pos = sprite::bishop;
    }

	bool canMove(pos2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Knight : public Piece {
public:
    Knight(pos_t const& x, pos_t const& y) :
        Knight()
    {
        atPos = { x,y };
    }
	Knight(pos2d_t const& pos) :
		Knight(pos.x, pos.y) {}
    
    Knight() {
        p_type = Type::knight;
        p_token = 'N';
        spr_pos = sprite::knight;
    }

	bool canMove(pos2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Rook : public Piece {
public:
    Rook(pos_t const& x, pos_t const& y) :
        Rook()
    {
        atPos = { x,y };
    }

	Rook(pos2d_t const& pos) :
		Rook(pos.x, pos.y) {}
    
    Rook() {
        p_type = Type::rook;
        p_token = 'R';
        spr_pos = sprite::rook;
    }
	
	bool canMove(pos2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Pawn : public Piece {
public:
    Pawn(pos_t const& x, pos_t const& y) :
        Pawn()
    {
        atPos = { x,y };
    }

	Pawn(pos2d_t const& pos) :
		Pawn(pos.x, pos.y) {}
    
    Pawn() {
        p_type = Type::pawn;
        p_token = 'P';
        spr_pos = sprite::pawn;
    }

	bool canMove(pos2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Player;

namespace alt {
class King {
public:
    King(pos_t const& x, pos_t const& y) :
        pos{ x, y } {}
    
    position2d_t pos;
    Type type{ Type::king };
    bool canMove(pos_t const& x, pos_t const& y);
};

}

#endif
