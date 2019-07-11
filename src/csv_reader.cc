#include "../lib/csv_reader.h"
#include <TString.h>
#include <TObjString.h>
#include <cmath>
#include <TList.h>
#include <TObject.h>
#include <TObjArray.h>
#include <TCollection.h>
/* Simple reader to read csv files*/
bool csv_reader::read( const std::string & fileName, source_jitter & sj, TString sampleTitle){
  std::cout << fileName << std::endl;
  std::fstream csv_file(fileName);
  //error mesage in case of mis-named file
  if(!csv_file){
  std::cout <<  "Error. No such  file at "<<fileName<< " exists" << std::endl;
    throw 1; //throw expression
 return false;

  }
   std::vector<double> jitterValues(2,0);
    std::string line;
    TObjArray* list;
    TString * value = new TString;
    int items = 0;    
    std::cout << sampleTitle << std::endl;
    while(getline(csv_file,line)) {
        items = 0;
	
        if('#' != line[0]){ //lines starting with "#" reserved for the comments
	  list = ((TString)line).Tokenize(" ");
	  items = list->GetEntries();
        }
	if ('N' == line[0]){
	  std::cout << line << std::endl;
	  sj.fileName = fileName;
	  sj.sampleTitle = sampleTitle;
	  return true;
	}
	
        if(items==2){
	  TIter next(list);//unfortunately TString can not be stored (or can not be converted to TObject) as TObject so TObjString it is...	  
	  for (int i = 0; i < items ; i++){
	    (value) =(& ((TObjString*)next())->String()); 
	    jitterValues.at(i) = (value->ReplaceAll(",","")).Atof();
	  }
	 
	  std::cout << jitterValues.at(0) << std::endl;
	  std::cout << jitterValues.at(1) << std::endl;

	  sj.jitter.push_back(jitterValues);
        }
    }
    sj.fileName = fileName;
    sj.sampleTitle = sampleTitle;
      
  return true;
}

