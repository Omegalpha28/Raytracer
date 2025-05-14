# ##
# ## EPITECH PROJECT, 2024
# ## B-OOP-400-LYN-4-1-arcade-loan.badey
# ## File description:
# ## Makefile
# ##

COMP = g++
FLAGS    = -Wall -Wextra -Werror -std=c++17 -fPIC -fno-gnu-unique -lconfig++
RM        = rm -rf
SFML_FLAGS = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lX11 -lXrandr -lXcursor -lXrender -lGL -lGLU -lpthread -ludev -lXi -fPIC

NAME = raytracer

SRC = main.cpp				\
		src/RayTracer.cpp	\
		src/Vector3D.cpp	\

OBJ  = $(SRC:.cpp=.o)

all:	comp

comp:	$(OBJ)
	$(COMP) -o $(NAME) $(OBJ) $(SFML_FLAGS) $(FLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
