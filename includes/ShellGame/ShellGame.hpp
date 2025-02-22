#ifndef SHELLGAME_HPP
# define SHELLGAME_HPP

# include "Game.hpp"
# include "Shell.hpp"
# include "ChessBoard/ChessBoard.hpp"
# include "ChessAi/ChessAi.hpp"
# include "AlgebraParser/AlgebraParser.hpp"

class ShellGame
{
	public:

		ShellGame(const bool blindMode, const bool sandBoxMode);
		~ShellGame(void);

		void	shellRoutine(void);
		string	getShellAnswer(void) const;

	private:

		ChessBoard*		_board;
		ChessAi*		_ai;
		AlgebraParser*	_checker;

		const bool		_blindMode;
		const bool		_sandBoxMode;

		int				_aiSide;
};

#endif