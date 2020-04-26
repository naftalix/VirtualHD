#include "Disk.h"
#include "Fcb.h"
#include<ctime>
#include<map>
#include<list>
using namespace std;
#pragma warning(disable: 4996)

namespace Fms{

	Disk::Disk(){
		init();
	} 

	Disk::Disk(std::string &diskName, std::string &ownerName, char code){
		init();
		if (diskName == ""){
			throw invalid_argument("Invalid arguement for create Disk (Disk name)");
		}
		if (ownerName == ""){
			throw invalid_argument("Invalid arguement for create Disk (Owner name)");
		}

		// 'c' - Create
		if (code == 'c'){
			createDisk(diskName, ownerName);
		}
		// 'm' - Mount
		if ((code == 'c') || (code == 'm')){
			fileName = diskName;
			mountDisk(diskName);
			if (string(vhd.diskOwner) != ownerName){
				unmountDisk();
				throw runtime_error("Disk owner mismatch. Access denied");
			}
		} else {
			throw invalid_argument("Invalid arguement for create Disk (Mode)");
		}
	}

	Disk::~Disk(){
		if (mounted){
			unmountDisk();
		}
	}

	void Disk::createDisk(string &diskName, string &ownerName){
		// Sanity check
		fileName = diskName;
		ifstream iFile(diskName);
		if (iFile) {
			throw ios::failure("Disk: createDisk: Disk already exist");
		}
		if (mounted){
			throw runtime_error("Disk: createDisk: Can't create disk while mounted");
		}

		// Create temp data for recreate to work with
		dskfl.open(diskName, ios::out | ios::binary);
		if (!dskfl){
			throw ios::failure("Disk: Failed to create disk");
		}
		dskfl << "Temp data";
		dskfl.close();

		// Fill correct data into image
		strncpy(vhd.diskOwner, ownerName.c_str(), sizeof(vhd.diskOwner)-1);
		recreateDisk(ownerName);
	}

	void Disk::recreateDisk(string &ownerName){
		// Sanity check
		if (fileName == ""){
			throw invalid_argument("Disk: recreateDisk: Invalid file name");
		}
		if (mounted){
			throw runtime_error("Disk: recreateDisk: Can't recreate disk while mounted");
		}

		verifyFile(fileName);

		// Check it's the owner that formats
		if (strncmp(ownerName.c_str(), vhd.diskOwner, sizeof(vhd.diskOwner)) != 0){
			throw invalid_argument("Disk: Can't recreate disk. Owner name mismatch");
		}

		// Reset values
		dat = Dat();
		vhd = VolumeHeader();
		rootDir = Dir();

		// Write empty sectors
		dskfl.open(fileName, ios::out | ios::in | ios::binary);
		mounted = true;
		for (SectorId i=0;i<CLUSTERSINDISK*CLUSTERSIZE;++i){
			Sector sector;
			sector.sectorNr = i;
			writeSector(i, &sector);
		}

		// Set correct tags
		vhd.sectorNr = 0;
		strncpy(vhd.diskName, removePath(fileName).c_str(), sizeof(vhd.diskName)-1);
		strncpy(vhd.diskOwner, ownerName.c_str(), sizeof(vhd.diskOwner)-1);
		strncpy(vhd.prodDate, getDate().c_str(), sizeof(vhd.prodDate)-1);
		vhd.clusQty = CLUSTERSINDISK;
		vhd.dataClusQty = CLUSTERSINDISK - CLUSTERSRESERVED;
		vhd.addrDat = 1;
		vhd.addrRootDir = 1; // Folders take clusters
		vhd.addrDatCpy = CLUSTERSIZE*2+1;
		vhd.addrRootDirCpy = 3;
		vhd.addrDataStart = 4;
		strncpy(vhd.formatDate, "01011970", sizeof(vhd.formatDate)-1); // Before 1970-01-01 there was nothing! (Maybe not)
		vhd.isFormated = false;

		unmountDisk();
	}

	void Disk::mountDisk(string &fname){
		if (mounted){
			throw invalid_argument("Disk: Can't mount a disk, while a disk is mounted");
		}
		verifyFile(fname);
		dskfl.open(fname, ios::in | ios::out | ios::binary);
		if (!dskfl){
			throw ios_base::failure("Disk: Can't mount disk.");
		}
		mounted = true;
		fileName = fname;

		// Load system sectors from virtual image to runtime object
		readSector(0, reinterpret_cast<Sector*> (&vhd));
		readSector(vhd.addrDat, reinterpret_cast<Sector*> (&dat));
		rootDir = Dir(readSectors(CLUSTERSIZE, vhd.addrRootDir*CLUSTERSIZE));
		seekToSector(CLUSTERSIZE*4);
	}

	void Disk::unmountDisk(){
		// Verify it's mounted
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: Disk isn't open, can't unmount.");
		}

		// Compare parts and save if differ
		Sector oldVhd;
		Sector oldDat;

		readSector(0, reinterpret_cast<Sector*> (&oldVhd));
		if (memcmp(&oldVhd, &vhd, sizeof(Sector)) != 0){
			writeSector(0, reinterpret_cast<Sector *> (&vhd));
		}

		readSector(vhd.addrDat, reinterpret_cast<Sector*> (&oldDat));
		if (memcmp(&oldDat, &dat, sizeof(Sector)) != 0){
			writeSector(vhd.addrDat, reinterpret_cast<Sector *> (&dat));
		}

		readSector(vhd.addrDatCpy, reinterpret_cast<Sector*> (&oldDat));
		if (memcmp(&oldDat, &dat, sizeof(Sector)) != 0){
			writeSector(vhd.addrDatCpy, reinterpret_cast<Sector *> (&dat));
		}

		vector<Sector> oldDirs(readSectors(CLUSTERSIZE, vhd.addrRootDir*CLUSTERSIZE));
		vector<Sector> newDirs(rootDir.sectorOutputAsVector());
		if (oldDirs != newDirs){
			writeSectors(newDirs, vhd.addrRootDir*CLUSTERSIZE);
		}

		vector<Sector> oldDirsCpy(readSectors(CLUSTERSIZE, vhd.addrRootDirCpy*CLUSTERSIZE));
		if (!(oldDirsCpy == newDirs)){
			writeSectors(newDirs, vhd.addrRootDirCpy*CLUSTERSIZE);
		}

		// Unmount
		dskfl.close();
		mounted = false;
	}

	void Disk::readSector(SectorId target, Sector* sector){
		seekToSector(target);
		readSector(sector);
	}

	void Disk::readSector(Sector* sector){
		if (currDiskSectorNr >= CLUSTERSINDISK*CLUSTERSIZE){
			throw out_of_range("Disk: current sector is out of range");
		}
		moveReadingHead();
		dskfl.read(reinterpret_cast<char*> (sector), sizeof(Sector));
		++currDiskSectorNr;
	}

	vector<Sector> Disk::readSectors(SectorId amount){
		vector<Sector> sectors;
		for (SectorId i=0;i<amount;++i){
			Sector sector;
			readSector(&sector);
			sectors.push_back(sector);
		}
		return sectors;
	}

	vector<Sector> Disk::readSectors(SectorId amount, SectorId location){
		seekToSector(location);
		return readSectors(amount);
	}

	void Disk::writeSector(SectorId target, Sector* sector){
		seekToSector(target);
		writeSector(sector);
	}

	void Disk::writeSector(Sector* sector){
		if (currDiskSectorNr >= CLUSTERSINDISK*CLUSTERSIZE){
			throw out_of_range("Disk: current sector is out of range");
		}
		moveWritingHead();
		sector->sectorNr = currDiskSectorNr;
		try{
			dskfl.write(reinterpret_cast<char*> (sector), sizeof(Sector));
		} catch (ios::failure e) {
			throw ios::failure(std::string("Disk: Failed to write data - ") + e.what());
		}
		++currDiskSectorNr;
	}

	void Disk::writeSectors(std::vector<Sector> sectors){
		for (auto sector : sectors){
			writeSector(&sector);
		}
	}

	void Disk::writeSectors(std::vector<Sector> sectors, SectorId location){
		seekToSector(location);
		writeSectors(sectors);
	}

	void Disk::seekToSector(SectorId target){
		if (target >= CLUSTERSINDISK * CLUSTERSIZE){
			throw out_of_range("Disk: seekToSector: out of range");
		}
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: Disk isn't open, can't seek.");
		}
		dskfl.clear();
		currDiskSectorNr = target;
		moveReadingHead();
		moveWritingHead();
	}

	Cluster Disk::readCluster(ClusterId location){
		seekToSector(location * CLUSTERSIZE);
		Cluster cluster;
		for (Sector &sector : cluster){
			readSector(&sector);
		}
		return cluster;
	}

	void Disk::writeCluster(Cluster cluster, ClusterId location){
		seekToSector(location * CLUSTERSIZE);
		for (Sector sector : cluster){
			writeSector(&sector);
		}
	}

	void Disk::moveReadingHead(){
		dskfl.clear();
		dskfl.seekg(currDiskSectorNr * SIZEOFSECTOR, ios::beg);
	}

	void Disk::moveWritingHead(){
		dskfl.clear();
		dskfl.seekp(currDiskSectorNr * SIZEOFSECTOR, ios::beg);
	}

	void Disk::init(){
		mounted = false;
		dskfl.exceptions(ios_base::badbit);
	}

	fstream* Disk::getDskfl(){
		if (dskfl.is_open())
			return &dskfl;
		return NULL;
	}

	void Disk::verifyFile(std::string fileName){
		ifstream iFile(fileName);
		if (!iFile) {
			throw ios::failure("File " + fileName + " doesn't exist");
		}
		iFile.close();
	}

	void Disk::format(std::string ownerName){
		// We only allow the disk to be formatted when it is mounted.
		// It might be true that format is only valid when the disk is not mounted, but we figured it would make the program easier to use
		// if we do it like this.
		if (!mounted){
			throw ios::failure("Disk: format: Can't format disk while NOT mounted");
		}
		if (ownerName != vhd.diskOwner){
			throw invalid_argument("Disk: Can't format. Owner name mismatch");
		}
		for (ClusterId i=0; i < CLUSTERSRESERVED; ++i){
			dat.dat[i] = 0;
		}
		for (ClusterId i=CLUSTERSRESERVED; i < CLUSTERSINDISK; ++i){
			dat.dat[i] = 1;
		}
		for (auto &entry : rootDir){
			entry.entryStatus = 0;
		}
		strncpy(vhd.formatDate, getDate().c_str(), sizeof(vhd.formatDate)-1); // Before 1970-01-01 there was nothing! (Maybe not)
		vhd.isFormated = true;
	}

	ClusterId Disk::howMuchEmpty() const{
		return dat.dat.count();
	}

	void Disk::dealloc(DatType &fat){
		dat.dat |= fat;
		fat.reset();
	}

	void Disk::alloc(DatType &fat, SectorId numSectors, uint32_t mode){
		if (fat.any()){
			throw runtime_error("Disk: alloc: FAT isn't empty");
		}
		allocExtend(fat, numSectors, mode);
	}

	void Disk::allocExtend(DatType &fat, SectorId numSectors, uint32_t mode){

		if (numSectors <= 0) {
			throw invalid_argument("Disk: allocExtend: invalid amount to allocate");
		}
		if (mode > 2){
			throw invalid_argument("Disk: allocExtend: invalid fit type");
		}

		// Check for free space
		ClusterId numClusters = numSectors / CLUSTERSIZE + (numSectors % CLUSTERSIZE ? 1 : 0);
		if (howMuchEmpty() < numClusters) {
			throw runtime_error("Disk: allocExtend: Can't allocate amount of clusters. Not enough space");
		}

		// Find place in HDD
		DatType extraFat;

		try{
			if (mode == 0) { // First fit
				extraFat = firstFit(numClusters);
			} else if (mode == 1) { // Best fit
				extraFat = bestFit(numClusters);
			} else if (mode == 2) { // Worst fit
				extraFat = worstFit(numClusters);
			} else {
				throw invalid_argument("Disk: allocExtend: invalid fit type");
			}
		} catch (exception e) {
			extraFat = fillFit(numClusters);
		}

		// Update FAT
		fat |= extraFat;

		// Update DAT
		dat.dat &= ~fat;
	}

	DatType Disk::firstFit(ClusterId numClusters) const{
		DatType fat;
		fat.reset();
		ClusterId freeAreaSize = 0;
		ClusterId freeAreaLocation = 0;
		for (ClusterId i = 0; i < CLUSTERSINDISK; ++i){
			if (!dat.dat.test(i)){
				freeAreaLocation = (i + 1);
				freeAreaSize = 0;
			} else {
				++freeAreaSize;
				if (freeAreaSize == numClusters){
					for (ClusterId j=0;j<numClusters;++j){
						fat[freeAreaLocation+j] = 1;
					}
					return fat;
				}
			}
		}
		throw runtime_error("Disk: firstFit: Can't find enough free space");
	}

	DatType Disk::bestFit(ClusterId numClusters) const{
		ClusterId freeAreaLocation = 0;
		ClusterId freeAreaLocationCurr = 0;
		ClusterId freeAreaSize = 0;	
		ClusterId freeAreaSizeCurr = 0;
		DatType fat;
		fat.reset();

		for (ClusterId i=0; i<CLUSTERSINDISK; ++i){
			if (!dat.dat.test(i)){
				if (freeAreaSizeCurr != 0){
					// End of free segment. Check if it's smaller than smallest found (yet still big enough)
					if (((freeAreaSize == 0) || (freeAreaSizeCurr < freeAreaSize)) && (freeAreaSizeCurr >= numClusters)){
						// Update smallest found
						freeAreaSize = freeAreaSizeCurr;
						freeAreaLocation = freeAreaLocationCurr;
					}
				}
				// Reset size counter
				freeAreaLocationCurr = i + 1;
				freeAreaSizeCurr = 0;
			} else {
				if (freeAreaSizeCurr == 0) {
					// If it's a start of a free segment, mark the starting point
					freeAreaLocationCurr = i;
				}

				// Increase amount of free clusters
				++freeAreaSizeCurr;
			}
		}

		// Maybe the free space ends in the end of the disk
		if (((freeAreaSize == 0) || (freeAreaSizeCurr < freeAreaSize)) && (freeAreaSizeCurr >= numClusters)){
			// Update smallest found
			freeAreaSize = freeAreaSizeCurr;
			freeAreaLocation = freeAreaLocationCurr;
		}

		// Check if it's enough
		if (freeAreaSize < numClusters){
			throw ios::failure("Disk: bestFit: Can't find enough free space");
		}

		for (ClusterId j=0;j<numClusters;++j){
			fat[freeAreaLocation+j] = 1;
		}
		return fat;
	}

	DatType Disk::worstFit(ClusterId numClusters) const{
		ClusterId freeAreaLocation = 0;
		ClusterId freeAreaLocationCurr = 0;
		ClusterId freeAreaSize = 0;	
		ClusterId freeAreaSizeCurr = 0;
		DatType fat;
		fat.reset();

		for (ClusterId i=0; i<CLUSTERSINDISK; ++i){
			if (!dat.dat.test(i)){
				if (freeAreaSizeCurr != 0){
					// End of free segment. Check if it's bigger than biggest found
					if (freeAreaSizeCurr > freeAreaSize){
						// Update biggest found
						freeAreaSize = freeAreaSizeCurr;
						freeAreaLocation = freeAreaLocationCurr;
					}
				}
				// Reset size counter
				freeAreaLocationCurr = i + 1;
				freeAreaSizeCurr = 0;
			} else {
				if (freeAreaSizeCurr == 0) {
					// If it's a start of a free segment, mark the starting point
					freeAreaLocationCurr = i;
				}

				// Increase amount of free clusters
				++freeAreaSizeCurr;
			}
		}
		// Maybe the free space ends in the end of the disk
		if (freeAreaSizeCurr > freeAreaSize){
			// Update biggest found
			freeAreaSize = freeAreaSizeCurr;
			freeAreaLocation = freeAreaLocationCurr;
		}

		// Check if it's enough
		if (freeAreaSize < numClusters) {
			throw ios::failure("Disk: worstFit: Can't find enough free space");
		}

		for (ClusterId j=0;j<numClusters;++j){
			fat[freeAreaLocation+j] = 1;
		}
		return fat;
	}

	DatType Disk::fillFit(ClusterId numClusters) const{
		if (dat.dat.count() < numClusters){
			throw runtime_error("Disk: fillFit: Can't allocate. Not enough space");
		}

		DatType fat;
		fat.reset();

		while (fat.count() < numClusters){
			ClusterId freeAreaLocation = 0;
			ClusterId freeAreaLocationCurr = 0;
			ClusterId freeAreaSize = 0;	
			ClusterId freeAreaSizeCurr = 0;

			for (ClusterId i=0; i<CLUSTERSINDISK; ++i){
				// If the cluster is marked as taken by the DAT or by the FAT we create:
				if ((!dat.dat.test(i)) || (fat.test(i))){
					if (freeAreaSizeCurr != 0){
						// End of free segment. Check if it's closer to the requested amount (preferebly from above).
						if (((freeAreaSizeCurr > freeAreaSize) && (freeAreaSize < numClusters - fat.count())) ||
							((freeAreaSizeCurr < freeAreaSize) && (freeAreaSizeCurr >= numClusters - fat.count()))){
								// Update prefered location
								freeAreaSize = freeAreaSizeCurr;
								freeAreaLocation = freeAreaLocationCurr;
						}
					}
					// Reset size counter
					freeAreaLocationCurr = i + 1;
					freeAreaSizeCurr = 0;

				} else { // Else it's marked as free space
					if (freeAreaSizeCurr == 0) {
						// If it's a start of a free segment, mark the starting point
						freeAreaLocationCurr = i;
					}

					// Increase amount of free clusters
					++freeAreaSizeCurr;
				}
			}

			// Maybe the free space ends in the end of the disk
			if ((freeAreaSize == 0) ||
				(((freeAreaSizeCurr > freeAreaSize) && (freeAreaSize < numClusters - fat.count())) ||
				((freeAreaSizeCurr < freeAreaSize) && (freeAreaSizeCurr >= numClusters - fat.count())))){
					// Update smallest found
					freeAreaSize = freeAreaSizeCurr;
					freeAreaLocation = freeAreaLocationCurr;
			}

			// Update suggested FAT
			ClusterId wantedSize = (freeAreaSize < numClusters - fat.count() ? freeAreaSize : numClusters - fat.count());
			for (ClusterId j=0;j<wantedSize;++j){
				fat[freeAreaLocation+j] = 1;
			}
		}

		return fat;
	}

	const Dat& Disk::getDat() const{
		if (mounted){
			return dat;
		}
		throw runtime_error("Disk: getDat: Disk not mounted");
	}

	const Dir& Disk::getDir() const{
		if (mounted){
			return rootDir;
		}
		throw runtime_error("Disk: getDir: Disk not mounted");
	}

	const VolumeHeader& Disk::getVolumeHeader() const{
		if (mounted){
			return vhd;
		}
		throw runtime_error("Disk: getVolumeHeaader: Disk not mounted");
	}

	void Disk::createFile(const std::string &fileName, const std::string &ownerName, const std::string &fileType,
		std::size_t recordLength, SectorId numSectors, const std::string &keyType, size_t keyOffset, uint32_t fit, size_t keyLength){
			// These are per the sepcs. We could have done createFile for sub folders, but that is not required.

			// Check if mounted
			if ((!mounted) || (!dskfl.is_open())){
				throw ios_base::failure("Disk: createFile: Disk isn't open, can't create file.");
			}

			// Check if disk is formatted
			if (!vhd.isFormated) {
				throw runtime_error("Disk: createFile: Disk not formatted");
			}

			// Check arguments
			if ((fileType.c_str()[0] != 'F') && (fileType.c_str()[0] != 'V')){
				throw invalid_argument("Disk: createFile: Invalid file type");
			}
			if ((keyType.c_str()[0] != 'I') && (keyType.c_str()[0] != 'F') && (keyType.c_str()[0] != 'D') && (keyType.c_str()[0] != 'C')){
				throw invalid_argument("Disk: createFile: Invalid key type");
			}
			if (recordLength == 0){
				throw invalid_argument("Disk: createFile: Invalid record length");
			}
			if ((keyType.c_str()[0] == 'C') && (keyLength == 0)){
				throw invalid_argument("Disk: createFile: Invalid key length");
			}
			// Check for free space
			if(howMuchEmpty() < (numSectors / CLUSTERSIZE + (numSectors % CLUSTERSIZE ? 1 : 0))){
				throw runtime_error("Disk: createFile: Not enough space in disk");
			}

			// Check for valid fit
			if (fit > 2) {
				throw runtime_error("Disk: createFile: Invalid fit");
			}

			// rootDir is the only folder this supports, but to make it easier to update (for sub folder support), we made a variable for the
			// folder to be used for this
			Dir &targetDir = rootDir;

			// Check if filename doesn't already exist and for free entry in the directory
			for (size_t i=0; i<targetDir.size(); ++i)
				if ((strncmp(targetDir[i].fileName, fileName.c_str(), sizeof(targetDir[i].fileName)) == 0) && targetDir[i].entryStatus == 1)
					throw invalid_argument("Disk: createFile: A file with such name already exist");

			size_t entryPlace = targetDir.size();
			for (size_t i=0; i<targetDir.size(); ++i){
				if ((targetDir[i].entryStatus == 0) || (targetDir[i].entryStatus == 2)){
					entryPlace = i;
					break;
				}
			}
			if (entryPlace == targetDir.size()){
				throw runtime_error("Disk: createFile: The directory is already full");
			}

			FileHeader file;
			if (fileName.length() >= sizeof(file.fileDesc.fileName)){
				throw invalid_argument("Disk: createFile: File name is too big");
			}
			// Create the file
			
			strncpy(file.fileDesc.fileName, fileName.c_str(), sizeof(file.fileDesc.fileName)-1);
			strncpy(file.fileDesc.fileOwner, ownerName.c_str(), sizeof(file.fileDesc.fileOwner)-1);
			strncpy(file.fileDesc.recFormat, fileType.c_str(), sizeof(file.fileDesc.recFormat));
			strncpy(file.fileDesc.crDate, getDate().c_str(), sizeof(file.fileDesc.crDate)-1);	
			if (fileType.c_str()[0] == 'F'){
				file.fileDesc.actualRecSize = file.fileDesc.maxRecSize = recordLength;
			} else {
				file.fileDesc.actualRecSize = file.fileDesc.maxRecSize = recordLength; // V isn't supported
			}
			file.fileDesc.maxRecSize = recordLength;
			file.fileDesc.fileSize = 0; // This is only used for Download / Upload files. So 0 if it's not uploaded.
			strncpy(file.fileDesc.keyType, keyType.c_str(), sizeof(file.fileDesc.keyType));
			file.fileDesc.keyOffset = keyOffset;

			// Optional
			if (keyType.c_str()[0] == 'C'){
				file.fileDesc.keySize = keyLength;
			} else {
				if (keyLength == 0){
					switch (keyType.c_str()[0]){
					case 'I':
						file.fileDesc.keySize = sizeof(int);
						break;
					case 'F':
						file.fileDesc.keySize = sizeof(float);
						break;
					case 'D':
						file.fileDesc.keySize = sizeof(double);
						break;
					}
				} else {
					file.fileDesc.keySize = keyLength;
				}
			}
			file.fileDesc.eofRecNr = 0;
			file.fileDesc.entryStatus = 1;

			// Should we add a sector for the fileHeader? We think we should
			// alloc(file.FAT, numSectors, fit); // This is how it would be if we don't add
			alloc(file.FAT, numSectors + 1, fit); // This is how it would be if we add

			// Find the first sector of the file
			SectorId firstSector;
			for (ClusterId i=0; i<file.FAT.size(); ++i){
				if (file.FAT.test(i)){
					firstSector = i * CLUSTERSIZE;
					break;
				}
			}
			file.fileDesc.fileAddr = firstSector;
			writeSector(firstSector, reinterpret_cast<Sector*> (&file));

			// Update the directory
			targetDir[entryPlace] = file.fileDesc;

	}

	void Disk::delFile(const std::string &fileName, const std::string &ownerName){

		// Check if mounted
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: delFile: Disk isn't open");
		}

		// Check if disk is formatted
		if (!vhd.isFormated) {
			throw runtime_error("Disk: delFile: Disk not formatted");
		}

		Dir &targetDir = rootDir; // See comment in createFile
		size_t entryPlace;

		FileHeader file = findFile(fileName, entryPlace);

		// Check that the owner has set the request
		if (strncmp(file.fileDesc.fileOwner,ownerName.c_str(),sizeof(file.fileDesc.fileOwner)) != 0){
			throw runtime_error("Disk: delFile: Ownername mismatch. Can't delete");
		}

		// Delete the file
		dealloc(file.FAT);
		file.fileDesc.entryStatus = 2;
		targetDir[entryPlace] = file.fileDesc;
		writeSector(file.fileDesc.fileAddr, reinterpret_cast<Sector*> (&file));

	}

	void Disk::extendFile(const std::string &fileName, const std::string &ownerName, SectorId amount, uint32_t fit){
		// Check if mounted
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: extendFile: Disk isn't open");
		}

		// Check if disk is formatted
		if (!vhd.isFormated) {
			throw runtime_error("Disk: extendFile: Disk not formatted");
		}

		// Check for valid fit
		if (fit > 2) {
			throw runtime_error("Disk: extendFile: Invalid fit");
		}

		Dir &targetDir = rootDir; // See comment in createFile
		size_t entryPlace;

		FileHeader file = findFile(fileName, entryPlace);

		// Check that the owner has set the request
		if (strncmp(file.fileDesc.fileOwner,ownerName.c_str(),sizeof(file.fileDesc.fileOwner)) != 0){
			throw runtime_error("Disk: extendFile: Ownername mismatch. Can't extend");
		}

		// Allocate
		DatType oldFat = file.FAT;
		allocExtend(file.FAT, amount, fit);
		updateFileToFat(oldFat, file.FAT, (file.fileDesc.fileAddr / CLUSTERSIZE));
		targetDir[entryPlace] = file.fileDesc;
		writeSector(file.fileDesc.fileAddr, reinterpret_cast<Sector*> (&file));

	}

	FileHeader Disk::findFile(const std::string &fileName ,size_t &ePlace){
		const Dir &targetDir = rootDir;

		// Find the item
		size_t entryPlace = targetDir.size();
		for (size_t i=0; i<targetDir.size(); ++i){
			if ((targetDir[i].entryStatus == 1) && (strncmp(targetDir[i].fileName,fileName.c_str(),sizeof(targetDir[i].fileName)) == 0)){
				entryPlace = i;
				break;
			}
		}

		// Verify the item exist
		if (entryPlace == targetDir.size()){
			throw runtime_error("Disk: findFile: File not found");
		}

		FileHeader file;
		readSector(targetDir[entryPlace].fileAddr, reinterpret_cast<Sector*> (&file));
		ePlace = entryPlace;
		return file;
	}

	void Disk::updateFileToFat(DatType oldFat, DatType newFat, ClusterId start){
		if (oldFat.count() > newFat.count()){
			throw invalid_argument("Disk: UpdateFileToFat: New FAT has less space than old FAT");
		} else if (oldFat.count() == newFat.count()){
			// Nothing to do
			return;
		}

		FatReader oldFatReader(oldFat, start);
		FatReader newFatReader(newFat, start);
		// Move all sectors to the start of the file
		// As we wish to preserve the order of the file
		for (ClusterId i=1; i<oldFat.count(); ++i){
			// Progress pointers to the next marked clusters
			++oldFatReader;
			++newFatReader;

			// No point in copying from the same location to the same location
			if (*oldFatReader != *newFatReader){
				// Copy entire cluster
				writeCluster(readCluster(*oldFatReader), *newFatReader);
			}
		}
	}

	unique_ptr<Fcb> Disk::openFile(const std::string &fileName, const std::string &userName, const std::string &mode){
		// Check if mounted
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: openFile: Disk isn't open");
		}

		// Check if disk is formatted
		if (!vhd.isFormated) {
			throw runtime_error("Disk: openFile: Disk not formatted");
		}

		size_t place;
		FileHeader file = findFile(fileName, place);
		Fcb::OpenMode fcbMode;
		if (mode == string("I")){
			fcbMode = Fcb::OpenMode::I;
		} else if ((mode == string("IO")) || (mode == string("O")) || (mode == string("E"))){
			if (userName != string(file.fileDesc.fileOwner)){
				throw invalid_argument("Disk: openFile: User that isn't owner of file can't open it for writing");
			}
			if (mode == string("IO")){
				fcbMode = Fcb::OpenMode::IO;
			} else {
				fcbMode = Fcb::OpenMode::O;
			}
		} else {
			throw invalid_argument("Disk: openFile: Invalid opening mode");
		}
		Fcb *fcb = new Fcb(this);
		fcb->fat = file.FAT;
		fcb->fileDesc = file.fileDesc;
		fcb->mode = fcbMode;
		if (mode == string("E")){
			fcb->seek(2,0);
		} else {
			fcb->seek(0,0);
		}
		return unique_ptr<Fcb>(fcb);
	}

	void Disk::uploadFile(const std::string &src, const std::string &fName, const std::string &fOwner, uint32_t fit, uint8_t recSizeOption){
		// Check if mounted
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: openFile: Disk isn't open");
		}

		// Check if disk is formatted
		if (!vhd.isFormated) {
			throw runtime_error("Disk: openFile: Disk not formatted");
		}
		std::ifstream f(src, ios::binary);
		size_t recordLen;
		switch (recSizeOption){
		case 30:
			recordLen = 30;
			break;
		case 64:
			recordLen = 64;
			break;
		case 98:
			recordLen = 98;
			break;
		case 200:
			recordLen = 200;
			break;
		default:
			throw invalid_argument("Disk: uploadFile: Invalid recSizeOption given");
		}
		size_t keyLen = 4;
		Dir& targetDir = rootDir;
		RecordId recordsInSector = (SIZEOFSECTOR - sizeof(SectorId)) / (recordLen + keyLen);

		// Get the file size
		FileSize sizeInBytes;
		{
			std::streampos begin, end;
			f.seekg(0, ios::beg);
			begin = f.tellg();
			f.seekg (0, ios::end);
			end = f.tellg();
			sizeInBytes = size_t(end - begin);
		}
		f.seekg(0, ios::beg);
		RecordId sizeInRecords = sizeInBytes / recordLen + (sizeInBytes % recordLen ? 1 : 0);
		SectorId sizeInSectors = sizeInRecords / recordsInSector + (sizeInRecords % recordsInSector ? 1 : 0);
		createFile(fName, fOwner, string("F"), recordLen + keyLen, sizeInSectors, string("I"), 0, fit, keyLen);
		size_t place;
		FileHeader fileHeader = findFile(fName, place);
		fileHeader.fileDesc.fileSize = sizeInBytes;
		writeSector(fileHeader.sectorNr, reinterpret_cast<Sector*>(&fileHeader));
		targetDir[place] = fileHeader.fileDesc;

		unique_ptr<Fcb> fcb(openFile(fName, fOwner, string("O")));
		unique_ptr<char[]> charStream(new char[recordLen + keyLen]);
		unique_ptr<char[]> iStream(new char[recordLen]);
		for (size_t i=0;i<sizeInRecords;++i){
			*(reinterpret_cast<int*>(charStream.get())) = i;
			f.read(iStream.get(), recordLen);
			memcpy(charStream.get()+keyLen,iStream.get(),recordLen);
			fcb->write(charStream.get());
		}
	}

	void Disk::downloadFile(const std::string &dest, const std::string &fName, const std::string &fOwner){
		// Check if mounted
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: openFile: Disk isn't open");
		}

		// Check if disk is formatted
		if (!vhd.isFormated) {
			throw runtime_error("Disk: openFile: Disk not formatted");
		}
		size_t place;
		FileHeader fileHeader = findFile(fName, place);
		if (fileHeader.fileDesc.keyOffset != 0){
			// As per instructions, offset is always 0
			throw ios::failure("Disk: downloadFile: Unsupported key offset");
		}
		if (fileHeader.fileDesc.fileSize == 0){
			throw ios::failure("Disk: downloadFile: Can't download record based file");
		}
		if (std::string(fileHeader.fileDesc.fileOwner) != fOwner){
			throw runtime_error("Disk: downloadFile: A user who isn't the owner can't download the file");
		}
		size_t recordLen = fileHeader.fileDesc.actualRecSize - fileHeader.fileDesc.keySize;
		size_t keyLen = fileHeader.fileDesc.keySize;
		RecordId recordsInSector = (SIZEOFSECTOR - sizeof(SectorId)) / (recordLen + keyLen);
		FileSize sizeInBytes = fileHeader.fileDesc.fileSize;
		RecordId sizeInRecords = sizeInBytes / recordLen + (sizeInBytes % recordLen ? 1 : 0);
		SectorId sizeInSectors = sizeInRecords / recordsInSector + (sizeInRecords % recordsInSector ? 1 : 0);
		unique_ptr<Fcb> fcb = openFile(fName, fOwner, string("I"));
		//unique_ptr<char[]> oStream(new char[recordLen]);
		std::ofstream f(dest, ios::binary);
		for (size_t i=0;i<sizeInRecords - (sizeInBytes % recordLen ? 1 : 0);++i){
			unique_ptr<char[]> charStream(fcb->read());
			if (*(reinterpret_cast<int*>(charStream.get())) == -1) continue;
			f.write(charStream.get()+keyLen, recordLen);
		}
		if (sizeInBytes % recordLen){
			unique_ptr<char[]> charStream(fcb->read());
			f.write(charStream.get()+keyLen, sizeInBytes % recordLen);
		}
	}

	void Disk::writeFreeSector(SectorId target, Sector* sector){
		if (!dat.dat[target / CLUSTERSIZE]){
			throw runtime_error("Disk: writeFreeSector: Sector is marked as in being used");
		}
		writeSector(target, sector);
	}

	void Disk::swapClusters(ClusterId loc1, ClusterId loc2){
		Cluster cluster1(readCluster(loc1));
		Cluster cluster2(readCluster(loc2));
		writeCluster(cluster1, loc2);
		try{
			writeCluster(cluster2, loc1);
		} catch (exception e) {
			// Try to recover
			writeCluster(cluster2, loc2);
			throw ios::failure("Disk: swapClusters: Failed to swap clusters");
		}
	}

	ClusterId Disk::findFirstClusterOfFile(DatType fat){
		if (fat.none()) {
			throw runtime_error("Disk: findFirstClusterOfFile: Fat is empty");
		}
		for (ClusterId i=0; i < fat.size(); ++i){
			if (fat.test(i)){
				return i;
			}
		}
		throw logic_error("Disk: findFirstClusterOfFile: Should never get here");
	}

	void Disk::moveFile(DatType oldFat, DatType newFat, ClusterId startOfOld){
		// Sanity checks
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: moveFile: Disk isn't open");
		}
		if (!vhd.isFormated) {
			throw runtime_error("Disk: moveFile: Disk not formatted");
		}
		if (oldFat.count() != newFat.count()){
			throw invalid_argument("Disk: moveFile: Fat sizes differ");
		}
		if (!oldFat.any()){
			throw invalid_argument("Disk: moveFile: Invalid FAT");
		}

		FatReader oldFatReader(oldFat, startOfOld);
		FatReader newFatReader(newFat, findFirstClusterOfFile(newFat));
		DatType sharedFat = oldFat & newFat;
		std::map<ClusterId, ClusterId> swapMap;
		std::list<ClusterId> freeSwaps;

		// Get a list of swapping
		for (ClusterId i=0; i<oldFat.count(); ++i){
			swapMap[*oldFatReader] = *newFatReader;
			++oldFatReader;
			++newFatReader;
			// Is this more readable?
			//swapMap[oldFatReader++] = newFatReader++;
			// Check if it's a free swap
			if (sharedFat[*newFatReader] == 0){
				freeSwaps.push_back(*oldFatReader);
			}
		}

		// Preform `free` swaps (that require no saving)
		for (ClusterId oldLoc : freeSwaps){
			ClusterId newLoc = swapMap.at(oldLoc);
			swapClusters(oldLoc, newLoc);
			swapMap.erase(oldLoc);
		}
		freeSwaps.clear(); // Free some memory

		// Preform the rest of the swaps
		while (swapMap.size() > 0){
			auto toCpy = swapMap.begin();
			// Check if we need to save the target
			auto toSave = swapMap.find(toCpy->second);
			swapClusters(toCpy->first, toCpy->second);
			if (toSave != swapMap.end()){
				swapMap[toCpy->first] = toSave->second;
				swapMap.erase(toSave);
			} else {
				swapMap.erase(toCpy);
			}
		}
	}

	void Disk::defrag(size_t rounds){
		defrag(rootDir, rounds);
	}

	void Disk::defrag(Dir& dir, size_t rounds){
		// Sanity checks
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: defrag: Disk isn't open");
		}
		if (!vhd.isFormated) {
			throw runtime_error("Disk: defrag: Disk not formatted");
		}
		if (dat.dat.count() < dat.dat.size() / 100){
			throw runtime_error("Disk: defrag: Not enough free space to try and defrag");
		}

		bool changed = true;
		size_t roundsLeft = rounds;
		defragAlignStart(dir);
		while ((changed) && ((rounds == 0) || (roundsLeft > 0))){
			changed = false;

			for (auto &entry : dir) {
				if (entry.entryStatus != 1) continue;
				FileHeader file;
				readSector(entry.fileAddr, reinterpret_cast<Sector*> (&file));
				entry = file.fileDesc; // Force update
				if ((fatIsSequential(file.FAT)) && (entry.fileAddr == findFirstClusterOfFile(file.FAT) * CLUSTERSIZE)) continue;

				DatType newFat(defragFitEnd(file.FAT));
				moveFile(file.FAT, newFat, entry.fileAddr / CLUSTERSIZE);
				dat.dat |= file.FAT;
				dat.dat &= ~newFat;
				file.FAT = newFat;
				file.fileDesc.fileAddr = findFirstClusterOfFile(newFat) * CLUSTERSIZE;
				entry = file.fileDesc;
				writeSector(file.fileDesc.fileAddr, reinterpret_cast<Sector*> (&file));

				DatType datBefore = dat.dat;
				defragAlignStart(dir, entry);
				if (datBefore != dat.dat) changed = true;
			}

			defragAlignStart(dir);
			if (roundsLeft > 0) --roundsLeft; // We finished a whole round
		}
	}

	void Disk::defragAlignStart(Dir& dir, Dir::DirEntry &skip){
		// Sanity checks
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: defragAlignStart: Disk isn't open");
		}
		if (!vhd.isFormated) {
			throw runtime_error("Disk: defragAlignStart: Disk not formatted");
		}

		bool changed;
		do {
			changed = false;
			for (auto &entry : dir){
				if (entry.entryStatus != 1) continue;
				if ((skip.entryStatus == 1) && (strncmp(skip.fileName, entry.fileName, sizeof(entry.fileName)) == 0)) continue;
				if (skip == entry) continue; // Not needed HERE BE DRAGONS
				try{
					FileHeader file;
					readSector(entry.fileAddr, reinterpret_cast<Sector*> (&file));
					entry = file.fileDesc; // Force update
					DatType newFat(defragFitFirst(file.FAT));
					if ((newFat != file.FAT) || (entry.fileAddr != findFirstClusterOfFile(file.FAT) * CLUSTERSIZE)){
						changed = true;
						moveFile(file.FAT, newFat, entry.fileAddr / CLUSTERSIZE);
						dat.dat |= file.FAT;
						dat.dat &= ~newFat;
						file.FAT = newFat;
						file.fileDesc.fileAddr = findFirstClusterOfFile(newFat) * CLUSTERSIZE;
						entry = file.fileDesc;
						writeSector(file.fileDesc.fileAddr, reinterpret_cast<Sector*> (&file));
					}
				} catch (exception e) {	}
			}
		} while (changed);
	}

	bool Disk::fatIsSequential(DatType fat) const{
		ClusterId loc = findFirstClusterOfFile(fat);
		for (ClusterId i = 0; i < fat.count(); ++i){
			if (!fat.test(loc+i)) return false;
		}
		return true;
	}

	DatType Disk::defragFitFirst(DatType oldFat) const{
		// Sanity checks
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: defragFitFirst: Disk isn't open");
		}
		if (!vhd.isFormated) {
			throw runtime_error("Disk: defragFitFirst: Disk not formatted");
		}

		DatType fat;
		fat.reset();
		ClusterId freeAreaSize = 0;
		ClusterId freeAreaLocation = 0;
		for (ClusterId i = 0; i < CLUSTERSINDISK; ++i){
			if (!dat.dat.test(i) && !oldFat.test(i)){
				freeAreaLocation = (i + 1);
				freeAreaSize = 0;
			} else {
				++freeAreaSize;
				if (freeAreaSize == oldFat.count()){
					for (ClusterId j=0;j<oldFat.count();++j){
						fat[freeAreaLocation+j] = 1;
					}
					return fat;
				}
			}
		}
		throw runtime_error("Disk: defragFitFirst: Can't find enough free space");
	}

	DatType Disk::defragFitEnd(DatType oldFat) const{
		// Sanity checks
		if ((!mounted) || (!dskfl.is_open())){
			throw ios_base::failure("Disk: defragFitEnd: Disk isn't open");
		}
		if (!vhd.isFormated) {
			throw runtime_error("Disk: defragFitEnd: Disk not formatted");
		}

		DatType newFat;
		newFat.reset();
		ClusterId count = 0;
		// Scan from the end of the Fat. Stop when the finished moving through the file.
		// Due to i being unsigned, i-1 --> i > oldFat.size().
		for (ClusterId i = oldFat.size()-1; i >= 0 || i > oldFat.size(); --i){
			if ((dat.dat.test(i)) || (oldFat.test(i))){
				newFat.set(i);
				++count;
			}
			if (count == oldFat.count()) break;
		}
		if (newFat.count() != oldFat.count()){
			throw runtime_error("Disk: defragFitEnd: Failed to generate new fat"); 
		}
		return newFat;
	}

	ClusterId Disk::sizeOfFile(const std::string& fName){
		size_t loc;
		FileHeader f = findFile(fName, loc);
		return f.FAT.count();
	}

	std::vector<std::pair<ClusterId, SectorId> > Disk::locationsVectorOfFile(const std::string& fName){
		size_t loc;
		FileHeader fileHeader = findFile(fName, loc);
		return FatReader(fileHeader.FAT, fileHeader.fileDesc.fileAddr / CLUSTERSIZE).getLocationsVector();
	}

	std::ostream& operator<< (std::ostream& out, const Disk &disk){
		const VolumeHeader &vh = disk.vhd;
		out << endl;
		out << " disk name:        " << vh.diskName << endl;  
		out << " Owner Name:       " << vh.diskOwner << endl;
		out << " prodDate:         " << convertDate(vh.prodDate) << endl;
		out << " formatDate:       " << convertDate(vh.formatDate) << endl;
		out << " isFormated:       " << vh.isFormated << endl; 
		out << " addrDataStart:    " << vh.addrDataStart << endl;

		out << " ClusQty:          " << vh.clusQty << endl;  
		out << " dataClusQty:      " << vh.dataClusQty << endl;

		out << " addrDAT:          " << vh.addrDat << endl; 
		out << " addrRootDir:      " << vh.addrRootDir << endl; 
		out << " addrDATcpy:       " << vh.addrDatCpy << endl;  
		out << " addrRootDirCpy:   " << vh.addrRootDirCpy << endl << endl;

		return out;
	}

	Disk::FatReader::FatReader(const DatType &fat, ClusterId phyStart):fat(fat), phyLoc(phyStart), phyStart(phyStart), logicLoc(0){
		if (!fat.any()){
			throw invalid_argument("Disk: FatReader: Empty FAT");
		}
		if (!fat.test(phyStart)){
			throw invalid_argument("Disk: FatReader: Invalid starting point");
		}
	}

	ClusterId Disk::FatReader::operator*(){
		return phyLoc;
	}

	ClusterId Disk::FatReader::operator++(){
		do{
			phyLoc = (phyLoc+1) % CLUSTERSINDISK;
		} while (fat[phyLoc] != 1);
		logicLoc = (logicLoc + 1) % fat.count();
		return phyLoc;
	}

	ClusterId Disk::FatReader::operator++(int){
		ClusterId oldLoc = phyLoc;
		do{
			phyLoc = (phyLoc+1) % CLUSTERSINDISK;
		} while (fat[phyLoc] != 1);
		logicLoc = (logicLoc + 1) % fat.count();
		return oldLoc;
	}

	ClusterId Disk::FatReader::operator--(){
		do{
			phyLoc = (phyLoc-1) % CLUSTERSINDISK;
		} while (fat[phyLoc] != 1);
		logicLoc = (logicLoc - 1) % fat.size();
		return phyLoc;

	}

	ClusterId Disk::FatReader::operator--(int){
		ClusterId oldLoc = phyLoc;
		do{
			phyLoc = (phyLoc-1) % CLUSTERSINDISK;
		} while (fat[phyLoc] != 1);
		logicLoc = (logicLoc - 1) % fat.size();
		return oldLoc;
	}

	std::vector<std::pair<ClusterId, SectorId> > Disk::FatReader::getLocationsVector() const{
		vector<pair<ClusterId, SectorId> > vec;
		pair<ClusterId,SectorId> p;
		p.first = phyStart;
		p.second = CLUSTERSIZE;
		ClusterId curr = phyStart;
		for (ClusterId curr=phyStart+1;curr!=phyStart;curr=(curr+1)%CLUSTERSINDISK){
			if (fat[curr] == 0){
				if (p.second > 0){
					vec.push_back(p);
				}
				p.first = (curr+1)%CLUSTERSINDISK;
				p.second = 0;
			} else {
				p.second += CLUSTERSIZE;
			}
		}
		if (p.second > 0){
			vec.push_back(p);
		}
		return vec;
	}
}