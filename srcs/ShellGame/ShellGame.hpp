#ifndef SHELLGAME_HPP
# define SHELLGAME_HPP

# include "../../includes/Game.hpp"
# include "../../includes/Shell.hpp"
# include "../ChessBoard/ChessBoard.hpp"
# include "../ChessAi/ChessAi.hpp"
# include "../AlgebraParser/AlgebraParser.hpp"

class ShellGame
{
	public:

		ShellGame(const bool blindMode, const bool sandBoxMode);
		~ShellGame(void);

		bool	fail(void) const
			{ return (_error); };

		void	shellRoutine(void);
		string	getShellAnswer(void) const;

	private:

		ChessBoard*		_board;
		ChessAi*		_ai;
		AlgebraParser*	_checker;

		const bool		_blindMode;
		const bool		_sandBoxMode;

		int				_aiSide;

		bool			_error;

};

#endif