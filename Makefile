NAME = libmx.a

LIBMX = libmx

USH = ush

SRC = src/*.c src/console_parser/*.c src/command_handler/*.c src/validator_handler/*.c src/terminal_signal/*.c

OBJ = obj

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make -C ./libmx 
	@clang $(FLAGS) $(SRC) -L libmx -lmx -o $(USH)

uninstall: clean
	@rm -rf ./libmx/$(NAME)
	@rm -rf $(USH)

clean:
	@rm -rf $(OBJ)

reinstall: uninstall all
