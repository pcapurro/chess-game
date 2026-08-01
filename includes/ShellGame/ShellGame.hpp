#ifndef SHELLGAME_HPP
# define SHELLGAME_HPP

# include "Game.hpp"
# include "Shell.hpp"
# include "ChessBoard.hpp"
# include "ChessAi.hpp"
# include "AlgebraParser.hpp"

class ShellGame
{
	public:

		ShellGame(void) = delete;
		ShellGame(const bool blindMode, const bool sandBoxMode);
		~ShellGame(void) = default;

		void					shellRoutine(void);

	private:

		void					initWelcome(void);
		void					printTitle(void);
		void					printGradually(const string str, const int value);

		void					printGame(void);

		string					getShellAnswer(void) const;

		optional<ChessBoard>	_board;
		optional<ChessAi>		_ai;
		AlgebraParser			_checker;

		const bool				_blindMode;
		const bool				_sandBoxMode;

		int						_aiSide;
};

#endif
