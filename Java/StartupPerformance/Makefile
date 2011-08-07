StartupPerformance: SHELL:=/bin/bash
StartupPerformance: numloops:=100

all: StartupPerformance

%.class: %.java
	javac $^

StartupPerformance: StartupPerformance.class
	starttime=$$(date +%s%N); \
	for ((i=0; i<$(numloops); i++)) ; \
	do \
	java $(JAVAFLAGS) StartupPerformance ; \
	done ; \
	endtime=$$(date +%s%N) ; \
	echo Java StartupPerformance: time: $$((endtime - starttime)) ns
