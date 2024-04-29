#pragma once
#include <string>
#include <map>


namespace DeduplicationApp {
	namespace FileStorage {
		class FileStorage {
		public:
			void setup();
			FileStorage();
			~FileStorage();
		private:
		public:
			std::string Folders;
			std::map <std::string, std::string> hash_file;
		};
	}
}