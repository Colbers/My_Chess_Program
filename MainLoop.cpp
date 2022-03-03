#include "MainLoop.h"
#include "Move_Logic.h"
#include "Input_Logic.h"

void draw_piece(Piece* piece) {
    
    char p_token{};
    char p_team{};
    
	switch (piece->type) {
	case Type::king:
		p_token = 'K';
		break;

	case Type::queen:
		p_token = 'Q';
		break;

	case Type::bishop:
		p_token = 'B';
		break;

	case Type::knight:
		p_token = 'N';
		break;

	case Type::rook:
		p_token = 'R';
		break;

	case Type::pawn:
		p_token = 'P';
		break;

	default:
        p_token = '?';
		break;
	}
    if (piece->team == Team::black){
        p_team = 'b';
        p_token = tolower(p_token);
    }
    else
        p_team = 'w';
    
    std::cout << p_token;
}

static std::array<const char, 8> p_file{ 'a','b','c','d','e','f','g','h' };
static std::array<const char, 8> p_rank{ '1','2','3','4','5','6','7','8' };


void draw_cell(Cell const& cell) {
	if (cell.notEmpty())
		draw_piece(cell.piece.get());
}

std::ostream& operator<<(std::ostream& out, std::array<const char, 8>& arr) {
	for (auto x : arr)
		out << x;
		return out;
}

void draw_north(Board& board) {

    // variables for readability
    
	auto board_w{ board.size.x };
	auto board_h{ board.size.y };


	for (pos_t r{ 0 }; r < board_h; ++r) {
		for (pos_t f{ 0 }; f < board_w; ++f) {
                // we start drawing from the top, 8th rank.
               // to "climb down" we subtract
              // our index from the max, also
             // reduce index by one since arrays
            // start at 0, rather than 1
            
			pos_t _r = (board_h - r) - 1;

            // print the rank number at the start of row
            if (f == 0) std::cout << p_rank[_r];

            // draw piece or '*' if empty
			if (board.cell_position(f, _r).isEmpty())
				std::cout << '*';
			else
				draw_cell(board.cell_position(f,_r));

            // end of line, new line
            if (f == board_w - 1)
				std::cout << '\n';
		}
	}
      // space is added to account for the fact
     // that each row is one longer,
    // because each row prints its number + the row
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
            
        default:
            break;
	}
}

class Game{
public:
    Game() : pl_turn{ Team::white }{
        players.push_back(Player(Team::white));
        players.push_back(Player(Team::black));
    }
    void next_turn(){
        pl_turn =
        (pl_turn == Team::white) ?
        Team::black : Team::white;
    }
    Board board;
    std::vector<Player> players;
    Team pl_turn;
};

bool Player::my_turn(Game& game){
    return pl_team == game.pl_turn;
}

void print_size(const char* object){

}

void Chess::Run() {

	bool quit{ false };

	Board board;
    
    std::string FEN{
        "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR"
    };

	while (!quit) {
        
        generate_from_FEN(board, FEN);
		draw_board(board);

        
        
		quit = true;
		std::cout << "\nquit = true;\n";
	}
}
