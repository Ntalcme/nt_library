NAME        		= libnt.a
CC          		= gcc
CFLAGS      		= -Wall -Wextra -Werror -pedantic -std=c99 -Iinclude -Isrc
AR          		= ar
ARFLAGS     		= rcs
RM          		= rm -rf

BUILD_DIR   		= build
OBJ_DIR     		= $(BUILD_DIR)/obj
LIB_DIR     		= $(BUILD_DIR)/lib

LIB_SRCS    		= $(shell find src/ -name '*.c')

LIB_OBJS    		= $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(LIB_SRCS))

DEP_FILES   		= $(LIB_OBJS:.o=.d)

INSTALL_DIR         = /usr/local
INSTALL_LIB_DIR     = $(INSTALL_DIR)/lib
INSTALL_INC_DIR     = $(INSTALL_DIR)/include/$(NAME:.a=)

all: 				$(LIB_DIR)/$(NAME)

install: 			all
					@echo "Installation of the $(NAME) library..."
					@mkdir -p $(INSTALL_LIB_DIR)
					@cp $(LIB_DIR)/$(NAME) $(INSTALL_LIB_DIR)
					@mkdir -p $(INSTALL_INC_DIR)
					@cp -r include/nt_library/* $(INSTALL_INC_DIR)/
					@echo "$(NAME) has been installed in $(INSTALL_LIB_DIR) and its headers in $(INSTALL_INC_DIR) !"
					@echo "Cleaning up local build files..."
					$(RM) $(BUILD_DIR)
					@echo "Local clean-up completed."

uninstall:
					@echo "Uninstalling the $(NAME) library..."
					$(RM) $(INSTALL_LIB_DIR)/$(NAME)
					$(RM) $(INSTALL_INC_DIR)
					@echo "$(NAME) has been uninstalled."

$(LIB_DIR)/$(NAME): $(LIB_OBJS) | $(LIB_DIR)
					@$(AR) $(ARFLAGS) $@ $(LIB_OBJS)
					@echo "Compilation completed."

$(OBJ_DIR)/%.o: 	src/%.c
					@mkdir -p $(dir $@)
					@echo "Compilation of $<..."
					@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
					@mkdir -p $@

$(OBJ_DIR):
					@mkdir -p $@

$(LIB_DIR):
					@mkdir -p $@

clean:
					@echo "Cleaning up object files and dependencies..."
					$(RM) $(OBJ_DIR)

fclean: 
					@echo "Cleaning up the $(NAME) library..."
					$(RM) $(BUILD_DIR)
					@echo "Local clean-up completed."

re: 				fclean all


-include 			$(DEP_FILES)

.PHONY: 			all lib clean fclean re install uninstall
