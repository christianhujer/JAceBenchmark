include common.mak

.PHONY: all
## Run all available benchmarks.
all: StartupPerformance MemSpeed HdSpeed1 HdSpeed2


StartupPerformance:
	make -C Java/StartupPerformance/

.PHONY: MemSpeed
## Runs the memory speed benchmark.
MemSpeed:
	$(call timed, dd if=/dev/zero of=/dev/null bs=262144 count=262144)

.PHONY: HdSpeed1
## Runs the harddisk speed benchmark.
HdSpeed1:
	$(call timed, dd iflag=direct if=/dev/sda of=/dev/null bs=65536 count=65536)

.PHONY: HdSpeed2
## Runs the harddisk speed benchmark.
HdSpeed2:
	hdparm -t /dev/sda

.PHONY: MemInfo
MemInfo:
	dmidecode -t 17
