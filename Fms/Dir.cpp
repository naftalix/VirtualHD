#include "Dir.h"
#include<stdexcept>

namespace Fms{
	Dir::Dir(){	}

	Dir::Dir(std::vector<Sector> sectors){
		if (sectors.size() != CLUSTERSIZE){
			throw std::invalid_argument("Dir constructor. Given vector isn't correct");
		}
		sectorNr = sectors[0].sectorNr;
		for (SectorId i=0; i<sectors.size(); ++i){
			memcpy(dirs[i], reinterpret_cast<char*> (&(sectors[i]))+sizeof(SectorId), ENTRIESPERSECTOR * sizeof(DirEntry));
		}
	}

	Dir::DirEntry::DirEntry(){
		memset(fileName, '\0', sizeof(fileName));
		memset(fileOwner, '\0', sizeof(fileOwner));
		fileAddr = 0;
		memset(crDate, '\0', sizeof(crDate));
		fileSize = 0;
		eofRecNr = 0;
		maxRecSize = 0;
		actualRecSize = 0;
		memset(recFormat, '\0', sizeof(recFormat));
		keyOffset = 0;
		keySize = 0;
		memset(keyType, '\0', sizeof(keyType));
		entryStatus = 0;
	}

	Dir::DirEntry& Dir::operator[](SectorId i){
		if (i > size()) throw std::out_of_range("Dir operator[]: Out of range");
		return dirs[i / ENTRIESPERSECTOR][i % ENTRIESPERSECTOR];
	}

	const Dir::DirEntry& Dir::operator[](SectorId i) const{
		if (i > size()) throw std::out_of_range("Dir operator[] const: Out of range");
		return dirs[i / ENTRIESPERSECTOR][i % ENTRIESPERSECTOR];
	}

	size_t Dir::size() const{
		return ENTRIESPERSECTOR * CLUSTERSIZE;
	}

	size_t Dir::activeEntries() const{
		size_t entriesNum = 0;
		for (auto entry : *(this)){
			if (entry.entryStatus == 1){
				++entriesNum;
			}
		}
		return entriesNum;	
	}

	bool Dir::DirEntry::operator==(const DirEntry &entry) const{
		if (
			(strncmp(fileName, entry.fileName, sizeof(fileName)) != 0) ||
			(strncmp(fileOwner, entry.fileOwner, sizeof(fileOwner)) != 0) || 
			(fileAddr != entry.fileAddr) ||
			(strncmp(crDate, entry.crDate, sizeof(crDate)) != 0) ||
			(fileSize != entry.fileSize) ||
			(eofRecNr != entry.eofRecNr) ||
			(maxRecSize != entry.maxRecSize) ||
			(actualRecSize != entry.actualRecSize) ||
			(strncmp(recFormat, entry.recFormat, sizeof(recFormat)) != 0) ||
			(keyOffset != entry.keyOffset) ||
			(keySize != entry.keySize) ||
			(strncmp(keyType, entry.keyType, sizeof(keyType)) != 0) ||
			(entryStatus != entry.entryStatus)){
				return false;
		}
		return true;
	}

	bool Dir::DirEntry::operator!=(const DirEntry &entry) const{
		return !operator==(entry);
	}

	bool Dir::operator==(const Dir &dir) const{
		// Compare all entries in the folder
		for (ClusterId cluster=0; cluster<CLUSTERSIZE; ++cluster){
			for (SectorId sector=0; sector<SIZEOFSECTOR; ++sector){
				if (dirs[cluster][sector] != dir.dirs[cluster][sector]){
					return false;
				}
			}
		}
		return true;
	}

	bool Dir::operator!=(const Dir &dir) const{
		return !operator==(dir);
	}

	std::vector<Sector> Dir::sectorOutputAsVector() const{
		std::vector<Sector> sectors;
		for (int i=0;i<CLUSTERSIZE;++i){
			Sector sector;
			sector.sectorNr = sectorNr+i;
			memcpy(reinterpret_cast<char*> (&sector) + sizeof(SectorId), dirs[i], ENTRIESPERSECTOR * sizeof(DirEntry));
			sectors.push_back(sector);
		}
		return sectors;
	}

	std::unique_ptr<char[]> Dir::sectorOutputAsCharStream() const{
		char *output = new char[CLUSTERSIZE * SIZEOFSECTOR];

		for (int i=0;i<CLUSTERSIZE;++i){
			SectorId location = sectorNr + i;
			memcpy(output + SIZEOFSECTOR*i, &location, sizeof(SectorId));
			memcpy(output + SIZEOFSECTOR*i + sizeof(SectorId), dirs[i], SIZEOFSECTOR - sizeof(SectorId));
		}
		return std::unique_ptr<char[]>(output);
	}

	Dir::Dir(const char * input){
		memcpy(&sectorNr, input, sizeof(SectorId));
		for (int i=0;i<CLUSTERSIZE;++i){
			memcpy(dirs[i], input + SIZEOFSECTOR*i + sizeof(SectorId), ENTRIESPERSECTOR * sizeof(DirEntry));
		}
	}

	Dir::iterator Dir::begin(){
		return iterator(this, 0);
	}

	Dir::iterator Dir::end(){
		return iterator(this, CLUSTERSIZE*ENTRIESPERSECTOR);
	}

	Dir::iterator::iterator(Dir *p, SectorId loc):p(p), loc(loc){ }

	bool Dir::iterator::operator==(const Dir::iterator &it) const{
		return ((p == it.p) && (loc == it.loc));
	}

	bool Dir::iterator::operator!=(const Dir::iterator &it) const{
		return !operator==(it);
	}

	bool Dir::iterator::operator>(const Dir::iterator &it) const{
		if (p != it.p) return false;
		return  loc > it.loc;
	}

	bool Dir::iterator::operator<(const Dir::iterator &it) const{
		if (p != it.p) return false;
		return  loc < it.loc;
	}

	bool Dir::iterator::operator>=(const Dir::iterator &it) const{
		if (p != it.p) return false;
		return !operator<(it);
	}

	bool Dir::iterator::operator<=(const Dir::iterator &it) const{
		if (p != it.p) return false;
		return !operator>(it);
	}

	Dir::DirEntry& Dir::iterator::operator*(){
		return (*p)[loc];
	}

	Dir::DirEntry* Dir::iterator::operator->(){
		return &(*p)[loc];
	}

	Dir::DirEntry& Dir::iterator::operator[](int){
		return (*p)[loc];
	}

	Dir::iterator Dir::iterator::operator++(){
		if (operator==(p->end())) throw std::out_of_range("Dir iterator: ++ Out of range");
		++loc;
		return *this;
	}

	Dir::iterator Dir::iterator::operator++(int){
		if (operator==(p->end())) throw std::out_of_range("Dir iterator: ++ Out of range");
		iterator tmp(*this);
		++loc;
		return tmp;
	}

	Dir::iterator Dir::iterator::operator--(){
		if (operator==(p->begin())) throw std::out_of_range("Dir iterator: -- Out of range");
		--loc;
		return *this;
	}

	Dir::iterator Dir::iterator::operator--(int){
		if (operator==(p->begin())) throw std::out_of_range("Dir iterator: -- Out of range");
		iterator tmp(*this);
		--loc;
		return tmp;
	}

	Dir::iterator Dir::iterator::operator+(const int &n) const{
		if (operator>(p->end())) throw std::out_of_range("Dir iterator: + Out of range");
		iterator tmp = *this;
		tmp.loc+=n;
		return tmp;
	}

	Dir::iterator Dir::iterator::operator-(const int &n) const{
		if (operator>(p->begin())) throw std::out_of_range("Dir iterator: + Out of range");
		iterator tmp = *this;
		tmp.loc-=n;
		return tmp;
	}

	Dir::iterator Dir::iterator::operator+=(const int &n){
		if (operator>(p->end())) throw std::out_of_range("Dir iterator: + Out of range");
		loc+=n;
		return *this;
	}

	Dir::iterator Dir::iterator::operator-=(const int &n){
		if (operator>(p->begin())) throw std::out_of_range("Dir iterator: + Out of range");
		loc-=n;
		return *this;
	}

	int Dir::iterator::operator-(const Dir::iterator &it) const{
		if (p != it.p) throw std::logic_error("Dir iterator: iterator - iterator - iterator mismatch");
		return loc - it.loc;
	}

	// const_iterator
	Dir::const_iterator Dir::begin() const{
		return const_iterator(this, 0);
	}

	Dir::const_iterator Dir::end() const{
		return const_iterator(this, CLUSTERSIZE*ENTRIESPERSECTOR);
	}

	Dir::const_iterator::const_iterator(const Dir *p, SectorId loc):p(p), loc(loc){ }

	Dir::const_iterator::const_iterator(const iterator& it): p(p), loc(loc){ }

	bool Dir::const_iterator::operator==(const Dir::const_iterator &it) const{
		return ((p == it.p) && (loc == it.loc));
	}

	bool Dir::const_iterator::operator!=(const Dir::const_iterator &it) const{
		return !operator==(it);
	}

	bool Dir::const_iterator::operator>(const Dir::const_iterator &it) const{
		if (p != it.p) return false;
		return  loc > it.loc;
	}

	bool Dir::const_iterator::operator<(const Dir::const_iterator &it) const{
		if (p != it.p) return false;
		return  loc < it.loc;
	}

	bool Dir::const_iterator::operator>=(const Dir::const_iterator &it) const{
		if (p != it.p) return false;
		return !operator<(it);
	}

	bool Dir::const_iterator::operator<=(const Dir::const_iterator &it) const{
		if (p != it.p) return false;
		return !operator>(it);
	}

	const Dir::DirEntry& Dir::const_iterator::operator*(){
		return (*p)[loc];
	}

	const Dir::DirEntry* Dir::const_iterator::operator->(){
		return &(*p)[loc];
	}

	const Dir::DirEntry& Dir::const_iterator::operator[](int){
		return (*p)[loc];
	}

	Dir::const_iterator Dir::const_iterator::operator++(){
		if (operator==(p->end())) throw std::out_of_range("Dir iterator: ++ Out of range");
		++loc;
		return *this;
	}

	Dir::const_iterator Dir::const_iterator::operator++(int){
		if (operator==(p->end())) throw std::out_of_range("Dir iterator: ++ Out of range");
		const_iterator tmp(*this);
		++loc;
		return tmp;
	}

	Dir::const_iterator Dir::const_iterator::operator--(){
		if (operator==(p->begin())) throw std::out_of_range("Dir iterator: -- Out of range");
		--loc;
		return *this;
	}

	Dir::const_iterator Dir::const_iterator::operator--(int){
		if (operator==(p->begin())) throw std::out_of_range("Dir iterator: -- Out of range");
		const_iterator tmp(*this);
		--loc;
		return tmp;
	}

	Dir::const_iterator Dir::const_iterator::operator+(const int &n) const{
		if (operator>(p->end())) throw std::out_of_range("Dir iterator: + Out of range");
		const_iterator tmp = *this;
		tmp.loc+=n;
		return tmp;
	}

	Dir::const_iterator Dir::const_iterator::operator-(const int &n) const{
		if (operator>(p->begin())) throw std::out_of_range("Dir iterator: + Out of range");
		const_iterator tmp = *this;
		tmp.loc-=n;
		return tmp;
	}

	Dir::const_iterator Dir::const_iterator::operator+=(const int &n){
		if (operator>(p->end())) throw std::out_of_range("Dir iterator: + Out of range");
		loc+=n;
		return *this;
	}

	Dir::const_iterator Dir::const_iterator::operator-=(const int &n){
		if (operator>(p->begin())) throw std::out_of_range("Dir iterator: + Out of range");
		loc-=n;
		return *this;
	}

	int Dir::const_iterator::operator-(const Dir::const_iterator &it) const{
		if (p != it.p) throw std::logic_error("Dir iterator: iterator - iterator - iterator mismatch");
		return loc - it.loc;
	}

	std::ostream& operator<< (std::ostream &out, const Dir &dir){

		out << std::endl;
		size_t num = 0;

		for (size_t i=0; i < dir.size(); ++i){
			if (dir[i].entryStatus == 1){
				out << "File number:\t\t\t" << ++num << std::endl;
				out << "\tFile name:\t\t\t" << dir[i].fileName << std::endl;
				out << "\tFile owner:\t\t\t" << dir[i].fileOwner << std::endl;
				out << "\tFirst sector:\t\t\t" << dir[i].fileAddr << std::endl;
				out << "\tCreated date:\t\t\t" << convertDate(dir[i].crDate) << std::endl;
				out << "\tFile size:\t\t\t" << dir[i].fileSize << std::endl;
				out << "\tEof Record Number:\t\t" << dir[i].eofRecNr << std::endl;
				out << "\tMax Record Size:\t\t" << dir[i].maxRecSize << std::endl;
				out << "\tActual Record Size:\t\t" << dir[i].actualRecSize << std::endl;
				out << "\tRecord Format:\t\t" << dir[i].recFormat[0] << std::endl;
				out << "\tKey Offset:\t\t\t" << dir[i].keyOffset << std::endl;
				out << "\tKey Size:\t\t\t" << dir[i].keySize << std::endl;
				out << "\tKey Type:\t\t\t" << dir[i].keyType[0] << std::endl;
				out << "\tEntry Status:\t\t\t" << int(dir[i].entryStatus) << std::endl;
				out << std::endl;
			}
		}
		if (dir == 0){
			out << "Directory is empty\n:";
		}
		return out;
	}

}