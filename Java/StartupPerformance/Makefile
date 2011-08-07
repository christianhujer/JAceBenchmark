StartupPerformance: SHELL:=/bin/bash
StartupPerformance: numloops:=100

all: StartupPerformance

PrepareStartupPerformance:
	javac StartupPerformance.java

StartupPerformance: PrepareStartupPerformance
	starttime=$$(date +%s%N); \
	for ((i=0; i<$(numloops); i++)) ; \
	do \
	java $(JAVAFLAGS) StartupPerformance ; \
	done ; \
	endtime=$$(date +%s%N) ; \
	echo Java StartupPerformance: time: $$((endtime - starttime)) ns
