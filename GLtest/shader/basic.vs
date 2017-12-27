#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;
layout (location = 3) in vec2 VertexTexCoord;

out vec3 VPosition;
out vec3 VNormal;
out vec3 VColor;
out vec2 VTexCoord;
out vec4 VShadowCoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
uniform mat4 ShadowMatrix;

uniform vec3 ObjectPosition;
uniform vec3 ObjectScale;
uniform vec3 ObjectRotation;

void main()
{
	vec3 rotate = ObjectRotation/vec3(1,0,0);
    vec3 pos = VertexPosition*ObjectScale+ObjectPosition;
	VNormal = normalize( NormalMatrix * VertexNormal );
    VPosition = vec3(ModelViewMatrix * vec4(pos,1.0));
	VColor = VertexColor;
	VTexCoord = VertexTexCoord;
    VShadowCoord = ShadowMatrix * vec4(pos,1.0);
    gl_Position = MVP * vec4(pos,1.0);
}
