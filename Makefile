EXEC := TicTacToe
CORE_DIR := ./TTT_core
DISP_DIR := ./Dispatcher

all:
	cd ${CORE_DIR}; make all
	g++ -Wall -g -o ${EXEC} ${DISP_DIR}/dispatcher.cpp
	make clean
	
clean:
	-rm *.o *.d *~
	cd ${CORE_DIR}; make clean
