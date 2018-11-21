CONFIG_NAME = linux-sdk
GEN_NAME    = generator.py
IP          = 192.168.1.2


all: gen compil run 

gen: $(GEN_NAME)
	python3 $(GEN_NAME) --vertex ./test/vertex.txt --edges ./test/edge.txt --out automaticInitGeneration.h


compil: CMakeLists.txt
	qibuild configure -c $(CONFIG_NAME)
	qibuild make      -c $(CONFIG_NAME)

run:
	./build-$(CONFIG_NAME)/sdk/bin/movementgraph --pip ${IP}
clear:
	rm -r build-$(CONFIG_NAME)
