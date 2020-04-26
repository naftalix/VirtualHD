#include "Dat.h"

namespace Fms{

	Dat::Dat(){
		sectorNr = 1;
		for (ClusterId i=0; i<CLUSTERSINDISK; ++i){
			dat[i]=1;
		}
		memset(emptyArea, '\0', sizeof(emptyArea));
	}

	std::ostream& operator<< (std::ostream& out, const Dat& dat){
		//out << "The current 'DAT' map is:\n" << dat.dat << std::endl; 
		out << "Current free space is: " << double(dat.dat.count()) / dat.dat.size() * 100 << "%\n (" << dat.dat.count() << " Clusters)\n";
		return out;
	}
}