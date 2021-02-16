TARGET = $(BIN_DIR)/Calculator
OBJ_DIR = ../obj
BIN_DIR = ../bin
INC_DIR = ../inc
TEST_DIR = ../test
RUL_DIR = ../rules
SRC_DIR = .
OBJS = $(OBJ_DIR)/calc.o \
		$(OBJ_DIR)/parser.o \
		$(OBJ_DIR)/scanner.o \
		$(OBJ_DIR)/memory.o
FLEX_RULES = $(RUL_DIR)/scanner.l
BISON_RULES = $(RUL_DIR)/parser.y
FLEX_C = $(SRC_DIR)/scanner.c
BISON_C = $(SRC_DIR)/parser.c
BISON_H = $(INC_DIR)/token.h
CC = gcc
CFLAGS = -I$(INC_DIR)
RM 			= del /q /f /s
ARCHIVO_ENTRADA = $(TEST_DIR)/entrada.txt
ARCHIVO_ESPERADO = $(TEST_DIR)/esperado.txt
ARCHIVO_OBTENIDO = $(TEST_DIR)/obtenido.txt
# -----------------------------------------

$(TARGET): $(FLEX_C) $(BISON_C) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $@

$(FLEX_C): $(FLEX_RULES)
	@flex -o"$(FLEX_C)" "$(FLEX_RULES)"

$(BISON_C): $(BISON_RULES)
	@bison -yd -o"$(BISON_C)" "$(BISON_RULES)" --defines="$(BISON_H)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)*.d

.PHONY : clean
clean :
	@$(RM) "$(OBJ_DIR)/*.o"
	@$(RM) "$(OBJ_DIR)/*.d"
	@$(RM) "$(FLEX_C)"
	@$(RM) "$(BISON_C)"
	@$(RM) "$(BISON_H)"
	@$(RM) "$(TARGET).exe"
	@$(RM) "$(ARCHIVO_OBTENIDO)"
	
test : $(TARGET)
	@"$(TARGET).exe" < $(ARCHIVO_ENTRADA) > $(ARCHIVO_OBTENIDO)
	@comp "$(ARCHIVO_OBTENIDO)" "$(ARCHIVO_ESPERADO)" /M /A /L

run : $(TARGET)
	@$(TARGET)