#include "MainLoop.h"
#include "Game.h"
#include "Move_Logic.h"


//void rudimentary_draw_board(Chess::Game& game) {
//
//	auto board_x{ game.Board().x };
//	auto board_y{ game.Board().y };
//
//	for (pos_t rank{ 0 }; rank < board_y; ++rank) {
//		for (pos_t file{ 0 }; file <= board_x; ++file) {
//			if (file == board_x) std::cout << '\n';
//		}
//	}
//}
//

void draw_piece(Piece* piece) {
	switch (piece->type) {
	case Type::king:
		std::cout << 'K';
		break;

	case Type::queen:
		std::cout << 'Q';
		break;

	case Type::bishop:
		std::cout << 'B';
		break;

	case Type::knight:
		std::cout << 'N';
		break;

	case Type::rook:
		std::cout << 'R';
		break;

	case Type::pawn:
		std::cout << 'P';
		break;

	default:
		break;
	}
}

static std::array<const char, 8> p_file{ 'a','b','c','d','e','f','g','h' };
static std::array<const char, 8> p_rank{ '1','2','3','4','5','6','7','8' };


void draw_cell(const Cell* cell) {
	if (cell->notEmpty())
		draw_piece(cell->piece);
}

std::ostream& operator<<(std::ostream& out, std::array<const char, 8>& arr) {
	for (auto x : arr)
		out << x;
		return out;
}

void draw_north(Board& board) {

	auto board_w{ board.size.x };
	auto board_h{ board.size.y };


	for (pos_t r{ 0 }; r < board_h; ++r) {
		for (pos_t f{ 0 }; f < board_w; ++f) {
			pos_t _r = (board_h - 1) - r;

			if (f == 0) std::cout << p_rank[_r];

			if (board.position(f, _r)->isEmpty())
				std::cout << '*';
			else
				draw_cell(board.position(f,_r));

			if (f == board_w - 1)
				std::cout << '\n';
		}
	}
	std::cout << ' ' << p_file << '\n';
}

void draw_south(const Board& board) {

}

void draw_east(const Board& board) {

}

void draw_west(const Board& board) {

}

void draw_board(Board& board, cardinal facing = cardinal::north) {
	switch (facing) {

	case cardinal::north:
		draw_north(board);
		break;

	case cardinal::south:
		draw_south(board);
		break;

	case cardinal::east:
		draw_east(board);
		break;

	case cardinal::west:
		draw_west(board);
		break;
	}
}

void Chess::Run() {

	bool quit{ false };

	Board board;
	Player player1;
	Player player2;

	while (!quit) {

		//draw_board(board);
				
		quit = true;
		std::cout << "\nquit = true;\n";
	}
}