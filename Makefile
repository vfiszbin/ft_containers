# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 15:33:50 by vfiszbin          #+#    #+#              #
#    Updated: 2023/01/17 14:54:13 by vfiszbin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME1 = exec_with_std
NAME2 = exec_with_ft

SOURCES = main.cpp
INCLUDES = map.hpp vector.hpp stack.hpp iterator.hpp utils.hpp

all : $(NAME1) $(NAME2)

$(NAME1) : $(SOURCES)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=1 -o $(NAME1) $(SOURCES)

$(NAME2) : $(SOURCES) $(INCLUDES)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=0 -o $(NAME2) $(SOURCES)

clean :
	$(RM) $(OBJECTS) $(DEPENDS)

fclean : clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)

re : fclean all

.PHONY : all clean fclean re