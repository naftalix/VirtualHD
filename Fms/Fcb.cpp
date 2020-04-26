#include "Fcb.h"
#include "Disk.h"
using namespace std;

namespace Fms{
	void Fcb::init(){
		d = NULL;
		fileDesc = Dir::DirEntry();
		fat.reset();
		currRecNumber = 0;
		currSecNr = 1;
		currRecNrInBuff = 0;
		OpenMode mode = OpenMode::IO; // Default
		lock = false;
		loaded = false;
	}

	Fcb::Fcb(){
		init();
	}

	Fcb::Fcb(Disk* disk){
		init();
		d = disk;
	}

	Fcb::~Fcb(){
		try{
			updateCancel();
		} catch (...){ }
		try{
			closeFile();
		} catch (...){ }
	}

	void Fcb::seek(uint32_t mode, int32_t amount){
		if (lock){
			throw runtime_error("Fcb: seek: Can't seek while file is locked");
		}
		bool flushed = false;
		if (fileDesc.recFormat[0] == 'F'){
			switch (mode){
			case 0: // From start of file
				{
					if (amount < 0){
						throw invalid_argument("Fcb: seek: Can't jump before the first record");
					}
					if (static_cast<RecordId>(amount) > fileDesc.eofRecNr){
						throw invalid_argument("Fcb: seek: Can't jump past EOF");
					}
					SectorId targetSector = (amount / ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize)) + 1;
					if (targetSector != currSecNr){
						flushFile();
						flushed = true;
					}
					currRecNumber = amount;
					currSecNr = targetSector;
					currRecNrInBuff = (amount % ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize));
				}
				break;
			case 1: // From current record
				{
					RecordId targetRecord = currRecNumber + amount;
					if (((amount < 0) && (targetRecord > currRecNumber)) || ((amount > 0) && (targetRecord < currRecNumber)) || (targetRecord > fileDesc.eofRecNr)){
						throw invalid_argument("Fcb: seek: Amount result in overflow");
					}

					SectorId targetSector = targetRecord / ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize) + 1;
					if (targetSector != currSecNr){
						flushFile();
						flushed = true;
					}
					currRecNumber = targetRecord;
					currSecNr = targetSector;
					currRecNrInBuff = targetRecord % ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize);
				}
				break;
			case 2: // From end of file
				{
					if (amount > 0){
						throw invalid_argument("Fcb: seek: Can't jump after the last record");
					}
					int32_t tmp = 0 - amount;
					if (static_cast<RecordId>(tmp) > fileDesc.eofRecNr){
						throw invalid_argument("Fcb: seek: Can't go farther than start of file");
					}
					RecordId targetRecord = fileDesc.eofRecNr + amount;
					SectorId targetSector = targetRecord / ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize) + 1;
					if (targetSector != currSecNr){
						flushFile();
						flushed = true;
					}
					currRecNumber = targetRecord;
					currSecNr = targetSector;
					currRecNrInBuff = targetRecord % ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize);
				}
				break;
			default:
				throw invalid_argument("Fcb: seek: Invalid seek mode");
			}
			if (flushed || !loaded){
				d->readSector(getRealSectorNumber(), &buffer);
				loaded = true;
			}
		} else if (fileDesc.recFormat[0] == 'V') {
			throw runtime_error("Fcb: seek: Not implemented for varried length");
		} else {
			throw runtime_error("Fcb: seek: Invalid file type");
		}
	}

	void Fcb::closeFile(){
		if (d == NULL){
			return;
		}
		if (lock){
			throw runtime_error("Fcb: closeFile: Can't close a locked file");
		}
		if (mode != OpenMode::I){
			flushFile();
			FileHeader tmp;
			d->readSector(fileDesc.fileAddr, reinterpret_cast<Sector*>(&tmp));
			if (tmp.fileDesc != fileDesc){
				tmp.fileDesc = fileDesc;
				d->writeSector(fileDesc.fileAddr, reinterpret_cast<Sector*>(&tmp));
			}
		}
		init();
	}

	void Fcb::flushFile(){
		if (lock){
			throw runtime_error("Fcb: flushFile: Can't flush while file is locked");
		}
		if (mode == OpenMode::I){
			return; // Nothing to do
		}
		Sector tmp;
		SectorId sectorId = getRealSectorNumber();
		d->readSector(sectorId, &tmp);
		if (tmp != buffer){
			d->writeSector(sectorId, &buffer);
		}
	}

	SectorId Fcb::getRealSectorNumber() const{
		Disk::FatReader fatReader(fat, fileDesc.fileAddr / CLUSTERSIZE);
		for (size_t i=0; i<(currSecNr/CLUSTERSIZE); ++i){
			++fatReader;
		}
		return (*fatReader * CLUSTERSIZE) + (currSecNr % CLUSTERSIZE);
	}

	//void Fcb::read(char *dst, uint32_t mode){
	//	memcpy(dst, read(mode).get(), fileDesc.actualRecSize);
	//}

	std::unique_ptr<char[]> Fcb::read(uint32_t mode){
		if (fileDesc.recFormat[0] != 'F') throw runtime_error("Fcb: read: Non Fixed length records are not supported as per instructions");
		if (lock){
			throw runtime_error("Fcb: read: Can't read while file is locked");
		}
		if (this->mode == OpenMode::O){
			throw runtime_error("Fcb: read: Can't read write-only file");
		}
		if ((this->mode == OpenMode::I) && (mode == 1)){
			throw runtime_error("Fcb: read: Can't open read only file for updating");
		}
		if (mode > 1){
			throw invalid_argument("Fcb: read: Invalid reading mode");
		}
		if (currRecNumber == fileDesc.eofRecNr){
			throw runtime_error("Fcb: read: Can't read EOF");
		}
		unique_ptr<char[]> record(new char[fileDesc.actualRecSize]);
		memcpy(record.get(),reinterpret_cast<char*>(&buffer)+fileDesc.actualRecSize*currRecNrInBuff+sizeof(SectorId),fileDesc.actualRecSize);

		if (mode == 0){
			moveToNextRecord();
		} else {
			lock = true;
		}

		return record;
	}

	void Fcb::write(char *src){
		if (fileDesc.recFormat[0] != 'F') throw runtime_error("Fcb: write: Non Fixed length records are not supported as per instructions");
		if (lock){
			throw runtime_error("Fcb: write: Can't write while file is locked");
		}
		if (mode == OpenMode::I){
			throw runtime_error("Fcb: write: Can't write to read only file");
		}
		if (fat.count() * CLUSTERSIZE == currSecNr){
			//throw out_of_range("Fcb: write: Can't write. End of physical file");
			// Try to extend file
			d->extendFile(fileDesc.fileName, fileDesc.fileOwner, 1);
			size_t loc;
			RecordId eof = fileDesc.eofRecNr;
			FileHeader header = d->findFile(fileDesc.fileName, loc);
			fileDesc = header.fileDesc;
			fileDesc.eofRecNr = eof;
			fat = header.FAT;
			seek(2,0); // Move to the new logical EOF
		}
		memcpy(reinterpret_cast<char*>(&buffer)+fileDesc.actualRecSize*currRecNrInBuff+sizeof(SectorId), src, fileDesc.actualRecSize);
		if (currRecNumber == fileDesc.eofRecNr){
			++fileDesc.eofRecNr; // Yet another record
		}
		moveToNextRecord();
	}

	void Fcb::moveToNextRecord(){
		if (fat.count() * CLUSTERSIZE == currSecNr){
			throw out_of_range("Fcb: moveToNextRecord: Can't move past physical EOF");
		}
		if (fileDesc.eofRecNr == currRecNumber){
			throw out_of_range("Fcb: moveToNextRecord: can't move past EOF");
		}
		if (currRecNrInBuff+1 == ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize)){
			flushFile();
			currSecNr+=1;
			d->readSector(getRealSectorNumber(), &buffer);
		}
		currRecNrInBuff = (currRecNrInBuff+1) % ((sizeof(Sector) - sizeof(SectorId)) / fileDesc.actualRecSize);
		currRecNumber+=1;
	}

	void Fcb::updateCancel(){
		if (fileDesc.recFormat[0] != 'F') throw runtime_error("Fcb: updateCancel: Non Fixed length records are not supported as per instructions");
		if (this->mode != OpenMode::IO){
			throw runtime_error("Fcb: updateCancel: Can't unlock write/read only file");
			// This isn't needed, as it'll never get locked. But just to follow the instructions.
		}
		if (!lock){
			throw runtime_error("Fcb: updateCancel: The record isn't locked");
		}
		lock = false;
	}

	void Fcb::delRecord(){
		if (fileDesc.recFormat[0] != 'F') throw runtime_error("Fcb: delRecord: Non Fixed length records are not supported as per instructions");
		if (this->mode != OpenMode::IO){
			throw runtime_error("Fcb: delRecord: Can't delete write/read only file");
			// This isn't needed, as it'll never get locked. But just to follow the instructions.
		}
		if (!lock){
			throw runtime_error("Fcb: delRecord: The record isn't locked");
		}

		unique_ptr<char[]> del(new char[fileDesc.keySize]);
		switch (fileDesc.keyType[0]){
		case 'I':
			switch (fileDesc.keySize){
			case 1:
				{
					int8_t x = -1;
					memcpy(del.get(),reinterpret_cast<char*>(&x),fileDesc.keySize);
				}
				break;
			case 2:
				{
					int16_t x = -1;
					memcpy(del.get(),reinterpret_cast<char*>(&x),fileDesc.keySize);
				}
				break;
			case 4:
			case 0:
				{
					int32_t x = -1;
					memcpy(del.get(),reinterpret_cast<char*>(&x),fileDesc.keySize);
				}
				break;
			case 8:
				{
					int64_t x = -1;
					memcpy(del.get(),reinterpret_cast<char*>(&x),fileDesc.keySize);
				}
				break;
			default:
				throw runtime_error("Fcb: delRecord: Key size isn't supported");
				break;
			}
			break;
		case 'F':
			{
				if (fileDesc.keySize != sizeof(float)){
					throw runtime_error("Fcb: delRecord: Key size isn't supported");
				}
				float x = -1;
				memcpy(del.get(),reinterpret_cast<char*>(&x),fileDesc.keySize);
			}
			break;
		case 'D':
			{
				if (fileDesc.keySize != sizeof(double)){
					throw runtime_error("Fcb: delRecord: Key size isn't supported");
				}
				double x = -1;
				memcpy(del.get(),reinterpret_cast<char*>(&x),fileDesc.keySize);
			}
			break;
		case 'C':
			for (size_t i = 0; i < fileDesc.keySize; ++i){
				del[i] = '\0';
			}
			break;
		default:
			throw runtime_error("Fcb: delRecord: Unsupported recored key type");
		}
		memcpy(reinterpret_cast<char*>(&buffer)+fileDesc.actualRecSize*currRecNrInBuff + fileDesc.keyOffset + sizeof(SectorId), del.get(), fileDesc.keySize);

		lock = false;
		moveToNextRecord();
	}

	void Fcb::update(char* rec){
		if (fileDesc.recFormat[0] != 'F') throw runtime_error("Fcb: update: Non Fixed length records are not supported as per instructions");
		if (this->mode != OpenMode::IO){
			throw runtime_error("Fcb: update: Can't update write/read only file");
			// This isn't needed, as it'll never get locked. But just to follow the instructions.
		}
		if (!lock){
			throw runtime_error("Fcb: update: The record isn't locked");
		}

		lock = false;
		write(rec);
	}

	bool Fcb::eof(){
		return currRecNumber == fileDesc.eofRecNr;
	}

}
