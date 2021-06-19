# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 16:51:08 by taemkim           #+#    #+#              #
#    Updated: 2021/06/19 15:43:36 by taemkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SRC_PATH = srcs
HDR_PATH = includes
OBJ_PATH = obj
LIBFT = libft/libft.a

SRC_CODE= utils.c

SRC_SERVER= server.c $(SRC_CODE)
SRC_CLIENT= client.c $(SRC_CODE)
HDR_NAME= minitalk.h

OBJ_SERVER= $(SRC_SERVER:.c=.o)
OBJ1= $(addprefix $(OBJ_PATH)/,$(OBJ_SERVER))
SRC1= $(addprefix $(SRC_PATH)/,$(OBJ_SERVER))

OBJ_CLIENT= $(SRC_CLIENT:.c=.o)
OBJ2= $(addprefix $(OBJ_PATH)/,$(OBJ_CLIENT))
SRC2= $(addprefix $(SRC_PATH)/,$(SRC_CLIENT))

HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))
FLAGS= -Wall -Wextra -Werror
H_FLAG= -I $(HDR_PATH)

COMP= gcc -g

all: $(SERVER) $(CLIENT)

$(SERVER) : $(LIBFT) $(OBJ1)
	@rm -rf $(SERVER)
	@$(COMP) $(H_FLAG) $(OBJ1) $(LIBFT) -o $@
	@echo "	Compilation of  $(SERVER):  \033[1;32mOK\033[m"

$(CLIENT) : $(LIBFT) $(OBJ2)
	@rm -rf $(CLIENT)
	@$(COMP) $(H_FLAG) $(OBJ2) $(LIBFT) -o $@
	@echo "	Compilation of  $(CLIENT):  \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH)
	@$(COMP)  $(FLAGS) $(H_FLAG)  -o $@ -c $<

$(LIBFT):
	@$(MAKE) all -C libft/
	@echo "	Compilation of  libft :  \033[1;32mOK\033[m"

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C libft/
	@echo "\033[1;33m>> all .o files are deleted.\033[0m"

fclean: clean
	@rm -rf $(SERVER)
	@echo "\033[0;31m>> $(SERVER) all obbjects are deleted.\033[0m"
	@rm -rf $(CLIENT)
	@echo "\033[0;31m>> $(CLIENT) all obbjects are deleted.\033[0m"
	@make fclean -C libft/
	@echo "\033[0;31m>> libft all obbjects are deleted.\033[0m"

re : fclean all
