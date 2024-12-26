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

void	*visualTexture::load(SDL_Renderer *renderer, SDL_Surface *surface, int &baseCheck, const char *path)
{
	int	fail = false;

	if (baseCheck == 1)
		SDL_FreeSurface(surface);
	baseCheck = 0;

    surface = SDL_LoadBMP(path);
    if (surface == NULL)
		fail = true;
	else
	{
		baseCheck = 1;

		_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (_texture == NULL)
			fail = true;

		SDL_FreeSurface(surface);
		baseCheck = 0;
	}

	if (fail == true)
		return (nullptr);

	return (_texture);
}
