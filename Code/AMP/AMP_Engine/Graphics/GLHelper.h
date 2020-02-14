// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#include "GLES3/gl3platform.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../AssetLoader/MeshLoaderFromObj.h"

namespace GLHelper {

	template<typename T>
	static void SetBufferData(const T* data, size_t count, GLenum type = GL_STATIC_DRAW) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * count, data, type);
	}

	static inline void CreateBuffer(GLuint& buffer, GLenum target = GL_ARRAY_BUFFER) {
		if (buffer == GL_NONE)
			glGenBuffers(1, &buffer);
		glBindBuffer(target, buffer);
	}

	template<typename T>
	static void SetBuffer(GLuint& buffer, size_t count, const T* data, GLenum target = GL_ARRAY_BUFFER) {
		CreateBuffer(buffer, target);
		if (count > 0) {
			glBufferData(target, sizeof(T) * count, data, GL_STATIC_DRAW);
		}
	}

	static void ErrorCheck() {
		GLenum error = glGetError();
		assert(error == GL_NONE);
	}

	static unsigned int CreateUniformInt(GLuint& ShaderProgram, const char* Name) {
		return glGetUniformLocation(ShaderProgram, Name);
	}

	static void SetUniformInt(GLuint& UniformInt) {
		glUniform1i(UniformInt, 0);
	}

	static int SetTexture(GLuint& textureBuffer, TexAttributes* texAttr,GLuint& ShaderProgram,const char* textureName) {
		glGenTextures(1, &textureBuffer);
		glBindTexture(GL_TEXTURE_2D, textureBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, texAttr->numberOfComponents == 4 ? GL_RGBA : GL_RGB, texAttr->width, texAttr->height, 0, texAttr->numberOfComponents == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texAttr->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		return CreateUniformInt(ShaderProgram, textureName);
	}

	static void SetUniformMatrix(unsigned int shaderProgram, const char* name, glm::mat4 matrix)
	{
		unsigned int loc = glGetUniformLocation(shaderProgram, name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	static void SetUniformVector(unsigned int ShaderProgram, const char* name, glm::vec3 vector) {
		unsigned int loc = glGetUniformLocation(ShaderProgram, "CustomColor");
		glUniform3fv(loc, 1, glm::value_ptr(vector));
	}

	//Texture ID is already set
	static void BindTexture(unsigned int texture, int textureNumber = 0,GLenum type = GL_TEXTURE_2D)
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber);
		glBindTexture(type, texture);
	}

	//Texture ID becomes set here
	static void BindTexture(unsigned int texture, unsigned int textureID, int textureNumber = 0, GLenum type = GL_TEXTURE_2D) {
		BindTexture(texture, textureNumber, type);
		glUniform1i(textureID, 0);
	}

	static void BindArrayBuffer(unsigned int index, int size, unsigned int buffer)
	{
		glEnableVertexAttribArray(index);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	template<typename T>
	static void BindAndSetArrayBuffer(unsigned int index, int size, unsigned int buffer,int count, const T* data,GLenum type)
	{
		glEnableVertexAttribArray(index);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		SetBufferData(data, count, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
}
