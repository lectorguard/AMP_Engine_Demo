// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#include "GLES3/gl3platform.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "Component.h"
#include "../AssetLoader/MeshLoaderFromObj.h"
#include "AMP_Engine.h"
#include "Text.h"
#include "vector"
#include "cstdio"
#include "cassert"
#include "Graphics/Shader.h"
#include "Graphics/GLHelper.h"




namespace amp
{
	struct TextRenderInformation {
		TEXT text;
		int locX = 0;
		int locY = 0;
		int fontsize = 60;
		TextRenderInformation(TEXT text){
			this->text = text;
		};
	};
	
	class TextRenderer : public Component
	{
	public:
		TextRenderer() {};
		TextRenderer(const TextRenderer&) = delete;
		TextRenderer(TextRenderer&&) = delete;
		~TextRenderer() override;
		void setUpText(TEXT FontTexturePath, TEXT ShaderProgramPath, const int CharactersPerLine = 32, const int NumberOfLines = 8);

		void renderText(std::string text, int locX, int locY, int fontsize, float duration = 0.0f);

		void renderText(TextRenderInformation info, float duration = 0.0f);

		void renderText(std::string text, float duration = 0.0f);

		int count() { return textInfos.size(); }

		void eraseLast();

		void eraseElementByHash(size_t hash);

		void setColor(float r, float g, float b) {
			ColorRGB = glm::vec3(r, g, b);
		}

		void setAnimation(bool IsAnim) {
			this->isAnim = IsAnim;
		}

	private:
		void update() override;

		void draw();

		void DurationRemoveEvent(float duration, TEXT& curr);

		void SetUVsAndVerticesForText(TextRenderInformation& info, std::vector<glm::vec2>& positions, std::vector<glm::vec2>& uvs);

		void SetLetterUVs(char character, std::vector<glm::vec2>& uvs);

		void SetLetterVertices(TextRenderInformation& info, int row, int column, std::vector<glm::vec2>& positions);

		void ColorChangingTextAnimation();

		unsigned int VBO = GL_NONE;
		unsigned int VertexBuffer = GL_NONE;
		unsigned int UVBuffer = GL_NONE;
		unsigned int ShaderProgram = GL_NONE;
		unsigned int TextureID = GL_NONE;
		unsigned int Texture = GL_NONE;

		glm::vec3 ColorRGB = glm::vec3(1.0,1.0,1.0);
		bool isAnim = false;
		int CharactersPerLine = 32;
		int NumberOfLines = 8;
		double accumulator = 0.0;
		glm::vec2 HalfWidthHeight = glm::vec2(0,0);
		std::vector<TextRenderInformation> textInfos;
	};
}

