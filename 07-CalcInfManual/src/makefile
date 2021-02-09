TARGET 		= $(BIN_DIR)/Calculator
OBJ_DIR		= ../obj		#.o
BIN_DIR		= ../bin		#app
INC_DIR		= ../inc 		#headers
SRC_DIR		= .				#.c y makefile
OBJS		= $(OBJ_DIR)/calc.o 	\
			  $(OBJ_DIR)/parser.o 	\
			  $(OBJ_DIR)/scanner.o 	\
			  $(OBJ_DIR)/memory.o

CFLAGS		= -Wall
CC			= gcc
RM 			= del /Q /F
FLEX_RULES 	= scanner.l
FLEX_C 		= scanner.c
BISON_RULES = parser.y
BISON_C 	= parser.c
BISON_H 	= y.tab.h

default: $(TARGET)
all: default

$(TARGET) : $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# $< y $@ sustituye el nombre el target y el source
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c					#Genero un .o por cada .c en el DIR
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@
# $< = SRC_DIR y $@ = OBJ_DIR
# mkdir -p crea si no existe el directorio

.PHONY : clean
clean :
	$(RM) -r $(OBJ_DIR) $(BIN_DIR)