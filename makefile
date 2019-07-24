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

ROOT_LIBS = `root-config --libs` -lGenVector -lMathMore -lMinuit
ifeq ($(OMP_ENABLE),1)
	CXX_FLAGS =  -O3 -fPIC -fopenmp `root-config --cflags`
else
	CXX_FLAGS =  -O3 -fPIC `root-config --cflags`
endif


ifeq ("$(OS)","Darwin")
	CXX_FLAGS += -std=c++14
	INCS = -I/usr/include -I${ROOTSYS}/include -I$(JITTER_LIB) -lz -lCore
else
	CXX_FLAGS += -std=c++1y
	INCS = -I/usr/include -I${ROOTSYS}/include -I$(JITTER_LIB) -L/usr/lib64 -lz -lCore		
endif


all: spect_jitter gen_clock analyze_tdc
spect_jitter:$(JITTER_DIR)/spect_jitter.cc csv.o jitter.o 
	@echo "Compiling $@..." 	
	$(CXX) $(CXX_FLAGS) $(JITTER_DIR)/spect_jitter.cc csv.o jitter.o $(INCS) $(ROOT_LIBS) -o spect_jitter -lm 
	@echo "Done." 		
gen_clock:$(JITTER_DIR)/generate_clock.cc $(JITTER_LIB)/clock_gen.h $(JITTER_SRC)/clock_gen.cc
	@echo "Compiling $@..." 	
	$(CXX) $(CXX_FLAGS) $(JITTER_DIR)/generate_clock.cc $(JITTER_SRC)/clock_gen.cc $(INCS) $(ROOT_LIBS) -o gen_clock -lm 
	@echo "Done." 		 
analyze_tdc:$(JITTER_DIR)/analyze_tdc.cc tdc.o csv.o
	@echo "Compiling $@..." 	
	$(CXX) $(CXX_FLAGS) $(JITTER_DIR)/analyze_tdc.cc tdc.o csv.o $(INCS) $(ROOT_LIBS) -o analyze_tdc -lm 
	@echo "Done." 		 
jitter.o:$(JITTER_SRC)/jitter_analyzer.cc $(JITTER_LIB)/jitter_analyzer.h
	$(CXX) $(CXX_FLAGS) -o jitter.o -c  $(JITTER_SRC)/jitter_analyzer.cc
csv.o:$(JITTER_SRC)/csv_reader.cc $(JITTER_LIB)/csv_reader.h
	$(CXX) $(CXX_FLAGS) -o csv.o -c  $(JITTER_SRC)/csv_reader.cc
tdc.o:$(JITTER_SRC)/tdc_analyzer.cc $(JITTER_LIB)/tdc_analyzer.h
	$(CXX) $(CXX_FLAGS) -o tdc.o -c  $(JITTER_SRC)/tdc_analyzer.cc
clean:
	rm -f *~ spect_jitter gen_clock analyzer_csv *.o ?