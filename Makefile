NAME=vastChallenge
TESTS=tests
CC=g++
CFLAGS=-Wall
SRCS=main.cpp Truck/Truck.cpp App/App.cpp Utils/Utils.cpp Thread/Thread.cpp UnloadStation/UnloadStation.cpp FifoQueue/FifoQueue.cpp Common/Common.cpp
INC=./Truck ./App ./UnloadStation ./Utils
INC_PARAMS=$(INC:%=-I%)
OBJS=$(SRCS:.cpp=.o)
TEST_SRCS=tests.c circbuf.c
TEST_OBJS=$(TEST_SRCS:.c=.o)

.phony: all clean test

all: $(NAME)

# Build app executable
${NAME}: ${OBJS}
	${CC} -g ${CFLAGS} ${INC_PARAMS} -o ${NAME} ${OBJS}

# Compile all object files.
${OBJS} : %.o: %.cpp
	${CC} ${INC_PARAMS} -c -o $@ $<

test: ${TEST_OBJS} 
	${CC} ${CFLAGS} ${INC_PARAMS} -o ${TESTS} ${TEST_OBJS} 

# Clean
clean:
	rm -f ${NAME} ${TESTS} *.o Truck/*.o App/*.o Utils/*.o Utils/*.o Thread/*.o UnloadStation/*.o Common/*.o FifoQueue/*.o
