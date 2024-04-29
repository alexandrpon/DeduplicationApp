
#include "Globals.h"
#include "Configuration.h"
#include "FS.h"
#include "Commands.h"

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;	

#define INIPATH "config.ini"

//void setup() {
//	while (1) {
//		cout << "1. Choose FILE_STORAGE\n 2. Choose HASH_STORAGE\n 3. Choose CHUNK_SIZE\n";
//		char option;
//		cin >> option;
//		string str;
//		cin >> str;
//		switch (option)
//		{
//		case '1':
//#define FILE_STORAGE str
//			break;
//		case '2':
//#define HASH_STORAGE str
//			break;
//		case '3':
//#define CHUNK_SIZE str
//			break;
//		default:
//			option = ' ';
//			break;
//		}
//		if (option != ' ') {
//			cout << "Setup end\n";
//			break;
//		}
//		cout << "Error happend. Try again\n";
//	}
//    
//	return;
//}
//
//
//int fingerprint(const uint8_t* data, char* fingerprint) {
//	
//	
//	string str = "";
//	for (int i = 0; i < CHUNKSIZE; i++) {
//		str += data[i];
//	}
//	//memcpy(str, data, FINGERPRINT_LENGTH);
//	//string[FINGERPRINT_LENGTH] = '\0';
//	hash<string> hasher;
//	int ans = hasher(str);
//	//memset(fingerprint, 0, FINGERPRINT_LENGTH);
//
//	//uint64_t hash = 5381;
//	//int c;
//	//while ((c = *data++))
//	//	hash = ((hash << 5) + hash) + c;
//
//	//memcpy(fingerprint, &hash, sizeof(uint64_t));
//	return ans;
//}



int main()
{
	DeduplicationApp::Configuration::ini::ini((char*)INIPATH);
	HASHSTORAGE.setup();
	FILESTORAGE.setup();
	
	char filename[] = "D:\\Projects\\VisualStudio\\TestStorage\\test.txt";
	DeduplicationApp::Commands::addFile(filename);
	//DeduplicationApp::Commands::getFile(filename);

	/*cout << INITFILE.Default.chunk_size << '\n';
	cout << INITFILE.Default.fingerprint_length << '\n';

	for (size_t i = 0; i < INITFILE.Default.file_storage_dir_number; i++)
	{
		cout << INITFILE.Default.file_storage_dir[i] << '\n';
	}

	for (size_t i = 0; i < INITFILE.Default.hash_storage_dir_number; i++)
	{
		cout << INITFILE.Default.hash_storage_dir[i] << '\n';
	}*/


	/*string path = FILESTORAGE.Folders;
	for (const auto& entry : fs::directory_iterator(path)) {
		FILE* file = fopen((char*)entry.path().c_str(), "r+");
		if (file != NULL) {
			while (!feof(file)) {

			}
			fclose(file);
		}
		std::cout << entry.path() << std::endl;
	}*/


	return 0;

	//map<string, int> hash_store;

	//uint8_t* buffer = (uint8_t*) malloc(CHUNKSIZE);
	//if (buffer == NULL) {
	//	fprintf(stderr, "Failed to allocate memory for buffer\n");
	//	exit(EXIT_FAILURE);
	//}

	//// Process input data in chunks
	//size_t bytes_read;
	//char fp[FINGERPRINT_LENGTH];
	//while ((bytes_read = fread(buffer, 1, CHUNKSIZE, stdin)) > 0) {
	//	cout << "rgdsf\n";
	//	fingerprint(buffer, fp);
	//	cout << "rgdsf\n";
	//	cout << bytes_read << '/n';
	//	//printf(PRINTF_FMT, PRINTF_CAST * ((uint64_t*)fp), bytes_read);
	//}

	//cout << "rgdsf\n";

	//free(buffer);
    
}
