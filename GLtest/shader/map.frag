#version 400

in vec3 LightIntensity;

layout( location = 0 ) out vec4 FragColor;

void main() {
	FragColor = vec4(0.0,0.0,LightIntensity.y, 1.0);
}
