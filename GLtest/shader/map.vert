#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

struct LightInfo{
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};
uniform LightInfo Light;

struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

void main()
{
    LightIntensity = VertexPosition;

    gl_Position = vec4(VertexPosition.x/10,VertexPosition.y/10,VertexPosition.z/10,1.0);
}
