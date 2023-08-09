SRC = ./SRC
INC = ./Include
LIB = ./LIB

TARGET = uniPicsteg

OBJS = 	$(LIB)/base64.o \
		$(SRC)/keyShaping.o \
		$(SRC)/encoding.o \
		$(SRC)/fractal.o \
		$(SRC)/encrypt.o \
		$(SRC)/interface.o \
		$(SRC)/fileSystem.o \
		$(SRC)/random.o \
		$(SRC)/picture.o \
		$(SRC)/noiseGen.o \
		$(SRC)/processing.o \
		$(SRC)/test.o \
		$(SRC)/main.o

CXX = g++

#Compiler flags
DBFLAGS = -O3
WFLAGS = -Wall -std=c++17 -g #Wall flag 

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
