#pragma once
#include "Commands.h"
#include "Globals.h"

namespace DeduplicationApp {
	namespace Commands {
		
		long long polyhash(std::string str) {
			long long k = 31, mod = 1e9 + 7;

			long long h = 0, m = 1;
			for (int c : str) {
				h = (h + m * c) % mod;
				m = (m * k) % mod;
			}
			return h;
		}

		void addFile(char* filename) {

			FILE* file = fopen(filename, "rb+");
			if (file != NULL) {
				std::string fileChunk = "";

				while (!feof(file)) {

					std::string chunk = "";
					for (size_t i = 0; i < INITFILE.Default.chunk_size; i++)
					{
						int c = getc(file);
						if (!feof(file)) break;
						chunk += (char)c;
					}
					while (chunk.size() < INITFILE.Default.chunk_size) chunk += ' ';
					long long hash = polyhash(chunk);
					HASHSTORAGE.hash_chunk[hash] = chunk;
					std::string hashString = std::to_string(hash);
					for (size_t i = hashString.size(); i < INITFILE.Default.fingerprint_length; i++) fileChunk += ' ';

					fileChunk += hash;
				}

				FILESTORAGE.hash_file[filename] = fileChunk;

				fclose(file);
			}
		}

		void getFile(char* filename) {

			if (FILESTORAGE.hash_file.count(filename)) {
				std::string file = "", hashStr = FILESTORAGE.hash_file[filename];
				std::cout << "  hashfile  " << hashStr << '\n';
				for (size_t i = 0; i < hashStr.size(); i++)
				{
					std::string hash = "";
					for (size_t j = 0; j < INITFILE.Default.fingerprint_length && i < hashStr.size(); j++) {
						hash += hashStr[i];
						i++;
					}
					file += HASHSTORAGE.hash_chunk[_atoi64(hash.c_str())];
					std::cout << "  hash   " << _atoi64(hash.c_str()) << '\n';
					std::cout << "   chunk   " << HASHSTORAGE.hash_chunk[_atoi64(hash.c_str())] << '\n';
				}
				std::cout << file << '\n';
			}
		}

		void removeFile(char* filename);
		void getStorageSize(char* filename);
		void getFileStorageSize(char* filename);
		void getHashStorageSize(char* filename);

	}
}
