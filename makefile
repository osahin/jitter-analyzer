CXX ?= g++
CC = icpc
OS = $(shell uname)

export OMP_ENABLE:=0


JITTER_DIR = ./
JITTER_SRC = ./src/
JITTER_LIB = ./lib/


ifndef ROOTSYS
$(error ROOTSYS is not defined!)
endif

ROOT_LIBS = `root-config --libs` -lGenVector -lMathMore -lMinuit2
ifeq ($(OMP_ENABLE),1)
	CXX_FLAGS =  -O3 -fPIC -fopenmp `root-config --cflags`
else
	CXX_FLAGS =  -O3 -fPIC `root-config --cflags`
endif


ifeq ("$(OS)","Darwin")
	CXX_FLAGS += -std=c++14
	INCS = -I/usr/include -I${ROOTSYS}/include -I$(JITTER_LIB) -lz -lCore
else
	CXX_FLAGS += -std=c++0x
	INCS = -I/usr/include -I${ROOTSYS}/include -I$(JITTER_LIB) -L/usr/lib64 -lz -lCore		
endif


all: spect_jitter
spect_jitter:$(JITTER_DIR)/spect_jitter.cc $(JITTER_SRC)/csv_reader.cc jitter.o 
	@echo "Compiling $@..." 	
	$(CXX) $(CXX_FLAGS) $(JITTER_DIR)/spect_jitter.cc $(JITTER_SRC)/csv_reader.cc jitter.o $(INCS) $(ROOT_LIBS) -o spect_jitter -lm 
	@echo "Done." 		
jitter.o:$(JITTER_SRC)/jitter_analyzer.cc $(JITTER_LIB)/jitter_analyzer.h
	$(CXX) $(CXX_FLAGS) -o jitter.o -c  $(JITTER_SRC)/jitter_analyzer.cc
clean:
	rm -f *~ spect_jitter jitter.o