#ifndef csv_reader_h
#define csv_reader_h
#include "jitter_analyzer.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class csv_reader{
 public:
  bool read( const std::string & fileName, source_jitter & sj, const std::string & sampleTitle);
  csv_reader(){};
};
#endif
