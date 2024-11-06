# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = shell-chess

SRCS = srcs/main.cpp \
	srcs/print.cpp \
	srcs/aiChess/aiChess.cpp \
	srcs/visualGame/visualDisplay.cpp \
	srcs/visualGame/visualRoutine.cpp \
	srcs/visualGame/visualFree.cpp \
	srcs/visualGame/visualInit.cpp \
	srcs/visualGame/visualTextures.cpp \
	srcs/visualGame/visualEvent.cpp \
	srcs/visualGame/visualTools.cpp \
	srcs/shellGame/shellInit.cpp \
	srcs/shellGame/shellRoutine.cpp \
	srcs/shellGame/shellFree.cpp \
	srcs/algebraParser/algebraBase.cpp \
	srcs/algebraParser/algebraChecker.cpp \
	srcs/algebraParser/algebraParser.cpp \
	srcs/algebraParser/algebraTools.cpp \
	srcs/chessBoard/boardHeart.cpp \
	srcs/chessBoard/boardCounter.cpp \
	srcs/chessBoard/boardPrint.cpp \
	srcs/chessBoard/boardTools.cpp \
	srcs/chessBoard/boardInit.cpp \
	srcs/chessBoard/boardFree.cpp \
	srcs/chessBoard/checkers/boardEndChecker.cpp \
	srcs/chessBoard/checkers/boardMoveChecker.cpp \
	srcs/chessBoard/checkers/boardPieceChecker.cpp \

CXX = c++

CXXFLAGS = # -Wall -Wextra -Werror

SDLFLAG = -lSDL2

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SDLFLAG)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)