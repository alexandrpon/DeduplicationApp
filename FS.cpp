#pragma once
#include "FS.h"
#include <stdio.h>

namespace DeduplicationApp {
	namespace FS {
		void getDirFiles(char* filename) {

		};

		void serialize(char* object, size_t size, char* filename) {
			FILE* file = fopen(filename, "rb+");
			if (file != NULL) {
				for (; size--; )
				{
					putc(*object++, file);
				}
				fclose(file);
			}
		};

		void deserialize(char* object, size_t size, char* filename) {
			FILE* file = fopen(filename, "rb+");
			if (file != NULL) {
				for (; size--; )
				{
					*object = getc(file);
					object++;
				}
				fclose(file);
			}
		};
	}
}
