#VERTEX
#version 320 es

// Attributes
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


// Interpolated outputs
out Varying {
   vec3        normal;
   vec2        texCoord;
   vec3        position;
} vertexOutput;

void main() {
    vertexOutput.normal = normalize(mat3x3(projection*view*model) * normal);
    vertexOutput.position = (projection*view*model * vec4(position, 1.0)).xyz;
    vertexOutput.texCoord = texCoord;

    gl_Position = projection*view*model*vec4(position, 1.0);
}

#FRAGMENT
#version 320 es

in Varying{
   lowp vec3 normal;
   lowp vec2 texCoord;
   lowp vec3 position;
} interpolated;

uniform sampler2D TextureSampler;

//uniform sampler2D colorTexture;
out lowp vec3 pixelColor;

void main() {
    //pixelColor = texture(colorTexture, interpolated.texCoord).rgb;
    //pixelColor = vec3(interpolated.texCoord.xy, 0);
	pixelColor = texture(TextureSampler,interpolated.texCoord).rgb;
    //pixelColor = vec3(1.0f,0.5f,0.2f);
}
