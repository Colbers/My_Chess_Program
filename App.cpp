#include "App.h"

inline auto Application::get_mouse_pos() {
	return SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
}

Application::Application() :
	window{"Title"},
	render{ window }
{}

Application::~Application() {

}


bool Application::Initialize() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	render.texture = &texture_asset;

	render.load_texture("D:/Game Asset/Sprites/2D Sprite/Chess/ChessFullSS.bmp");

	return (window);
}

int Application::Run() {

	if (!Initialize())
		return -1;

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			on_Event(&event);
		}

		on_Loop();
		on_Render();
	}

	Cleanup();

	return 0;
}

void Application::on_Event(SDL_Event* event) {
	if (event->type == SDL_QUIT)
		running = false;
}

void Application::on_Loop() {

	get_mouse_pos();

}

void Application::on_Render() {

	render.clear();

	auto square = [](int x, int y) {
		sprite_plan sq;
		(x + y) % 2 == 0 ?
			sq.sprite.set_index(1, 0) :
			sq.sprite.set_index(0, 0);

		sq.locale.set_index(x, y);
		return sq;
	};

	auto spr_of = [](piece_ptr piece, int x, int y) {
		sprite_plan p;
			p.sprite.set_index(piece->sprite_locale);
			p.locale.set_index(x, y);
			return p;
	};

	Board const& board = game.board;

	for (auto y{ 0 }; y < board.height; ++y) {
		for (auto x{ 0 }; x < board.width; ++x) {

			auto const& cell{ board.cell_position(x,y) };
			
			render.buffer_add(square(x,y));

			if (cell.notEmpty()) {

				render.buffer_add(spr_of(cell.piece, x, y));
			}
		}
	}

//	piece_ptr knight{ std::make_shared<Knight>() };
//	sprite_plan plan;
//	plan.sprite.set_index(knight->sprite_locale);

	SDL::Rect mouse_box{ screen::default_cell };

	mouse_box.set_position(mouse_pos % screen::default_cell);

	//plan.locale.set_position(mouse_pos.x/2, mouse_pos.y / 2);
//	render.buffer_add(plan);

	render.draw_buffer();
	
	SDL_RenderDrawRect(render.self, &mouse_box);

	render.present();

}

void Application::Cleanup() {
	SDL_Quit();
}


