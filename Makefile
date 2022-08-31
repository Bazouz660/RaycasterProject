##
## EPITECH PROJECT, 2022
## SpageGameRepo
## File description:
## Makefile
##

GREY   = $ \x1b[30m
RED    = $ \x1b[31m
GREEN  = $ \x1b[32m
YELLOW = $ \x1b[33m
BLUE   = $ \x1b[34m
PURPLE = $ \x1b[35m
CYAN   = $ \x1b[36m
WHITE  = $ \x1b[37m

END    = $ \x1b[0m
BOLD   = $ \x1b[1m
UNDER  = $ \x1b[4m
REV    = $ \x1b[7m

IGREY   = $ \x1b[40m
IRED    = $ \x1b[41m
IGREEN  = $ \x1b[42m
IYELLOW = $ \x1b[43m
IBLUE   = $ \x1b[44m
IPURPLE = $ \x1b[45m
ICYAN   = $ \x1b[46m
IWHITE  = $ \x1b[47m

SRC	=	src/core.c	\
		src/screen.c	\
		src/projection/walls.c	\
		src/raycasting/cast.c	\
		src/utils/get_min_max.c	\
		src/collision/level_collision.c	\
		src/level/grid.c	\
		src/matrix/matrix.c	\
		src/entities/update.c	\
		src/entities/creation.c	\
		src/entities/movement.c	\
		src/render/draw.c	\
		src/inits/init.c	\
		src/utils/smooth_color.c	\
		src/utils/vectors.c	\
		src/utils/string.c	\
		src/utils/itoa.c	\
		src/utils/random.c	\
		src/utils/new_sprite.c	\
		src/utils/circle_bounds.c	\
		src/utils/get_arr_len.c	\
		src/utils/fps.c	\
		src/utils/radian_to_degree.c	\
		src/utils/sound.c	\
		src/utils/get_angle.c	\
		src/utils/view.c	\
		src/utils/str_to_wa.c	\
		src/utils/my_strcat.c	\
		src/utils/absolute_value.c	\
		src/utils/init_texture.c	\
		src/utils/create_window.c	\
		src/utils/init_frect.c	\
		src/utils/set_sprite_pos.c	\
		src/utils/get_sprite_center.c	\
		src/utils/positive.c	\

CFLAGS = -g -I./include -I C:/CSFML/include -L C:/CSFML/lib/gcc -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

OBJ =	$(SRC:.c=.o)

%.o: %.c
	@gcc -o $@ -c $< $(CFLAGS)
	@printf "\t${PURPLE}%s\n${END}"  $<

NAME =	Raycaster

all: $(NAME)

$(NAME): header $(OBJ) done
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)

header:
	@printf "${IWHITE}               ${BOLD}${PURPLE}FILES                  \
	${END}\n"

done:
	@printf "${IGREEN}          ${BOLD}${WHITE}BUILD SUCCESSFUL            \
	${END}\n"

clean:
	@printf "${IWHITE}               ${BOLD}${GREY}CLEAN                    \
	${END}\n\n"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
