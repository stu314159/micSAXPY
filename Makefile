CC=icpc
CC_FLAGS=-mmic -openmp -Wno-unknown-pragmas
SOUCES=saxpy_test.cpp
OBJECTS=saxpy_test.o

TARGET=saxpy_test

%.o: %.cpp
	$(CC) $(CC_FLAGS) -c $^

$(TARGET): $(OBJECTS)
	$(CC) $(CC_FLAGS) -o $@ $^

clean:
	rm -f *.o *~ $(TARGET)
 
