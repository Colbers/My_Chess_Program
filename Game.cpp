#include "Game.h"

Chess::Game::Game() : state{ Game_State::Stasis } {}

Chess::Game::~Game() {}

void Chess::Game::Next_Turn() {
	switch (game_type) {
	case Game_Type::traditional:
		phase = (phase == Game_Phase::Player1) ?
			Game_Phase::Player2 : Game_Phase::Player1;
		break;

	default:
		break;
	}
}

void Chess::initialize(Game& game) {
	game.board = new Board();
}