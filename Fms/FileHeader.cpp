#include "FileHeader.h"

namespace Fms{
	bool FileHeader::operator==(const FileHeader &f) const{
		if (fileDesc != f.fileDesc || FAT != f.FAT){
			return false;
		}
		return true;
	}

	bool FileHeader::operator!=(const FileHeader &f) const{
		return !operator==(f);
	}
}