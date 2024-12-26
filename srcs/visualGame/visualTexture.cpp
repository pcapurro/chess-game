#include "visualTexture.hpp"

visualTexture::visualTexture()
{
	_texture = nullptr;
}

visualTexture::~visualTexture()
{
	if (_texture != nullptr && _texture != NULL)
		SDL_DestroyTexture(_texture);
}

void	*visualTexture::load(SDL_Renderer *renderer, const char *path)
{
	int			fail = false;
	SDL_Surface	*surface;

    surface = SDL_LoadBMP(path);
    if (surface == NULL)
		fail = true;
	else
	{
		_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (_texture == NULL)
			fail = true;

		SDL_FreeSurface(surface);
	}

	if (fail == true)
		return (nullptr);

	return (_texture);
}
