// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "android/asset_manager.h"
#include "GLES3/gl31.h"
#include "../AssetLoader/FilesManager.h"
#include "../AssetLoader/Attributes.h"
#include "string"

#define  IS_USED_AT_RUNTIME true

struct ShaderAttributes : public Attributes
{
	ShaderAttributes():Attributes(IS_USED_AT_RUNTIME){};
	~ShaderAttributes() override {
		if(!isSelfOrganized)glDeleteProgram(ShaderProgram);
	};
	unsigned int ShaderProgram;
	bool isSelfOrganized = false;
};

namespace amp
{
	class Shader
	{
	public:
		Shader() {};
		~Shader() {};
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		ShaderAttributes* getShaderProgramFromPath(const char* path);
	private:
		AAssetManager* manager;
		unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
		unsigned int CreateShader(const char* Source, GLenum Type);
		void setAssetManager(AAssetManager* manager);
		friend class AMP_Engine;
	};
}

