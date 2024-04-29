#pragma once
#include <string>
#include <map>

namespace DeduplicationApp {
	namespace HashStorage {
		class HashStorage {
		public:
			void setup();
			HashStorage();
			~HashStorage();
		private:
		public:
			std::string Folder;
			std::map <long long, std::string> hash_chunk;
		};
	}
}