## Use bash as shell.
# This is to be able to use extended shell options.
SHELL:=/bin/bash

## Shell options.
# Make sure that as soon as something fails, stop.
export SHELLOPTS:=pipefail:errexit

# Runs a timed loop.
# The \p 2 command is run in a loop of \p 1 count iterations.
# The time in ns it took to execute the loop is then printed to stdout.
# @param 1 Number of repetitions for the loop.
# @param 2 Command to loop.
timedloop=starttime=$$(date +%s%N); for ((i=0; i<$(1); i++)); do $(2); done; endtime=$$(date +%s%N); echo $@: time: $$((endtime - starttime)) ns

# Runs a timed command.
# The \p 1 command is run.
# The time in ns it took to execute the command is then printed to stdout.
# @param 1 Comand to time.
timed=starttime=$$(date +%s%N); $(1); endtime=$$(date +%s%N); echo $@: time: $$((endtime - starttime)) ns
