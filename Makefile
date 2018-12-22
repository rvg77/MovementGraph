CONFIG_NAME = linux-sdk
GEN_NAME    = generator.py
IP          = 192.168.1.2
VERTEXSET   = ./test/vertex.txt
EDGESET     = ./test/edge.txt
OUTPUT      = automaticInitGeneration.h

all: gen compil run

gen: $(GEN_NAME)
	python3 $(GEN_NAME) --vertex $(VERTEXSET) --edges $(EDGESET) --out $(OUTPUT)


compil: CMakeLists.txt
	qibuild configure -c $(CONFIG_NAME)
	qibuild make      -c $(CONFIG_NAME)

run:
	./build-$(CONFIG_NAME)/sdk/bin/graphcreator --pip ${IP}
clear:
	rm -r build-$(CONFIG_NAME)
