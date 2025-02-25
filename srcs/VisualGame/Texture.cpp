#include "VisualGame/VisualTexture.hpp"

VisualTexture::VisualTexture()
{
	_texture = nullptr;
}

VisualTexture::~VisualTexture()
{
	if (_texture != nullptr && _texture != NULL)
		SDL_DestroyTexture(_texture), _texture = nullptr;
}

int	VisualTexture::load(SDL_Renderer* renderer, const char* path, const char id)
{
	SDL_Surface*	surface;

	_id = id;
	
	surface = SDL_LoadBMP(path);
	if (surface == NULL)
		return (1);
	else
	{
		_texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (_texture == NULL)
			return (1);
	}

	return (0);
}
