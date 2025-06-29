NAME 			= libnt.a
CC 				= gcc
CFLAGS			= -Wall -Werror -Wextra -pedantic
AR 				= ar
ARFLAGS 		= rcs
RM 				= rm -rf
SRC_DIR 		= conversion fd str_utils nt_printf
SRCS 			=  $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJ_DIR     	= obj
OBJS 			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
DEP_FILES		= $(OBJS:.o=.d)
INSTALL_DIR		= /usr/local
INSTALL_LIB_DIR	= $(INSTALL_DIR)/lib
INSTALL_INC_DIR	= $(INSTALL_DIR)/include/$(NAME:.a=)

all:			$(NAME)

install:		all
				mkdir -p $(INSTALL_LIB_DIR)
				cp $(NAME) $(INSTALL_LIB_DIR)
				mkdir -p $(INSTALL_INC_DIR)
				cp libnt.h $(INSTALL_INC_DIR)
				for dir in $(SRC_DIR); do \
					mkdir -p $(INSTALL_INC_DIR)/$$dir; \
    				cp $$dir/*.h $(INSTALL_INC_DIR)/$$dir; \
				done
				@echo "$(NAME) library was installed in $(INSTALL_LIB_DIR) and its headers in $(INSTALL_INC_DIR) !"

uninstall:
				$(RM) $(INSTALL_LIB_DIR)/$(NAME)
				$(RM) $(INSTALL_INC_DIR)
				@echo "$(NAME) library was successfully uninstalled."

$(NAME): 		$(OBJ_DIR) $(OBJS)
				$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR):	
				mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include 		$(DEP_FILES)

clean:
				$(RM) $(OBJ_DIR)
fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re install uninstall
