# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAMEV = chess-game

NAMES = shell-chess

SRCSO = srcs/failPrint.cpp \
	srcs/algebraParser/algebraBase.cpp \
	srcs/algebraParser/algebraChecker.cpp \
	srcs/algebraParser/algebraParser.cpp \
	srcs/algebraParser/algebraTools.cpp \
	srcs/chessAi/chessAiInit.cpp \
	srcs/chessAi/chessAiEvaluate.cpp \
	srcs/chessAi/chessAiHeart.cpp \
	srcs/chessAi/chessAiTools.cpp \
	srcs/chessAi/chessAiAttack.cpp \
	srcs/chessAi/chessAiCounter.cpp \
	srcs/chessAi/chessAiDefense.cpp \
	srcs/chessAi/chessAiPassivity.cpp \
	srcs/chessAi/chessAiRandom.cpp \
	srcs/chessAi/chessAiCheckers.cpp \
	srcs/chessBoard/boardHeart.cpp \
	srcs/chessBoard/tools/boardCounter.cpp \
	srcs/chessBoard/tools/boardPrint.cpp \
	srcs/chessBoard/tools/boardTools.cpp \
	srcs/chessBoard/boardInit.cpp \
	srcs/chessBoard/boardFree.cpp \
	srcs/chessBoard/checkers/boardEndChecker.cpp \
	srcs/chessBoard/checkers/boardMoveChecker.cpp \
	srcs/chessBoard/checkers/boardPieceChecker.cpp \

SRCS_V = srcs/visualGame.cpp \
	srcs/visualGame/visualDisplay.cpp \
	srcs/visualGame/visualRoutine.cpp \
	srcs/visualGame/visualFree.cpp \
	srcs/visualGame/visualInit.cpp \
	srcs/visualGame/visualTextures.cpp \
	srcs/visualGame/visualEvent.cpp \
	srcs/visualGame/visualTools.cpp \
	$(SRCSO)

SRCS_S = srcs/shellGame.cpp \
	srcs/shellGame/shellInit.cpp \
	srcs/shellGame/shellRoutine.cpp \
	srcs/shellGame/shellFree.cpp \
	$(SRCSO)

CXX = c++

CXXFLAGS = # -Wall -Wextra -Werror

SDLFLAG = -lSDL2

OBJSV = $(SRCS_V:.cpp=.o)

OBJSS = $(SRCS_S:.cpp=.o)

## === RULES === ##

classic: $(NAMEV)

shell: $(NAMES)

all: $(NAMEV) $(NAMES)

$(NAMEV): $(OBJSV)
	$(CXX) $(CXXFLAGS) $(OBJSV) -o $(NAMEV) $(SDLFLAG)

$(NAMES): $(OBJSS)
	$(CXX) $(CXXFLAGS) $(OBJSS) -o $(NAMES)

re: fclean all

clean:
	@rm -rf $(OBJSS) $(OBJSV)

fclean: clean
	@rm -rf $(NAMEV) $(NAMES)