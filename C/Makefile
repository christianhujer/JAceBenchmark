include ../common.mak

OBJECTS:=$(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all
all: CPerformance

.PHONY: clean
clean:
	rm -rf *.c *.o

.PHONY: CPerformance
CPerformance: genfiles $(addsuffix .CPerformance,1 2 3 4 5 6 7 8)

.PHONY: %.CPerformance
%.CPerformance:
	rm -rf *.o
	$(call timed, bash -c "make -j $(patsubst %.CPerformance,%,$@) compile")

.PHONY: compile
compile: $(OBJECTS)

.PHONY: genFiles
genfiles:
	for ((i=0; i<100; i++)); do echo -e "#include <stdio.h>\n#include <stdlib.h>\n\nint main(void) { return 0; }" >$$(printf "source_%02d.c" $$i) ; done
