#include "Game.h"

Game::Game() : pl_turn{ Team::white }{
	g_players.push_back(Player(Team::white));
	g_players.push_back(Player(Team::black));

    assimilate_pieces();

}

void Game::assimilate_pieces() {
    for (auto& player : g_players) {
        for (auto& piece : player.pl_pieces) {
            g_board.get_cell_at(piece->pos).piece = piece;
        }
    }
}

void Game::next_turn() {
	pl_turn =
	(pl_turn == Team::white) ?
	Team::black : Team::white;

	++g_turn;
}

bool Game::player_turn(Player const& player) {
	return pl_turn == player.pl_team;
}

bool Game::valid_move(pos2d_t og, pos2d_t to) {

	auto selected_piece{ g_board.cell_position(og).piece };

	if (og > g_board.size || to > g_board.size) {
		std::cout << "Invalid: Position out of scope.\n";
		return false;
	}
	if (!selected_piece) {
		std::cout << "Invalid: No piece selected.\n";
		return false;
	}
	else if (selected_piece->team != pl_turn) {
		std::cout << "Invalid: " << pl_turn << " is to move.\n";
		return false;
	}

	return Legal_Move({ &g_board, selected_piece.get(), to }, g_players[(int)pl_turn-1].crux);
}

void Game::make_move(pos2d_t og, pos2d_t to) {

	if (!valid_move(og, to)) {
		std::cout << "\nInvalid: Error\n";
		return;
	}
	g_board.get_cell_at(to).release();

	Motion motion{ &g_board, og, to };

	Move(motion);

}

void create_piece(Board& board, piece_ptr p, pos_t x, pos_t y)
{
    p->get_pos() = pos2d_t(x, y);
    board.get_cell_at(x, y).nowHolds(p);
}

piece_ptr get_piece_from_token(char t) {

    piece_ptr mystery_piece;

    auto assign_piece = [&]<class T>(T) { mystery_piece = std::make_shared<T>(); };

    switch (t) {
        case 'K':
        case 'k': 
            assign_piece(King());
            break;
        case 'Q':
        case 'q':
            assign_piece(Queen());
            break;
        case 'B':
        case 'b':
            assign_piece(Bishop());
            break;
        case 'N':
        case 'n':
            assign_piece(Knight());
            break;
        case 'R':
        case 'r':
            assign_piece(Rook());
            break;
        case 'P':
        case 'p':
            assign_piece(Pawn());
            break;

        default:
            break;
    }

    if (isupper(t))
        mystery_piece->set_team(Team::white);
    else
        mystery_piece->set_team(Team::black);

    return mystery_piece;
}

void generate_from_FEN(Board& board, std::string& FEN) {

    auto num_of = [](char ch) { return (int)ch - '0'; };
    
    int file{ 0 }; // we start at the beginning of the row
    int rank{ 7 }; // climb down from the top of the board
    
    for (auto ch : FEN){
        
        if (isalpha(ch))
        { // determine piece to be made based on character token
            // process token
            // give result to create_piece()
            create_piece(board, get_piece_from_token(ch), file, rank);
            ++file; // we probably put a piece down, go to next in line
        } else
            
        if (isdigit(ch)
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


