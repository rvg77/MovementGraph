CONFIG_NAME = linux-sdk
GEN_NAME    = gen.py
IP          = 192.168.1.8

all: gen compil run 

gen: $(GEN_NAME)
	python3 $(GEN_NAME)

compil: CMakeLists.txt
	qibuild configure -c $(CONFIG_NAME)
	qibuild make      -c $(CONFIG_NAME)

run:
	./build-$(CONFIG_NAME)/sdk/bin/movementgraph
clear:
	rm -r build-$(CONFIG_NAME)
