CC = g++
LDFLAGS = -std=c++11
CFLAGS = -g -Wall

all:tseytinTransform

tseytinTransform:fileOperationsUtil.o tseytinTransform.o tseytinUtil.o
	$(CC) $(CFLAGS) -o tseytinTransform fileOperationsUtil.o tseytinTransform.o tseytinUtil.o

fileOperationsUtil.o:fileOperationsUtil.cpp
	$(CC) $(CFLAGS) -c fileOperationsUtil.cpp $(LDFLAGS)

tseytinUtil.o:tseytinUtil.cpp fileOperationsUtil.h
	$(CC) $(CFLAGS) -c tseytinUtil.cpp $(LDFLAGS)

tseytinTransform.o:tseytinTransform.cpp tseytinUtil.h
	$(CC) $(CFLAGS) -c tseytinTransform.cpp $(LDFLAGS)

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	$(RM) count *.o *~
