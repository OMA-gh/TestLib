#version 400

in vec3 GPosition;
in vec3 GNormal;
in vec3 GColor;
in vec2 GTexCoord;
in vec4 GShadowCoord;
noperspective in vec3 GEdgeDistance;

uniform sampler2D RenderTex;
uniform sampler2DShadow ShadowMap;

subroutine void RenderPassType();
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

void phongModel(out vec3 outAmb, out vec3 outDiff,out vec3 outSpec){
    vec3 s = normalize(vec3(Light.Position) - GPosition);
	float light_dist = length(vec3(Light.Position)-GPosition);
	vec3 v = normalize(-GPosition.xyz);
	vec3 r = reflect( -s, GNormal);
	vec3 ambient = Light.La * Material.Ka;
	float sDotN = max(dot(s,GNormal),0.0);
	vec3 diffuse = Light.Ld * Material.Kd * GColor * sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN>0.0){
		spec = Light.Ls * Material.Ks * pow( max( dot(r,v), 0.0), Material.Shininess);
	}
	
	outAmb = ambient;
	outDiff = diffuse;
	outSpec = spec;
}

subroutine (RenderPassType)
void pass1()
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
	//mixVal=0.0;
    
    float sum = 0;
    sum += textureProjOffset(ShadowMap,GShadowCoord,ivec2(-1, -1));
    sum += textureProjOffset(ShadowMap,GShadowCoord,ivec2(-1,  1));
    sum += textureProjOffset(ShadowMap,GShadowCoord,ivec2( 1,  1));
    sum += textureProjOffset(ShadowMap,GShadowCoord,ivec2( 1, -1));
    float shadow = sum*0.25;

	shadow = textureProj(ShadowMap,GShadowCoord);
	
	vec3 amb, diff, spec;
	phongModel(amb, diff,spec);
	vec4 texColor = texture(RenderTex,GTexCoord);
	
	//FragColor = vec4((diff+spec) + amb,1.0);
	//FragColor = vec4((diff+spec)*shadow + amb,1.0);
	FragColor = vec4((diff*shadow)+amb,1.0)*texColor + vec4(spec*shadow,1.0);
	//FragColor = vec4(1.0)*shadow;
	
	//FragColor = mix( vec4(phongModel(), 1.0), Line.Color, mixVal );
	//FragColor = vec4(amb+diff, 1.0) * texColor + vec4(spec, 1.0);
	//FragColor = texColor;
	//FragColor = mix( texColor, Line.Color, mixVal );
	//FragColor = mix( FragColor, Line.Color, mixVal );
}

float luminance( vec3 color ) {
    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

subroutine( RenderPassType )
void pass2()
{
	FragColor = texture( RenderTex, GTexCoord );
}

subroutine( RenderPassType )
void recordDepth()
{
    // Do nothing, depth will be written automatically
}

void main() {
	RenderPass();
}
