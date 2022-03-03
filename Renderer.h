#ifndef RENDER_H
#define RENDER_H

#include "SDL_Handler.h"
#include "includes.h"
#include "Texture.h"

namespace screen {
	inline vi32_t default_size{ 1024,1024 };
	inline vi32_t default_cell{ default_size.x/8, default_size.y/8 };
}

struct window_spec {

	window_spec();
	window_spec(const char*);

	SDL_Window* object{ nullptr };

	pos2d pos{
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED
	};

	pos2d size{ screen::default_size };

	inline operator bool() const { return object != nullptr; }
};

struct sprite_plan {
	SDL::Rect sprite{ sprite::default_dim };
	SDL::Rect locale{ screen::default_cell };
};


struct Renderer {
	Renderer() = default;
	Renderer(window_spec const&);

	SDL_Renderer* self{ nullptr };
	Texture* texture{ nullptr };

	std::vector<sprite_plan> sprite_buffer;

	void buffer_add(sprite_plan const& sch) { sprite_buffer.push_back(sch); }
	void buffer_clear() { sprite_buffer.clear(); }

	void draw_buffer();

	bool load_texture(const char*);

	void clear();
	void copy(sprite_plan&);
	void present();
};

#endif

