include ../common.mak

CFLAGS?=-std=c99 -W -Wall -pedantic

OBJECTS:=$(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all
all: CPerformance

.PHONY: clean
clean:
	rm -rf source_*

.PHONY: CPerformance
CPerformance: genfiles $(addsuffix .CPerformance,1 2 3 4 5 6 7 8)

.PHONY: %.CPerformance
%.CPerformance:
	rm -rf source_*.o
	$(call timed, bash -c "make -j $(patsubst %.CPerformance,%,$@) compile")

.PHONY: compile
compile: $(OBJECTS)

.PHONY: genFiles
genfiles:
	for ((i=0; i<100; i++)); do cp template.c $$(printf "source_%02d.c" $$i) ; done
