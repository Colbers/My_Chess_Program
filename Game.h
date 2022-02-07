#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "Board.h"
#include "Player.h"

enum class Game_State {
	Stasis = 0,	Potential = 1, Action = 2
};

enum class Game_Phase {
	Menu=0, Player1, Player2, Player3, Player4
};

enum class Game_Type {
	traditional=0, custom
};

namespace Chess {

	class Game {
	public:
		Game();
		Game(Game_Type);
		~Game();
		Game_State state{};
		Game_Phase phase{};
		Game_Type game_type{};
		Board* board{ nullptr };
		const position2d_t& Board() const { return board->size; }
		std::vector<Player>* player;
		void Next_Turn();
	};

	void initialize(Game&);
};

#endif
