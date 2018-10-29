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
uniform mat4 MVP;
uniform mat4 ShadowMatrix;

uniform vec3 ObjectPosition;
uniform vec3 ObjectScale;
uniform mat4 ObjectRotation;

void main()
{
    mat4 rotate = ObjectRotation/mat4(1);
    vec3 scaled = VertexPosition*ObjectScale;
    //vec4 rotated = vec4(scaled,1.0);
    vec4 rotated = ObjectRotation*vec4(scaled,0);
    vec4 pos = rotated + vec4(ObjectPosition,1);
    vec4 rotated_normal = ObjectRotation*vec4(VertexNormal,0);
    VNormal = normalize(vec3(rotated_normal.x,rotated_normal.y,rotated_normal.z));
    VPosition = vec3(ModelViewMatrix * pos);
    VColor = VertexColor;
    VTexCoord = VertexTexCoord;
    VShadowCoord = ShadowMatrix * pos;
    gl_Position = MVP * pos;
}
