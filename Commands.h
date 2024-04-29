#pragma once

namespace DeduplicationApp {
	namespace Commands {

		void addFile(char* filename);
		void getFile(char* filename);
		void removeFile(char* filename);
		void getStorageSize(char* filename);
		void getFileStorageSize(char* filename);
		void getHashStorageSize(char* filename);

	}
}
