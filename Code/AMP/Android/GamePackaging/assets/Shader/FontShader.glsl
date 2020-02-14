#VERTEX
#version 320 es
layout (location = 0) in vec2 aPos;
layout(location = 1) in vec2 uvCoords;
uniform vec3 CustomColor;
out vec3 Color;
out vec2 UV;
 
void main()
{
	gl_Position = vec4(aPos,0,1.0);
	UV = uvCoords;
	Color = CustomColor;
}
#FRAGMENT
#version 320 es
uniform sampler2D FontTexSampler;
in lowp vec2 UV;
in highp vec3 Color;
out lowp vec4 PixelColor;
					
void main()
{
     lowp vec4 tempColor = texture(FontTexSampler,UV);
	 PixelColor = vec4(Color,1.0-tempColor.x);
}
