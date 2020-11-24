SRC_CONTEXT=src
TGT_CONTEXT=target
TEST_CONTEXT=test

DEPS=$(SRC_CONTEXT)/project.y $(SRC_CONTEXT)/project.l $(SRC_CONTEXT)/process.c
OUT=$(TGT_CONTEXT)/compiler

TEST_OUT=$(TEST_CONTEXT)/imp

INCLUDE=includes

$(OUT): $(DEPS)
	@mkdir -p $(TGT_CONTEXT)
	lex -o $(TGT_CONTEXT)/lex.yy.c $(SRC_CONTEXT)/project.l
	bison -b $(TGT_CONTEXT)/y -dy $(SRC_CONTEXT)/project.y
	gcc -o $@ $(TGT_CONTEXT)/y.tab.c -I $(INCLUDE) $(SRC_CONTEXT)/process.c $(TGT_CONTEXT)/lex.yy.c -lfl -lm
	#./a.out < inp

run: $(OUT) $(TEST_OUT)
	./$(OUT) < $(TEST_OUT)

all: $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean