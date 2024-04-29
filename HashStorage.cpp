#pragma once
#include <string>
#include "HashStorage.h"
#include "Globals.h"

namespace DeduplicationApp {
	namespace HashStorage {
		void HashStorage::setup() {
			Folder = INITFILE.Default.hash_storage_dir[0];

			FILE * file = fopen(INITFILE.Default.hash_storage_dir[0], "r+");
			if (file != NULL) {
				while(!feof(file)) {
					std::string key = "", value = "";
					int c;
					c = getc(file);
					while (!feof(file)) {
						if (c == ':') break;
						key += (char)c;
						c = getc(file);
					}
					c = getc(file);
					while (!feof(file)) {
						if (c == '\n') break;
						value += c;
						c = getc(file);
					}
					if (key != "") hash_chunk[_atoi64(key.c_str())] = value;
				}
				fclose(file);
			}
		}

		HashStorage::HashStorage() {}

		HashStorage::~HashStorage() {
			FILE* file = fopen(INITFILE.Default.hash_storage_dir[0], "r+");
			if (file != NULL) {

				for (auto& item : hash_chunk)
				{
					std::string cur = std::to_string(item.first);
					for (int i = 0; i < cur.size(); i++) putc(cur[i], file);
					putc(':', file);
					cur = item.second;
					for (int i = 0; i < cur.size(); i++) putc(cur[i], file);
					putc('\n', file);
				}

				fclose(file);
			}
		}
	}
}