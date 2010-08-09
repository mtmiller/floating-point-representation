TEST_PROGRAMS = floating_point_representation_test

default: all

all: $(TEST_PROGRAMS)

clean:
	-rm -f *.o $(TEST_PROGRAMS)

.PHONY: default all clean
