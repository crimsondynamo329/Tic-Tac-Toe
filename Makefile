CORE_DIR := ./TTT_core

all:
	cd ${CORE_DIR}; make all
	make clean
	
clean:
	-rm *.o *.d *~
	cd ${CORE_DIR}; make clean
