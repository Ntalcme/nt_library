NAME 			= libnt.a
CC 				= gcc
CFLAGS			= -Wall -Werror -Wextra
AR 				= ar
ARFLAGS 		= rcs
RM 				= rm -rf
SRC_DIR 		= conversion fd str_utils nt_printf
SRCS 			=  $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJ_DIR     	= obj
OBJS 			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

all:			$(NAME)

$(NAME): 		$(OBJ_DIR) $(OBJS)
				$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR):	
				mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJ_DIR)
fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
