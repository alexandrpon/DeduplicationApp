#pragma once
#include <stdio.h>
#include <iostream>


namespace DeduplicationApp {
	namespace Configuration {
		namespace ini {

			struct SECTIONS {

				struct DEFAULT {
					char** hash_storage_dir;
					size_t hash_storage_dir_number;

					char** file_storage_dir;
					size_t file_storage_dir_number;

					size_t chunk_size;
					size_t fingerprint_length;
				} Default;

			};

			struct Section;
			struct Dict;

			void ini(char* filename);
			Section* parseIni(char* filename);

			void parseComment(FILE* file);
			void parseEmptyLine(FILE* file);
			void parseSection(FILE* file, char** section);
			void parseDict(FILE* file, char** key, size_t& paramNumber, char*** value);
			void print(Section* ini);

		}
	}
}