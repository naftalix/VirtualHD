#include <sstream>
#include "Student.h"
using namespace std;
using namespace Fms;

namespace FmsUtils{
	Student::Student(){	
		id = 0;
		memset(name, '\0', sizeof(name));
		memset(address, '\0', sizeof(address));
		average=0;
	}

	Student::Student(std::unique_ptr<char[]> c){
		*this = Student(c.get());
	}

	Student::Student(char *c){
		size_t offset = 0;
		memcpy(reinterpret_cast<char*>(&id), c+offset, sizeof(int));
		offset += sizeof(int);
		memcpy(name, c+offset, sizeof(name));
		offset += sizeof(name);
		memcpy(address, c+offset, sizeof(address));
		offset += sizeof(address);
		memcpy(reinterpret_cast<char*>(&average), c+offset, sizeof(int));
	}

	std::unique_ptr<char[]> Student::toCharStream(){
		unique_ptr<char[]> c(new char[200]);
		size_t offset = 0;
		memcpy(c.get()+offset, reinterpret_cast<char*>(&id), sizeof(int));
		offset += sizeof(int);
		memcpy(c.get()+offset, name, sizeof(name));
		offset += sizeof(name);
		memcpy(c.get()+offset, address, sizeof(address));
		offset += sizeof(address);
		memcpy(c.get()+offset, reinterpret_cast<char*>(&average), sizeof(int));

		return c;
	}

	StudentRecord::StudentRecord(): key(0){	}

	StudentRecord::StudentRecord(std::unique_ptr<char[]> c){
		*this = StudentRecord(c.get());
	}

	StudentRecord::StudentRecord(char *c){
		size_t offset = 0;
		memcpy(reinterpret_cast<char*>(&key), c+offset, sizeof(int));
		offset += sizeof(int);
		memcpy(reinterpret_cast<char*>(&student.id), c+offset, sizeof(int));
		offset += sizeof(int);
		memcpy(student.name, c+offset, sizeof(student.name));
		offset += sizeof(student.name);
		memcpy(student.address, c+offset, sizeof(student.address));
		offset += sizeof(student.address);
		memcpy(reinterpret_cast<char*>(&student.average), c+offset, sizeof(int));
	}

	std::unique_ptr<char[]> StudentRecord::toCharStream(){
		unique_ptr<char[]> c(new char[204]);
		size_t offset = 0;
		memcpy(c.get()+offset, reinterpret_cast<char*>(&key), sizeof(int));
		offset += sizeof(int);
		memcpy(c.get()+offset, reinterpret_cast<char*>(&student.id), sizeof(int));
		offset += sizeof(int);
		memcpy(c.get()+offset, student.name, sizeof(student.name));
		offset += sizeof(student.name);
		memcpy(c.get()+offset, student.address, sizeof(student.address));
		offset += sizeof(student.address);
		memcpy(c.get()+offset, reinterpret_cast<char*>(&student.average), sizeof(int));

		return c;
	}

	void StudentRecord::uploadStudentsFile(Fms::Disk& d, std::string fName, std::string src){
		size_t counter = 0;
		size_t lines = 0;
		ifstream f(src);
		if (!f) throw ios::failure("StudentRecord: uploadStudentsFile: Can't open file for reading");
		string line;
		while (std::getline(f, line)){
			if (line.size() == 0) continue;
			++lines;
		}
		d.createFile(fName, std::string("Students"), std::string("F"), 204, lines / 5 + (lines % 5 ? 0 : 1), std::string("I"), 0, 1, 4);
		unique_ptr<Fcb> fcb = d.openFile(fName, std::string("Students"), std::string("E"));
		
		f.clear();
		f.seekg(0);
		for (size_t i=0;i<lines;++i){
			std::getline(f, line);
			if (line.size() == 0) continue;
			StudentRecord r;
			stringstream(line) >> r.student;
			r.key = counter++;
			fcb->write(r.toCharStream().get());
		}
	}

	void StudentRecord::downloadStudentsFile(Fms::Disk& d, std::string fName, std::string dst){
		unique_ptr<Fcb> fcb = d.openFile(fName, "Students", "I");
		ofstream f(dst);
		if (!f) throw ios::failure("StudentRecord: downloadStudentsFile: Can't open file for writing");
		while (!fcb->eof()){
			StudentRecord record(fcb->read());
			if (record.key != -1){
				f << record.student;
			}
		}
	}

	std::string StudentRecord::studentFileAsString(Fms::Disk& d, std::string fName){
		unique_ptr<Fcb> fcb = d.openFile(fName, "Students", "I");
		stringstream stream;
		while (!fcb->eof()){
			StudentRecord record(fcb->read());
			if (record.key != -1){
				stream << "ID = " << record.student.id << "\t\t\tNAME = " << record.student.name << "\nADDRESS = " << record.student.address << "\t\tAVERAGE: " << record.student.average << "\n" << std::endl;
			}
		}
		return stream.str();
	}

	std::ostream& operator<<(std::ostream& o, const Student &s){
		o << s.id << "\t" << s.name << "\t" << s.address << "\t" << s.average << "\n";
		return o;
	}

	std::istream& operator>>(std::istream& i, Student &s){
		i >> s.id >> s.name >> s.address >> s.average;
		return i;
	}
}