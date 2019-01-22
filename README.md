# jitter-analyzer
A simple jitter analyzer to handle raw data from the csv files and generate a clock with desired RJ and DJ.
For the phase noise analysis a spectrum analyzer output is necessary.
  An example usage of the libraries is given at 'spect_jitter.cc'.
  The output is written in the corresponding root file.
For the clock generation, "generate_clock.cc" should be modified with with the desired RJ and DJ values (in PS). 
  The dual-Dirac model is employed for the simulation of the jitter clock. 
  The histogram is stored in the root file, an overlay waveform of the first few hundred cycles (for a given # of cycle window) is printed on the PDF file, and the generated half-period information are available in the txt file.
  
  After installing ROOT analysis framework simply type 'make' then:
  
  ./spect_jitter
  
  ./gen_clock
  
**Important**
  
  The library requires ROOT6 (mainly for the plotting functionality).
