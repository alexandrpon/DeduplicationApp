#pragma once
#include "HashStorage.h"
#include "FileStorage.h"
#include "ini.h"

extern DeduplicationApp::HashStorage::HashStorage HASHSTORAGE;
extern DeduplicationApp::FileStorage::FileStorage FILESTORAGE;
extern DeduplicationApp::Configuration::ini::SECTIONS INITFILE;