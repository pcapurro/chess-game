# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = shell-chess

SRCS = srcs/main.cpp \
	srcs/print.cpp \
	srcs/algebraicParser/algebraicParser.cpp \
	srcs/chessBoard/boardBase.cpp \
	srcs/chessBoard/boardCheckers.cpp \
	srcs/chessBoard/boardInit.cpp \
	srcs/chessBoard/boardFree.cpp \

CXX = c++

CXXFLAGS = #-Wall -Wextra -Werror

OBJS = $(SRCS:.cpp=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)