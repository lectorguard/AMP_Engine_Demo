#VERTEX
#version 320 es
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    TexCoords = aTexCoords;
}  
#FRAGMENT
#version 320 es
out lowp vec4 FragColor;
  
in highp vec2 TexCoords;

uniform sampler2D screenTexture;
uniform int ShadingType;  

void main()
{ 
	if(ShadingType == 0){
		FragColor = texture(screenTexture, TexCoords);
		if(FragColor == vec4(0.0,0.0,0.0,1.0))FragColor = vec4(0.0,0.0,0.0,0.0);
	}else if(ShadingType == 1){
		FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)),1.0);
	}else if(ShadingType == 2){
		lowp const float offset = 1.0 / 300.0;

		lowp vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    //lowp float kernel[9] = float[](
    //    -1.0, -1.0, -1.0,
    //    -1.0,  9.0, -1.0,
    //    -1.0, -1.0, -1.0
    //);

	lowp float kernel[9] = float[](
    1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,
    2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0,
    1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0  
	);
    
    lowp vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    lowp vec3 col = vec3(0.0,0.0,0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    FragColor = vec4(col, 1.0);
	}
}
