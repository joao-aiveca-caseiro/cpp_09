SRCS		= main.cpp RPN.cpp
INCS		= RPN.hpp
OBJS		= ${SRCS:.cpp=.o}
NAME		= RPN
CXX			= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98

$(NAME):	${OBJS} ${INCS}
			${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all