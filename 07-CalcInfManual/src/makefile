TARGET = $(BIN_DIR)/Calculator
OBJ_DIR = ../obj
BIN_DIR = ../bin
INC_DIR = ../inc
SRC_DIR = .
TEST_DIR = ../test
OBJS = $(OBJ_DIR)/calc.o \
		$(OBJ_DIR)/parser.o \
		$(OBJ_DIR)/scanner.o \
		$(OBJ_DIR)/memory.o
CC = gcc
CFLAGS = -I$(INC_DIR)
RM 			= del /q /f /s
ARCHIVO_ENTRADA = $(TEST_DIR)/entrada.txt
ARCHIVO_ESPERADO = $(TEST_DIR)/esperado.txt
ARCHIVO_OBTENIDO = $(TEST_DIR)/obtenido.txt

$(TARGET) : $(OBJS)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)*.d

.PHONY : clean
clean :
	@$(RM) "$(OBJ_DIR)/*.o"
	@$(RM) "$(OBJ_DIR)/*.d"
	@$(RM) "$(TARGET).exe"
	@$(RM) "$(ARCHIVO_OBTENIDO)"
	
test : $(TARGET)
	@"$(TARGET).exe" < $(ARCHIVO_ENTRADA) > $(ARCHIVO_OBTENIDO)
	@comp "$(ARCHIVO_OBTENIDO)" "$(ARCHIVO_ESPERADO)" /M /A /L

run : $(TARGET)
	@$(TARGET)