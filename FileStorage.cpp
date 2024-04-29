#pragma once
#include "FileStorage.h"
#include "Globals.h"

namespace DeduplicationApp {
	namespace FileStorage {
		void FileStorage::setup() {
			Folders = INITFILE.Default.file_storage_dir[0];

			FILE* file = fopen(INITFILE.Default.file_storage_dir[0], "r+");
			if (file != NULL) {
				while (!feof(file)) {
					std::string keySize = "", valueSize = "";
					int c;
					c = getc(file);
					while (!feof(file)) {
						if (c == ' ') break;
						keySize += (char)c;
						c = getc(file);
					}
					c = getc(file);
					while (!feof(file)) {
						if (c == ' ') break;
						valueSize += (char)c;
						c = getc(file);
					}
					int intKeySize = _atoi64(keySize.c_str()), intValueSize = _atoi64(valueSize.c_str());

					std::string key = "", value = "";

					for (size_t i = 0; i < intKeySize; i++)
					{
						c = getc(file);
						key += c;
					}

					for (size_t i = 0; i < intValueSize; i++)
					{
						c = getc(file);
						value += c;
					}

					if (key != "") hash_file[key] = value;
				}
				fclose(file);
			}
		}

		FileStorage::FileStorage() {}

		FileStorage::~FileStorage() {
			FILE* file = fopen(INITFILE.Default.file_storage_dir[0], "r+");
			if (file != NULL) {

				for (auto& item : hash_file)
				{
					std::string curFirst = item.first, curSecond = item.second;

					std::string size = std::to_string(curFirst.size());
					for (size_t i = 0; i < size.size(); i++) putc(size[i], file);
					putc(' ', file);

					size = std::to_string(curSecond.size());
					for (size_t i = 0; i < size.size(); i++) putc(size[i], file);
					putc(' ', file);

					for (int i = 0; i < curFirst.size(); i++) putc(curFirst[i], file);
					for (int i = 0; i < curSecond.size(); i++) putc(curSecond[i], file);
				}

				fclose(file);
			}
		}
	}
}