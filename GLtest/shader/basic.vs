#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;

out vec3 VPosition;
out vec3 VNormal;
out vec3 VColor;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

uniform vec3 ObjectPosition;
uniform vec3 ObjectScale;
uniform vec3 ObjectRotation;

void main()
{
	vec3 rotate = ObjectRotation/vec3(1,0,0);
    vec3 pos = VertexPosition*ObjectScale+ObjectPosition;
	VNormal = normalize( NormalMatrix * VertexNormal );
	VNormal = normalize( VertexNormal );
    VPosition = vec3(ModelViewMatrix * vec4(pos,1.0));
	VColor = VertexColor;
    gl_Position = MVP * vec4(pos,1.0);
}
