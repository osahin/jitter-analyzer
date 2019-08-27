r#include "../lib/csv_reader.h"
#include <TString.h>
#include <TObjString.h>
#include <cmath>
#include <TList.h>
#include <TObject.h>
#include <TObjArray.h>
#include <TCollection.h>
/* Simple reader to read csv files*/
bool csv_reader::read( const std::string & fileName, source_jitter & sj, TString sampleTitle, bool readoutTDC){
  std::cout << fileName << std::endl;
  static const int sizeJitterCont = 2; /* noise vs freq values */
  static const int sizeTDCCont = 14;  /* output of AMS GPX2 TDC sw */ 
  std::fstream csv_file(fileName);
  if(!csv_file){
    std::cout <<  "Error. No file named: \" "+ fileName + "\" exists" << std::endl;
    throw 1; //throw expression arbitrary int
    return false;
  }
    std::vector<double> jitterValues( sizeJitterCont, 0);
    std::vector<double> TDCValues   ( sizeTDCCont, 0);
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
	  if (items == 1){ // sanitize the input by replacing the delimeters with space
	    line=((TString)line).ReplaceAll(";"," ").Data();
	    line=((TString)line).ReplaceAll(","," ").Data();
	    list = ((TString)line).Tokenize(" ");
	    items = list->GetEntries();
	  }
        }
	if ('N' == line[0]){
	  std::cout << line << std::endl;
	  sj.fileName = fileName;
	  sj.sampleTitle = sampleTitle;
	  return true;
	}
	
        if(sizeJitterCont == items){
	  TIter next(list);//unfortunately TString can not be stored (or can not be converted to TObject) as TObject so TObjString it is...	  
	  for (int i = 0; i < items ; i++){
	    (value) =(& ((TObjString*)next())->String()); 
	    jitterValues.at(i) = (value->ReplaceAll(",","")).Atof();
	  }
	  std::cout << jitterValues.at(0) << std::endl;
	  std::cout << jitterValues.at(1) << std::endl;

	  sj.valJitter.push_back(jitterValues);
        } else if (sizeTDCCont == items && true == readoutTDC){
	  TIter next(list);//unfortunately TString can not be stored (or can not be converted to TObject) as TObject so TObjString it is...	  
	  for (int i = 0; i < items ; i++){
	    (value) =(& ((TObjString*)next())->String()); 
	    TDCValues.at(i) = (value->ReplaceAll(",","")).Atof();
	  }
	  sj.valTDC.push_back(TDCValues);
	}
    }
    sj.fileName = fileName;
    sj.sampleTitle = sampleTitle;
    return true;
}

