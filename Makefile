# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAMEV = chess-game

NAMES = shell-chess

SRCSO = srcs/AlgebraParser/Init.cpp \
	srcs/AlgebraParser/Checker.cpp \
	srcs/AlgebraParser/Parser.cpp \
	srcs/AlgebraParser/Tools.cpp \
	srcs/ChessAi/Heart.cpp \
	srcs/ChessAi/Init.cpp \
	srcs/ChessAi/Free.cpp \
	srcs/ChessBoard/Heart.cpp \
	srcs/ChessBoard/Init.cpp \
	srcs/ChessBoard/Evaluate.cpp \
	srcs/ChessBoard/tools/Counter.cpp \
	srcs/ChessBoard/tools/Print.cpp \
	srcs/ChessBoard/tools/Testers.cpp \
	srcs/ChessBoard/tools/Tools.cpp \
	srcs/ChessBoard/tools/EndCheckers.cpp \
	srcs/ChessBoard/tools/EvaluateCheckers.cpp \
	srcs/ChessBoard/tools/MoveCheckers.cpp \
	srcs/ChessBoard/tools/PieceCheckers.cpp \

SRCS_V = srcs/visualGame.cpp \
	srcs/VisualGame/Display.cpp \
	srcs/VisualGame/Routine.cpp \
	srcs/VisualGame/Free.cpp \
	srcs/VisualGame/Init.cpp \
	srcs/VisualGame/Ressources.cpp \
	srcs/VisualGame/Texture.cpp \
	srcs/VisualGame/Event.cpp \
	srcs/VisualGame/React.cpp \
	srcs/VisualGame/Tools.cpp \
	$(SRCSO)

SRCS_S = srcs/shellGame.cpp \
	srcs/ShellGame/Init.cpp \
	srcs/ShellGame/Routine.cpp \
	srcs/ShellGame/Free.cpp \
	$(SRCSO)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I includes/

SDLFLAG = -lSDL2

OBJSV = $(SRCS_V:.cpp=.o)

OBJSS = $(SRCS_S:.cpp=.o)

## === RULES === ##

visual: $(NAMEV)

shell: $(NAMES)

all: $(NAMEV) $(NAMES)

$(NAMEV): $(OBJSV)
	$(CXX) $(CXXFLAGS) $(OBJSV) -o $(NAMEV) $(SDLFLAG)

$(NAMES): $(OBJSS)
	$(CXX) $(CXXFLAGS) $(OBJSS) -o $(NAMES)

clean:
	@rm -f .stockfish.answer
	@rm -rf $(OBJSS) $(OBJSV)

fclean: clean
	@rm -rf $(NAMEV) $(NAMES)