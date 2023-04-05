SRC = ./src/c
INC = ./include

TARGET = uniPicsteg

OBJS = $(SRC)/processing.o \
	   $(SRC)/main.o

CXX = g++

#Compiler flags
DBFLAGS = -O3
WFLAGS = -Wall -std=c++17 #Wall flag 

#OpenCV Flags
CVFLAGS = `pkg-config --cflags opencv4`
LCVFLAGS = `pkg-config --libs opencv4`

#Include & local libs flags
IFLAGS = -I${INC}
LFLAGS = -lstdc++ -fopenmp

#Compiling flags
CXXFLAGS = ${DBFLAGS} ${WFLAGS} ${IFLAGS} ${CVFLAGS} ${LFLAGS}
LDFLAGS = $(LCVFLAGS)

all: $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)

.SUFFIXES: .o .c .cpp .cxx .cc
.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) $<
.c.o:
	$(CXX) -c $(CXXFLAGS) $<
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
