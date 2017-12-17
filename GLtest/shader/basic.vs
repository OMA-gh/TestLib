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

void main()
{
    
	VNormal = normalize( NormalMatrix * VertexNormal );
	VNormal = normalize( VertexNormal );
    VPosition = vec3(ModelViewMatrix * vec4(VertexPosition,1.0));
	VColor = VertexColor;
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
