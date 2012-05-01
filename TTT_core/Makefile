SRC := $(wildcard *.cpp)
OBJ := ${SRC:.cpp=.o}
LIBS := 
CC := g++
CFLAGS := -Wall -g -std=c++0x

all: ${OBJ}
	${CC} ${CFLAGS} -o TTT ${LIBS} ${OBJ}

#generate dependancy files at the same time as object compilation
%.o : %.cpp
	${CC} ${CXX_FLAGS} -MD -g -o $@ -c $< 
	@cp $*.d $*.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	 	  -e '/^$$/ d' -e 's/$$/ :/' < $*.P >> $*.d; \
	  rm -f $*.P

clean:
	-rm *.o *.d *~
	
force: clean
force: all

debug: CFLAGS += -DDEBUG
debug: CXX_FLAGS += -DDEBUG
debug: all

debug_verbose: CFLAGS += -DDEBUGV
debug_verbose: CXX_FLAGS += -DDEBUGV
debug_verbose: all

