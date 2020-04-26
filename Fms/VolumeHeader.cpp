#include "VolumeHeader.h"
#include<cstring>

namespace Fms{

	VolumeHeader::VolumeHeader(){
		sectorNr = 0;
		memset(diskName, '\0', sizeof(diskName));
		memset(diskOwner, '\0', sizeof(diskOwner));
		memset(prodDate, '\0', sizeof(prodDate));
		clusQty = 0;
		dataClusQty = 0;
		addrDat = 0;
		addrRootDir = 0;
		addrDatCpy = 0;
		addrRootDirCpy = 0;
		addrDataStart = 0;
		memset(formatDate, '\0', sizeof(formatDate));
		isFormated = false;
	}

}