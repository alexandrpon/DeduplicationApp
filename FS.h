#pragma once

namespace DeduplicationApp {
	namespace FS {
		void getDirFiles(char* filename);
		void serialize(char* object, size_t size, char* filename);
		void deserialize(char* object, size_t size, char* filename);
	}
}
