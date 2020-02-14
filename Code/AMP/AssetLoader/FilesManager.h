// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "android/asset_manager.h"
#include "stdlib.h"
#include "string"
#include "sstream"
#include "istream"


namespace amp
{
	class FilesManager
	{

	public:
		//Path relative from the Asset Folder as origin
		//char* has to be freed !!
		static char* readAssetFile(AAssetManager* manager,const char* path, int mode = AASSET_MODE_BUFFER);
		//Path relative from the Asset Folder as origin
		static void readShaderFile(AAssetManager* manager,const char* path,std::string& vertexFile, std::string& fragmentFile);
		//Path relative from the Asset Folder as origin
		static FILE* readImageFile(AAssetManager* manager, const char* path);
	private:
		static int android_read(void* cookie, char* buf, int size) {
			return AAsset_read((AAsset*)cookie, buf, size);
		}

		static int android_write(void* cookie, const char* buf, int size) {
			return EACCES; // can't provide write access to the apk
		}

		static fpos_t android_seek(void* cookie, fpos_t offset, int whence) {
			return AAsset_seek((AAsset*)cookie, offset, whence);
		}

		static int android_close(void* cookie) {
			AAsset_close((AAsset*)cookie);
			return 0;
		}
	};
}

