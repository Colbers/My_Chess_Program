#ifndef APP_H
#define APP_H

#include "Renderer.h"
#include "Game.h"


class Application {
public:
	Application();
	~Application();

	int Run();

	bool Initialize();

	void on_Event(SDL_Event*);
	void on_Loop();
	void on_Render();

	void Cleanup();

	inline auto get_mouse_pos();

private:

	Game game{};

	bool running{ true };

	vector2d<int> mouse_pos{};

	bool holding_piece{ false };

	window_spec window{};

	Renderer render;

	Texture texture_asset{};

};

#endif