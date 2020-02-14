// Copyright 2020 Simon Keller. All Rights Reserved.

#include "pch.h"
#include "HelmetActor.h"
#include "Graphics/FrameBuffer.h"


void HelmetActor::Update()
{
	RotateActor(-1, 0, 1, 0);
}

void HelmetActor::OnTouch(int32_t x, int32_t y)
{
	// TO DO: PostProcessing has huge performance impact

	//if(engine->sceneBuffer.getShadingType() == 2)
	//	engine->sceneBuffer.setShadingType(amp::ShadingType::DEFAULT);
	//else engine->sceneBuffer.setShadingType(amp::ShadingType::BLUR);
}


void HelmetActor::AfterWindowStartup()
{
	helmet->Mesh_SetUpGL(TEXT("Shader/MeshShader.glsl"),	//Shader
		TEXT("3DModels/helmet.obj"),					//OBJ
		TEXT("3DModels/helmet.mtl"),					//MTL
		TEXT("Textures/helmet.png"));					//Texture
	ScaleActor(0.5f);
	TranslateActor(0, 80, 0);
}
