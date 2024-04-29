#pragma once
#include "ini.h"
#include "Globals.h"
#include <stdio.h>
#include <iostream>


namespace DeduplicationApp {
	namespace Configuration {
		namespace ini {

			struct Dict
			{
				char* keyName;
				size_t paramNumber;
				char** valueName;
				Dict* nextDict;
			};

			struct Section
			{
				char* sectionName;
				Dict* dict;
				Section* nextSection;
			};

			void parseComment(FILE* file) {
				int c = getc(file);

				if (feof(file)) return;

				if (c == ';') {
					while (c != '\n' && !feof(file)) {
						c = getc(file);
					}
				} else {
		#ifdef linux
					fseek(file, -1, SEEK_CUR);
		#endif
			
		#ifdef _WIN32
					if (c == '\n') fseek(file, -2, SEEK_CUR);
					else fseek(file, -1, SEEK_CUR);
		#endif
				}
			}

			void parseEmptyLine(FILE* file) {
				int c = getc(file);
				if (feof(file)) return;

				if (c != '\n') {
					fseek(file, -1, SEEK_CUR);
				}
			}

			void parseSection(FILE* file, char** section) {
				int c = getc(file);
				if (feof(file)) return;

				if (c == '[') {
					// sectionName size
					size_t position = ftell(file);
					while (c != ']') {
						c = getc(file);
					}
					size_t size = ftell(file) - position;

					if (!fseek(file, position, SEEK_SET)) {
						char* sectionName = (char*)malloc(size);
						if (sectionName) {
							for (size_t i = 0; i < size; i++) {
								sectionName[i] = getc(file);
							}
							sectionName[size - 1] = '\0';
						}
						*section = sectionName;
					}
				}
				else {
		#ifdef linux
					fseek(file, -1, SEEK_CUR);
		#endif

		#ifdef _WIN32
					if (c == '\n') fseek(file, -2, SEEK_CUR);
					else fseek(file, -1, SEEK_CUR);
		#endif
					*section = NULL;
				}
			}

			void parseDict(FILE* file, char** key, size_t& paramNumber, char*** value) {
				int c = getc(file);
				if (feof(file)) return;

				if (c != '[' && c != '\n' && c != ';') {
					// key size
					size_t position = ftell(file);
					while (c != ' ' && c != '=') {
						c = getc(file);
					}
					size_t size = ftell(file) - position + 1;

					if (!fseek(file, position - 1, SEEK_SET)) {
						char* keyName = (char*)malloc(size);
						if (keyName) {
							for (size_t i = 0; i < size; i++) {
								keyName[i] = getc(file);
							}
							keyName[size - 1] = '\0';
						}
						*key = keyName;
					}

					// values number
					if (c == ' ') {
						while (c != '=') {
							c = getc(file);
						}
					}

					c = getc(file);
					while (c == ' ') c = getc(file);

					position = ftell(file);
					paramNumber = 1;
					while (c != '\n' && !feof(file)) {
						if (c == ',') paramNumber++;
						c = getc(file);
					}

					if (!fseek(file, position - 1, SEEK_SET)) {
						char** paramName = (char**)malloc(paramNumber * sizeof(char*));

						for (size_t i = 0; i < paramNumber; i++) {
							position = ftell(file);
							c = getc(file);
							while (c != ' ' && c != ',' && c != '\n' && !feof(file)) {
								c = getc(file);
							}
							size_t size = ftell(file) - position;
		#ifdef _WIN32
							if (c == '\n') size--;
		#endif
							if (feof(file)) size++;

							if (!fseek(file, position, SEEK_SET)) {
								paramName[i] = (char*)malloc(size);
								if (paramName[i]) {
									for (size_t j = 0; j < size; j++) {
										paramName[i][j] = getc(file);
									}
									paramName[i][size - 1] = '\0';
								}
							}
					
							while (c == ' ' || c == ',') c = getc(file);
							if (!feof(file)) fseek(file, ftell(file) - 1, SEEK_SET);
						}

						*value = paramName;
					}
				}
				else {
		#ifdef linux
					fseek(file, -1, SEEK_CUR);
		#endif

		#ifdef _WIN32
					if (c == '\n') fseek(file, -2, SEEK_CUR);
					else fseek(file, -1, SEEK_CUR);
		#endif
					*key = NULL;
					*value = NULL;
					paramNumber = 0;
				}
			}

			Section* parseIni(char* filename) {
				FILE* file = fopen(filename, "r+");
				Section* curSection = (Section*)malloc(sizeof(Section));
				*curSection = { NULL, NULL, NULL };

				Section* ini = curSection;

				if (file != NULL) {
					Dict* curDict = NULL;
					while (!feof(file)) {
						parseComment(file);

						char* sectionName;
						parseSection(file, &sectionName);
						if (sectionName) {

							if (curSection->sectionName != NULL) {
								Section* nextSection = (Section*)malloc(sizeof(Section));
								*nextSection = { NULL, NULL, NULL };

								curSection->nextSection = nextSection;
								curSection = nextSection;
								curDict = NULL;
							}
							curSection->sectionName = sectionName;
							//free(sectionName);
						}
						parseEmptyLine(file);

						char* keyName;
						size_t paramNumber;
						char** valueName;
						parseDict(file, &keyName, paramNumber, &valueName);
						if (keyName && valueName) {
							if (curDict == NULL) {
								Dict* dict = (Dict*)malloc(sizeof(Dict));
								*dict = { NULL, 0, NULL, NULL };

								curDict = dict;
								curSection->dict = curDict;
							} else  {
								Dict* nextDict = (Dict*)malloc(sizeof(Dict));
								*nextDict = { NULL, 0, NULL, NULL };
								curDict->nextDict = nextDict;
								curDict = nextDict;
							}
							curDict->keyName = keyName;
							curDict->paramNumber = paramNumber;
							curDict->valueName = valueName;

							//for (int i = 0; i < paramNumber; i++) {
							//	free(valueName[i]);
							//}
							//free(keyName);
							//free(valueName);
						}
					}
					fclose(file);
				}
				return ini;
			}

			void print(Section* ini) {
		
				std::cout << "\n\nINI STRUCTURE\n\n";

				while (1) {
					if ((*ini).sectionName != NULL) std::cout << "SECTION " << (*ini).sectionName << "\n\n";
					if ((*ini).dict != NULL) {
						Dict* dict = (*ini).dict;
						while (1) {
							std::cout << "\tKEYNAME " << (*dict).keyName << " = ";
							for (size_t i = 0; i < (*dict).paramNumber; i++) {
								std::cout << (*dict).valueName[i] << ", ";
							}
							std::cout << '\n';
							if ((*dict).nextDict == NULL) break;
							dict = (*dict).nextDict;
						}
						std::cout << '\n';
					}
					if ((*ini).nextSection != NULL) ini = (*ini).nextSection;
					else break;
				}

			}

			void ini(char* filename) {
				Section* ini = parseIni(filename);
				//print(ini);
		
				while (1) {

					if (!strcmp(ini->sectionName, "default")) {

						if (ini->dict != NULL) {

							Dict* dict = ini->dict;
							while (1) {
								if (!strcmp(dict->keyName, "hash_storage_dir")) {
									INITFILE.Default.hash_storage_dir = dict->valueName;
									INITFILE.Default.hash_storage_dir_number = dict->paramNumber;
								}
								if (!strcmp(dict->keyName, "file_storage_dir")) {
									INITFILE.Default.file_storage_dir = dict->valueName;
									INITFILE.Default.file_storage_dir_number = dict->paramNumber;
								}
								if (!strcmp(dict->keyName, "chunk_size")) {
									INITFILE.Default.chunk_size = atoi(dict->valueName[0]);

								}
								if (!strcmp(dict->keyName, "fingerprint_length")) {
									INITFILE.Default.fingerprint_length = atoi(dict->valueName[0]);
								}

								if (dict->nextDict == NULL) break;
								dict = dict->nextDict;
							}
						}
					}

					if (ini->nextSection != NULL) ini = ini->nextSection;
					else break;
				}

			}
		}
	}
}