// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "Mesh.h"


amp::Mesh::~Mesh()
{
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &texCoordBuffer);
	if(texture != GL_NONE)glDeleteTextures(1, &texture);
	GLHelper::ErrorCheck();
}



void amp::Mesh::Mesh_SetUpGL(TEXT ShaderProgramPath, TEXT MeshAttributesPath,TEXT MeshMTLPath, TEXT TexturePath)
{	
	LoadShader(ShaderProgramPath);
	auto attr = LoadMesh(MeshAttributesPath, MeshMTLPath);
	SetAttributes(attr);
	LoadTexture(TexturePath);
	GLHelper::ErrorCheck();
}

void amp::Mesh::LoadTexture(TEXT TexturePath)
{
	if (!engine)throw "Engine Pointer not set for Mesh Component";
	TexAttributes* texAttr;
	if (auto result = engine->currentScene.AssetAttribMap.tryFind(TexturePath.getHash())) {
		texAttr = (TexAttributes*)*result;
	}
	else {
		texAttr = engine->meshLoader.loadTextureFromImage(TexturePath.getCharArray());
		engine->currentScene.AssetAttribMap.add(TexturePath.getHash(), texAttr);
	}
	TexID = GLHelper::SetTexture(texture,texAttr, ShaderProgram, "TextureSampler");
}

MeshAttributes* amp::Mesh::LoadMesh(TEXT MeshAttributesPath, TEXT MeshMTLPath)
{
	if (!engine)throw "Engine Pointer not set for Mesh Component";
	MeshAttributes* meshAttr;
	if (auto result = engine->currentScene.AssetAttribMap.tryFind(MeshAttributesPath.getHash())) {
		meshAttr = (MeshAttributes*)*result;
	}
	else {
		meshAttr = engine->meshLoader.loadOBJMesh(MeshAttributesPath.getCharArray(), MeshMTLPath.getCharArray());
		engine->currentScene.AssetAttribMap.add(MeshAttributesPath.getHash(), meshAttr);
	}
	this->MeshAttributesPath = MeshAttributesPath;
	return meshAttr;
}

void amp::Mesh::SetAttributes(MeshAttributes* meshAttr)
{
	NumIndices = meshAttr->indices.size();
	GLHelper::SetBuffer(indexBuffer, NumIndices, meshAttr->indices.data(),GL_ELEMENT_ARRAY_BUFFER);
	GLHelper::SetBuffer(positionBuffer, meshAttr->positions.size(), meshAttr->positions.data());
	GLHelper::SetBuffer(normalBuffer, meshAttr->normals.size(), meshAttr->normals.data());
	GLHelper::SetBuffer(texCoordBuffer, meshAttr->texCoords.size(), meshAttr->texCoords.data());
}

void amp::Mesh::LoadShader(TEXT ShaderProgramPath)
{
	if (!engine)throw "Engine Pointer not set for Mesh Component";
	ShaderAttributes* shaderAttr;
	if (auto result = engine->currentScene.AssetAttribMap.tryFind(ShaderProgramPath.getHash())) {
		shaderAttr = (ShaderAttributes*)*result;
	}
	else
	{
		shaderAttr = engine->ampShader.getShaderProgramFromPath(ShaderProgramPath.getCharArray());
		engine->currentScene.AssetAttribMap.add(ShaderProgramPath.getHash(), shaderAttr);
	}
	this->ShaderProgram = shaderAttr->ShaderProgram;
}

void amp::Mesh::draw()
{
	if (ShaderProgram == GL_NONE)throw "Mesh has to be set Up before becoming updated";
	glUseProgram(ShaderProgram);

	GLHelper::SetUniformMatrix(ShaderProgram, "model", AppliedTransform);
	GLHelper::SetUniformMatrix(ShaderProgram, "view", Camera::getView());
	GLHelper::SetUniformMatrix(ShaderProgram, "projection", Camera::getProjection());

	GLHelper::BindTexture(texture,TexID);
	GLHelper::BindArrayBuffer(0, 3, positionBuffer);
	GLHelper::BindArrayBuffer(1, 3, normalBuffer);
	GLHelper::BindArrayBuffer(2, 2, texCoordBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	GLHelper::ErrorCheck();
}

void amp::Mesh::update()
{
	if(isDrawEnabled)draw();
}