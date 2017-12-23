#version 400

in vec3 GPosition;
in vec3 GNormal;
in vec3 GColor;
in vec2 GTexCoord;
noperspective in vec3 GEdgeDistance;

uniform sampler2D RenderTex;

subroutine vec4 RenderPassType();
subroutine uniform RenderPassType RenderPass;

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

uniform struct LineInfo {
  float Width;
  vec4 Color;
} Line;

layout( location = 0 ) out vec4 FragColor;

void phongModel(out vec3 outAmbAndDiff,out vec3 outSpec){
    vec3 s = normalize(vec3(Light.Position - GPosition));
	float light_dist = length(Light.Position-GPosition);
	vec3 v = normalize(-GPosition.xyz);
	vec3 r = reflect( -s, GNormal);
	vec3 ambient = Light.La * Material.Ka;
	float sDotN = max(dot(s,GNormal),0.0);
	vec3 diffuse = Light.Ld * Material.Kd * GColor * sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN>0.0){
		spec = Light.Ls * Material.Ks * pow( max( dot(r,v), 0.0), Material.Shininess);
	}
	outAmbAndDiff = ambient + diffuse;
	outSpec = spec;
}
subroutine (RenderPassType)
vec4 pass1()
{
	// Find the smallest distance
    float d = min( GEdgeDistance.x, GEdgeDistance.y );
    d = min( d, GEdgeDistance.z );

    float mixVal;
    if( d < Line.Width - 1 ) {
        mixVal = 1.0;
    } else if( d > Line.Width + 1 ) {
        mixVal = 0.0;
    } else {
        float x = d - (Line.Width - 1);
        mixVal = exp2(-2.0 * (x*x));
    }
	mixVal=0.0;
    
	
	vec3 ambAndDiff, spec;
	phongModel(ambAndDiff,spec);
	vec4 texColor = texture(RenderTex,GTexCoord);
	//FragColor = mix( vec4(phongModel(), 1.0), Line.Color, mixVal );
	return vec4(ambAndDiff, 1.0) * texColor + vec4(spec, 1.0);
	//FragColor = texColor;
	//FragColor = mix( texColor, Line.Color, mixVal );
}

float luminance( vec3 color ) {
    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

subroutine( RenderPassType )
vec4 pass2()
{
    float dx = 1.0 / 960.0;
    float dy = 1.0 / 540.0;

    float s00 = luminance(texture( RenderTex, GTexCoord + vec2(-dx,dy) ).rgb);
    float s10 = luminance(texture( RenderTex, GTexCoord + vec2(-dx,0.0) ).rgb);
    float s20 = luminance(texture( RenderTex, GTexCoord + vec2(-dx,-dy) ).rgb);
    float s01 = luminance(texture( RenderTex, GTexCoord + vec2(0.0,dy) ).rgb);
    float s21 = luminance(texture( RenderTex, GTexCoord + vec2(0.0,-dy) ).rgb);
    float s02 = luminance(texture( RenderTex, GTexCoord + vec2(dx, dy) ).rgb);
    float s12 = luminance(texture( RenderTex, GTexCoord + vec2(dx, 0.0) ).rgb);
    float s22 = luminance(texture( RenderTex, GTexCoord + vec2(dx, -dy) ).rgb);

    float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
    float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);

    float dist = sx * sx + sy * sy;
	float EdgeThreshold = 0.1;

    if( dist > EdgeThreshold )
        return vec4(1.0);
    else
        return vec4(0.0,0.0,0.0,1.0);
}

void main() {
	FragColor = RenderPass();
}
