#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Move_Logic.h"

class Game {
public:
	Game();

	void next_turn();
	bool player_turn(Player const&);
	bool valid_move(pos2d_t, pos2d_t);
	void make_move(pos2d_t, pos2d_t);

	void assimilate_pieces();

	uint16_t const& game_turn{ g_turn };
	Board const& board{ g_board };
	Board& get_board{ g_board };

	Board g_board;
	std::vector<Player> g_players;
	uint16_t g_turn{ 0 };
	Team pl_turn{};
};

//void create_piece(Board&, std::shared_ptr<Piece>&);

void generate_from_FEN(Board&, std::string&);


#endif