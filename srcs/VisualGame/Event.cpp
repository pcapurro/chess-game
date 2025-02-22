#include "VisualGame/VisualGame.hpp"

std::string	VisualGame::waitForNewGame(void)
{
	SDL_Event	event;

	while (true)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN \
				&& event.key.keysym.sym == SDLK_RETURN)
				break ;

			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
			{
				_visualInfo.x = event.button.x, _visualInfo.y = event.button.y;

				if (_visualInfo.x > 782 && _visualInfo.y < 60)
				{
					if (event.type == SDL_MOUSEMOTION)
						SDL_SetCursor(_playCursor);
					if (event.type == SDL_MOUSEBUTTONDOWN)
						return ("restart");
				}
				else
					SDL_SetCursor(_normalCursor);
			}
		}
	}
	return ("error");
}

std::string  VisualGame::waitForPromotion(void)
{
	int					select = 0;
	std::vector<char>	types;
	SDL_Event			event;

	types.push_back('Q'), types.push_back('B'), types.push_back('N'), types.push_back('R');
	SDL_Rect obj = getRectangle(_visualInfo.actualCoords, "promotion");

	displayPromotion(types.at(select), _visualInfo.actualCoords);

	while (true)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
				break ;

			_visualInfo.x = event.button.x, _visualInfo.y = event.button.y;
			std::string coords = getCoord(_visualInfo.x, _visualInfo.y);

			if (isAbovePromotion(_visualInfo.x, _visualInfo.y, obj) == true)
			{
				SDL_SetCursor(_playCursor);

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					int x = _visualInfo.x;
					int y = _visualInfo.y;

					if (x > obj.x && x < obj.x + 20 && y < obj.y + 50 && select != 0)
						select--;
					if (x > obj.x + 88 && x < (obj.x + obj.w) && y < obj.y + 50 && select != 3)
						select++;
					if (x > obj.x + 32 && x < (obj.x + obj.w) - 32 && y > obj.y + 50 && y < (obj.y + obj.h))
						return (_visualInfo.actualCoords + types.at(select));

					displayPromotion(types.at(select), _visualInfo.actualCoords);
				}
			}
			else
				SDL_SetCursor(_normalCursor);
		}
	}

	return ("error");
}

std::string	VisualGame::waitForEvent(void)
{
	SDL_Event	event;

	while (true)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ("end");

			_visualInfo.x = event.button.x, _visualInfo.y = event.button.y;
			if (_visualInfo.x > 850 || _visualInfo.x < 0 || _visualInfo.y > 800 || _visualInfo.y < 0)
				_visualInfo.x = 0, _visualInfo.y = 0;
			_visualInfo.actualCoords = getCoord(_visualInfo.x, _visualInfo.y);

			if (event.type == SDL_KEYDOWN)
				reactKeyDown(event.key.keysym.sym);

			if (event.type == SDL_MOUSEMOTION)
				reactMouseMotion();

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (_visualInfo.x > 780 && _visualInfo.y < 60)
					return ("restart");
				reactMouseDown(event.button.button);
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (_visualInfo.droppedSrc == _visualInfo.actualCoords)
				{
					_visualInfo.clickSrc = _visualInfo.actualCoords;
					_visualInfo.droppedSrc.clear();
					_visualInfo.droppedDests.clear();
				}
				else
				{
					reactMouseUp();
					return (getInput(_visualInfo.actualCoords));
				}
			}

			displayGame(true);
		}
	}

	return ("error");
}
