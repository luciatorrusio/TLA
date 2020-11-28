GCC_FLAGS=-lfl -lm -g -Wall -Wno-unused-function -O3

SRC_CONTEXT=src
TGT_CONTEXT=target
TEST_CONTEXT=test

DEPS=$(SRC_CONTEXT)/project.y $(SRC_CONTEXT)/project.l $(SRC_CONTEXT)/process.c $(SRC_CONTEXT)/translate.c $(SRC_CONTEXT)/tree_printing.c
OUT=$(TGT_CONTEXT)/compiler

INPUT=code.im
OUTPUT=out

RUNNER=imma

INCLUDE=includes

$(OUT): $(DEPS)
	@mkdir -p $(TGT_CONTEXT)
	lex -o $(TGT_CONTEXT)/lex.yy.c $(SRC_CONTEXT)/project.l
	bison -b $(TGT_CONTEXT)/y -v -dy $(SRC_CONTEXT)/project.y
	gcc -o $@ $(TGT_CONTEXT)/y.tab.c -I $(INCLUDE) $(SRC_CONTEXT)/process.c $(SRC_CONTEXT)/translate.c $(SRC_CONTEXT)/tree_printing.c $(TGT_CONTEXT)/lex.yy.c $(GCC_FLAGS)

$(OUTPUT): $(OUT) $(INPUT)
	./$(OUT) $(OUTPUT) < $(INPUT)

compile: $(OUT) $(INPUT) $(OUTPUT)

run: $(OUTPUT)
	./$(RUNNER) $(OUTPUT)

all: $(OUT)

clean:
	rm -rf $(TGT_CONTEXT)/*

.PHONY: all clean