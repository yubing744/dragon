include config.mk

EXE = test
SRC = test.c obj_loader.c
OBJ = $(SRC:.c=.o)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

.o:
	@echo CC $<
	@$(CC) -c $<

clean:
	rm -f ${OBJ} $(EXE)

dist: clean

.PHONY: clean dist
