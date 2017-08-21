#include "../lib/csv_reader.h"
#include <cmath>
/* Simple reader to read csv files*/
bool csv_reader::read( const std::string & fileName, source_jitter & sj, const std::string & sampleTitle){
  std::fstream csv_file(fileName);
  if(!csv_file) return false;
  std::vector<double> csv_line(2,0);
  while(csv_file >> csv_line.at(0) && csv_file >> csv_line.at(1) ){
    sj.jitter.push_back(csv_line); 
  }
  sj.fileName = fileName;
  sj.sampleTitle = sampleTitle;
  return true;
}

