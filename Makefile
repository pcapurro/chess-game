# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = shell-chess

SRCS = srcs/main.cpp \
	srcs/shell.cpp \
	srcs/visual.cpp \
	srcs/print.cpp \
	srcs/algebraicParser/algebraicBase.cpp \
	srcs/algebraicParser/algebraicChecker.cpp \
	srcs/algebraicParser/algebraicParser.cpp \
	srcs/algebraicParser/algebraicTools.cpp \
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

CXXFLAGS = #-Wall -Wextra -Werror

SDLFLAGS = -lSDL2

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(SDLFLAGS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)