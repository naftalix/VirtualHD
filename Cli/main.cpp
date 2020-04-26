#include<iostream>
#include<array>
#include "Disk.h"
#include "Student.h"

using namespace std;
using namespace Fms;


void mainText();
void testAllocation(Disk &);
enum class MENUOPTIONS : int {SHOWSIZES=0, CREATEDISK=1, RECREATEDISK, MOUNTDISK, UNMOUNTDISK, FORMATDISK,
	READSECTOR, WRITESECTOR, TESTALLOCATIONFROMFILE, CREATEFILE, DELFILE,
	EXTENDFILE, SHOWDISK, SHOWDAT, ACTIVEENTRIESNUMBER, SHOWDIRECTORY, DEFRAG, EXIT, CHEATCODE=98, CHEATCODE2, CHEATCODE3, CHEATCODE4};

int main(){

	Disk disk; // Disk object
	int choose;

	do{
		try{
			mainText();
			cin >> choose;
			switch (choose){
			case MENUOPTIONS::CHEATCODE:
				try{
					disk.unmountDisk();
				} catch(...) {}
				disk.mountDisk(string("aa"));
				disk.unmountDisk();
				disk.recreateDisk(string("aa"));
				disk.mountDisk(string("aa"));
				disk.format(string("aa"));
				disk.uploadFile(string("1.txt"), string("hello"), string("1"));
				disk.uploadFile(string("1.exe"), string("exec"), string("1"));
				break;
			case MENUOPTIONS::CHEATCODE2:
				try{
					disk.unmountDisk();
				} catch(...) {}
				disk.mountDisk(string("aa"));
				disk.downloadFile(string("2.txt"), string("hello"), string("1"));
				disk.downloadFile(string("2.exe"), string("exec"), string("1"));
				break;
			case MENUOPTIONS::CHEATCODE3:
				try{
					disk.unmountDisk();
				} catch(...) {}
				disk.mountDisk(string("aa"));
				disk.unmountDisk();
				disk.recreateDisk(string("aa"));
				disk.mountDisk(string("aa"));
				disk.format(string("aa"));
				disk.uploadFile(string("1.txt"), string("1.txt"), string("1"));
				disk.uploadFile(string("1.log"), string("1.log"), string("1"));
				disk.uploadFile(string("1a.txt"), string("1a.txt"), string("1"));
				disk.uploadFile(string("1.cpp"), string("1a.cpp"), string("1"));
				disk.delFile(string("1a.txt"), string("1"));
				disk.uploadFile(string("1.exe"), string("1.exe"), string("1"));
				disk.uploadFile(string("1a.txt"), string("1a.txt"), string("1"));
				disk.defrag();
				disk.downloadFile(string("2.txt"), string("1.txt"), string("1"));
				disk.downloadFile(string("2.log"), string("1.log"), string("1"));
				disk.downloadFile(string("2a.txt"), string("1a.txt"), string("1"));
				disk.downloadFile(string("2.cpp"), string("1a.cpp"), string("1"));
				disk.downloadFile(string("2.exe"), string("1.exe"), string("1"));

				break;
			case MENUOPTIONS::CHEATCODE4:
				{
					try{
						disk.unmountDisk();
					} catch(...) {}
					disk.mountDisk(string("aa"));
					disk.unmountDisk();
					disk.recreateDisk(string("aa"));
					disk.mountDisk(string("aa"));
					disk.format(string("aa"));
					FmsUtils::StudentRecord::uploadStudentsFile(disk, string("stud"), string("stud.txt"));
				}
				break;
			case MENUOPTIONS::SHOWSIZES: // Print the size of disk parts
				{
					Dir d;
					cout << endl;
					cout << "Dat " << sizeof(Dat) << endl;
					SectorId dirSize = 0;
					for (const auto &it : d.sectorOutputAsVector()){
						dirSize += sizeof(it);
					}
					cout << "Dir " << dirSize << endl;
					cout << "DirEntry " << sizeof(Dir::DirEntry) << endl;
					cout << "Disk " << sizeof(Disk) << endl;
					cout << "FileHeader " << sizeof(FileHeader) << endl;
					cout << "Sector " << sizeof(Sector) << endl;
					cout << "VolumeHeader " << sizeof(VolumeHeader);
				}
				break;
			case MENUOPTIONS::CREATEDISK: // Create a new disk
				{	
					string diskName, ownerName;
					cout << "Enter the file name and the owner name\n>> ";
					cin >> diskName >> ownerName;
					disk.createDisk(diskName, ownerName);
					cout << "The disk has been created.";
				}
				break;
			case MENUOPTIONS::RECREATEDISK: // Recreate a disk
				{
					string ownerName;
					cout << "Enter the name of the disk owner\n>> ";
					cin >> ownerName;
					disk.recreateDisk(ownerName);
					cout << "The disk has been recreated.";
				}
				break;
			case MENUOPTIONS::MOUNTDISK: // Mount disk
				{
					string fileName;
					cout << "Enter the file name where the disk is stored\n>> ";
					cin >> fileName;
					disk.mountDisk(fileName);
					cout << "The disk has been mounted.";
				}
				break;
			case MENUOPTIONS::UNMOUNTDISK: // Unmount disk
				disk.unmountDisk();
				cout << "The disk has been unmounted.";
				break;
			case MENUOPTIONS::READSECTOR:
				{
					SectorId sectorId;
					Sector sector;
					cout << "Please enter sector number.\n>> ";
					cin >> sectorId;
					disk.readSector(sectorId, &sector);
					cout << sector;
				}
				break;
			case MENUOPTIONS::WRITESECTOR:
				{
					SectorId sectorId;
					Sector sector;
					cout << "Please enter sector number and your data.\n>> ";
					cin >> sectorId;
					//cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin.getline(sector.rawData, sizeof(sector.rawData)-1);
					disk.writeSector(sectorId, &sector);
					cout << "The sector has been written.";
				}
				break;
			case MENUOPTIONS::SHOWDISK: // Show some data about the disk
				cout << disk;
				break;
			case MENUOPTIONS::FORMATDISK:
				{
					string ownerName;
					cout << "Please enter the owner name\n>> ";
					cin >> ownerName;
					disk.format(ownerName);
				}
				cout << "The disk has been formatted.";
				break;
			case MENUOPTIONS::TESTALLOCATIONFROMFILE:
				{
					cout << "Please be sure that your 'test-file' is in the right folder of the program!" << endl
						<< "Press Enter to continue..." << endl;
					cin.clear();
					cin.sync();
					cin.get();
					testAllocation(disk);
				}
				break;
			case MENUOPTIONS::CREATEFILE:
				{
					string fileName, ownerName, fileType, keyType;
					size_t recordLength, keyOffset, keyLength;
					uint32_t fit;
					SectorId numSectors;
					cout << "\nPlease enter:" << endl
						<< "1. File Name." << endl
						<< "2. Owner Name." << endl
						//	<< "3. File Type. ('F' for Fixed length file. 'V' for Variable length length file)" << endl
						//	<< "4. Record Length." << endl
						<< "3. Num of Sectors." << endl
						//	<< "6. Key Type ('I' int, 'F' Float, 'D' Double, 'C' Array of characters)" << endl
						//	<< "7. Key Offset." << endl
						<< "4. 'Fit' algorithm. (0 - First fit, 1 - Best fit, 2 - Worse fit)" << endl
						<< ">> ";
					cin >> fileName >> ownerName /*>> fileType >> recordLength*/ >> numSectors /*>> keyType >> keyOffset*/ >> fit;
					fileType = "F";
					recordLength = 2;
					keyType = "I";
					keyOffset = 2;
					keyLength = 0;

					//if (keyType[0] == 'C'){
					//	cout << "You selected 'Key Type' as array of characters, Please enter 'Key length': \n>> ";
					//	cin >> keyLength;
					//}
					//else 
					//	keyLength = 0;
					disk.createFile(fileName, ownerName, fileType, recordLength, numSectors, keyType, keyOffset, fit, keyLength);
					cout << "\nThe file has been created.";
				}
				break;
			case MENUOPTIONS::DELFILE:
				{
					string fileName, ownerName;
					cout << "\nPlease enter \n1. file Name. \n2. owner Name.\n>> ";
					cin >> fileName >> ownerName;
					disk.delFile(fileName, ownerName);
					cout << "\nThe file has been deleted.";
				}
				break;
			case MENUOPTIONS::EXTENDFILE:
				{
					string fileName, ownerName;
					SectorId numSectors;
					cout << "\nPlease enter: \n1. file Name. \n2. owner Name. \n3. num of Sectors. \n>> ";
					cin >> fileName >> ownerName >> numSectors;
					disk.extendFile(fileName, ownerName, numSectors);
					cout << "\nThe file has been extended.";
				}
				break;
			case MENUOPTIONS::SHOWDAT:
				cout << disk.getDat();
				break;
			case MENUOPTIONS::ACTIVEENTRIESNUMBER:
				{
					cout << "The current active entries of dir is: " << disk.getDir().activeEntries();
				}
				break;
			case MENUOPTIONS::SHOWDIRECTORY:
				{
					cout << disk.getDir();
				}
				break;
			case MENUOPTIONS::DEFRAG:
				{
					disk.defrag();
				}
				break;
			default:
				if(choose != static_cast<int> (MENUOPTIONS::EXIT)){
					cout << "Invalid option, try again.\n";
				}
				break;
			}

			// Go a line down after finishing the item
			cout << endl;

		} catch(exception ex){
			std::cout << "Exception was thrown: " << ex.what() << std::endl;
		}
		if(choose !=  static_cast<int> (MENUOPTIONS::EXIT)){
			cout << "\nPress Enter to go back to the menu...";
			cin.clear();
			cin.sync();
			cin.get();
			system("cls");
		}
	} while (choose != static_cast<int> (MENUOPTIONS::EXIT));

	return 0;
}

//! \brief Print a simple menu for program navigation.
void mainText(){
	cout << endl 
		<< "Welcome to Disk Management Program" << endl
		<< "Please choose an option below:\n" << endl
		<< "==================================\n" << endl
		<< "  " << static_cast<int> (MENUOPTIONS::SHOWSIZES) << ".) Show sizes." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::CREATEDISK) << ".) Create Disk." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::RECREATEDISK) << ".) Recreate Disk." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::MOUNTDISK) << ".) Mount Disk." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::UNMOUNTDISK) << ".) Unmount disk." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::FORMATDISK) << ".) Format Disk." << endl  
		<< "  " << static_cast<int> (MENUOPTIONS::READSECTOR) << ".) Read sector." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::WRITESECTOR) << ".) Write sector." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::TESTALLOCATIONFROMFILE) << ".) Test allocation from file." << endl 
		<< "  " << static_cast<int> (MENUOPTIONS::CREATEFILE) << ".) Create file." << endl 
		<< "  " << static_cast<int> (MENUOPTIONS::DELFILE) << ".) Delete file." << endl 
		<< "  " << static_cast<int> (MENUOPTIONS::EXTENDFILE) << ".) Extend file." << endl 
		<< "  " << static_cast<int> (MENUOPTIONS::SHOWDISK) << ".) Show Disk." << endl 	
		<< "  " << static_cast<int> (MENUOPTIONS::SHOWDAT) << ".) Show DAT." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::ACTIVEENTRIESNUMBER) << ".) Show active directory entries number." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::SHOWDIRECTORY) << ".) Show directory." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::DEFRAG) << ".) Defrag (Not the safest function to say the least)." << endl
		<< "  " << static_cast<int> (MENUOPTIONS::EXIT) << ".) Exit" << endl
		<< "\n>> ";
}

//! \brief Process the contents of alloc.txt as commands.
void testAllocation(Disk& disk){
	ifstream fin("alloc.txt");
	if (!fin)
		throw runtime_error("Main: testAllocation: file not found");

	char action;
	string fileNum , temp;
	SectorId sectorsNum;
	uint32_t fit;
	size_t entryPlace;
	string fitsName[3] = {"First-fit", "Best-fit", "Worst-fit"};
	size_t i = 0;
	temp = "F";

	while ((fin.peek()) && (!fin.eof())){
		fin.clear();
		fin >> action;
		if (action == 'A' || action == 'E'){
			fin >> fileNum >> sectorsNum >> fit;

			if (action == 'A'){
				disk.createFile(fileNum, fileNum, temp, 2, sectorsNum, temp, 2, fit, 0); 
				cout << "Action number " << ++i << ": \n'Allocate file': " << fileNum 
					<< ". \nClusters number: " << (sectorsNum/CLUSTERSIZE + sectorsNum % CLUSTERSIZE)  << " Fit-type: " << fitsName[fit] << endl;
			}
			if (action == 'E'){
				disk.extendFile(fileNum, fileNum, sectorsNum, fit); 
				cout << "Action number " << ++i << ": \n'Extend allocate file': " << fileNum 
					<< ". \nClusters number: " << (sectorsNum/CLUSTERSIZE + sectorsNum % CLUSTERSIZE) << " Fit-type: " << fitsName[fit] << endl;
			}

			FileHeader file = disk.findFile(fileNum, entryPlace);
			cout << "The FAT of file " << fileNum << " is: \n" << file.FAT << endl;

		} else if (action == 'D'){
			fin >> fileNum;
			disk.delFile(fileNum, fileNum);
			cout << "Action number " << ++i << ": \n'Deallocate file': " << fileNum << endl;
		}
		cout << endl << disk.getDat();
		cout << "Press any key to next action test...";
		cin.clear();
		cin.sync();
		cin.get();
	}
}
