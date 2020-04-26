#include "Dms.h"
using namespace std;

namespace Fms{
	Dms::Dms(size_t fcbArrSize):fcbArrSize(fcbArrSize){
		if (fcbArrSize < 1){
			throw invalid_argument("Dms: Dms: Array size is too little");
		}
		fcbArray = new Fcb[fcbArrSize];
	}

	Dms::~Dms(){
		delete [] fcbArray;
		fcbArray = NULL;
	}

	Fcb* Dms::lookForFcb(Disk* d, const std::string &fName){
		if (d == NULL){
			throw invalid_argument("Dms: lookForFcb: Invalid Disk pointer");
		}
		Fcb *fcb;
		for (size_t i=fcbArrSize-1;i>=0;--i){
			if (fcbArray[i].d == NULL){
				fcb = &fcbArray[i];
			} else if ((fcbArray[i].d == d) && (fName == string(fcbArray[i].fileDesc.fileName))){
				throw runtime_error("Dms: lookForFcb: File is already open");
			}
		}
		return fcb;
	}

	Fcb* Dms::openFile(Disk* d, const std::string &fileName, const std::string &userName, const std::string &mode){
		if (d == NULL){
			throw invalid_argument("Dms: lookForFcb: Invalid Disk pointer");
		}
		Fcb *f = lookForFcb(d, fileName);
		if (f == NULL){
			throw runtime_error("Dms: openFile: Can't find free Fcb");
		}
		*f = *(d->openFile(fileName, userName, mode));
		return f;
	}

}