#ifndef PIECE_H
#define PIECE_H

#include "includes.h"
#include "vector.h"
#include "Direction.h"

inline pos_t file(const position2d_t& pPos) { return pPos.x; }
inline pos_t rank(const position2d_t& pPos) { return pPos.y; }

enum class Team { null = 0, white = 1, black = 2 };
enum class Type { null = 0, king, queen, bishop, knight, rook, pawn };

class Piece {
public:
	Piece() = default;
	Piece(Type, const pos_t& x, const pos_t& y);
	Piece(Team, Type, const pos_t& x, const pos_t& y);
	Piece(Team, Type, const position2d_t&);

	bool initial_position() const { return initPos; }
	void has_moved() { initPos = false; }
	virtual bool canMove(const position2d_t& position);
    virtual	bool canMove(const pos_t x, const pos_t y) { return canMove(position2d_t(x, y)); }
	const position2d_t& origin() const { return atPos; }

	position2d_t& get_pos() { return atPos; }
	void set_team(Team t) { p_team = t; }
	friend const position2d_t position(Piece*);

	const position2d_t& pos{ atPos };
	const Type& type{ p_type };
	const Team& team{ p_team };

protected:
	position2d_t atPos{};
	Team p_team{ Team::null };
	Type p_type{ Type::null };
	bool initPos{ true };
};

inline const position2d_t position(Piece* piece) { return piece->atPos; }

using piece_container = std::vector<std::unique_ptr<Piece>>;

class King : public Piece {
public:
	King(Team _team, const pos_t& pos_x, const pos_t& pos_y) :
		Piece(_team, Type::king, pos_x, pos_y)
	{}

	King(Team _team, const position2d_t& pos) :
		King(_team, pos.x, pos.y)
	{}

	King(const pos_t& x, const pos_t& y) :
		King(Team::null, x, y)
	{}
	King(const position2d_t& p) :
		King(p.x, p.y)
	{}
	
	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
		return canMove(position2d_t(x, y)); }
};

class Queen : public Piece {
public:
	Queen(Team _team, const pos_t& pos_x, const pos_t& pos_y) :
		Piece(_team, Type::queen, pos_x, pos_y)
	{}

	Queen(Team _team, const position2d_t& pos) :
		Queen(_team, pos.x, pos.y)
	{}

	Queen(const pos_t& x, const pos_t& y) :
		Queen(Team::null, x, y)
	{}
	Queen(const position2d_t& p) :
		Queen(p.x, p.y)
	{}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) { return canMove(position2d_t(x, y)); }
};

class Bishop : public Piece {
public:
	Bishop(Team _team, const pos_t& pos_x, const pos_t& pos_y) :
		Piece(_team, Type::bishop, pos_x, pos_y)
	{}

	Bishop(Team _team, const position2d_t& pos) :
		Bishop(_team, pos.x, pos.y)
	{}

	Bishop(const pos_t& x, const pos_t& y) :
		Bishop(Team::null, x, y)
	{}
	Bishop(const position2d_t& p) :
		Bishop(p.x, p.y)
	{}
	
	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) { return canMove(position2d_t(x, y)); }
};

class Knight : public Piece {
public:
	Knight(Team _team, const pos_t& pos_x, const pos_t& pos_y) :
		Piece(_team, Type::knight, pos_x, pos_y)
	{}

	Knight(Team _team, const position2d_t& pos) :
		Knight(_team, pos.x, pos.y)
	{}

	Knight(const pos_t& x, const pos_t& y) :
		Knight(Team::null, x, y)
	{}
	Knight(const position2d_t& p) :
		Knight(p.x, p.y)
	{}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) { return canMove(position2d_t(x, y)); }
};

class Rook : public Piece {
public:
	Rook(Team _team, const pos_t& pos_x, const pos_t& pos_y) :
		Piece(_team, Type::rook, pos_x, pos_y)
	{}

	Rook(Team _team, const position2d_t& pos) :
		Rook(_team, pos.x, pos.y)
	{}
	
	Rook(const pos_t& x, const pos_t& y) :
		Rook(Team::null, x, y)
	{}
	Rook(const position2d_t& p) :
		Rook(p.x, p.y)
	{}
	
	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) { return canMove(position2d_t(x, y)); }
};

class Pawn : public Piece {
public:
	Pawn(Team _team, const pos_t& pos_x, const pos_t& pos_y, const direction& _face) :
		Piece(_team, Type::pawn, pos_x, pos_y), facing{ _face }
	{}

	Pawn(Team _team, const position2d_t& pos, const direction& _face) :
		Pawn(_team, pos.x, pos.y, _face)
	{}

	Pawn(const pos_t& x, const pos_t& y, const direction& facing) :
		Pawn(Team::null, x, y, facing)
	{}
	Pawn(const position2d_t& p, const direction& facing) :
		Pawn(p.x, p.y, facing)
	{}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) { return canMove(position2d_t(x, y)); }
	direction facing;
};

//namespace alt {
//	struct Motion;
//
//	class Piece {
//		position2d_t pos{};
//		Type type{};
//		Team team{};
//		bool init_pos{ true };
//
//		friend bool can(const Piece&, const Motion&);
//	};
//
//	bool king_move(const position2d_t& origin, const Motion& motion) {
//
//	}
//
//	bool can(const Piece& piece, const Motion& motion) {
//		using enum Type;
//		const position2d_t& origin{ piece.pos };
//		switch (piece.type) {
//		case king: king_move(piece.pos, motion);
//			break;
//		case queen: queen_move(piece.pos, motion);
//			break;
//		case bishop: bishop_move()
//		}
//	}
//
//}

#endif