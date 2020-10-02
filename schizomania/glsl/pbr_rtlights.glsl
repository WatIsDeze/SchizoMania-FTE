!!ver 100 150
!!permu TESS
!!permu BUMP
!!permu FRAMEBLEND
!!permu SKELETAL
!!permu UPPERLOWER
!!permu FOG
!!permu REFLECTCUBEMASK
!!cvarf r_glsl_offsetmapping_scale
!!cvardf r_glsl_pcf
!!cvardf r_tessellation_level=5
!!cvardf r_glsl_fresnel
!!samps shadowmap diffuse normalmap specular upper lower reflectcube reflectmask projectionmap

#include "sys/defs.h"

#define SPECULAR

//this is the main shader responsible for realtime dlights.

//texture units:
//s0=diffuse, s1=normal, s2=specular, s3=shadowmap
//custom modifiers:
//PCF(shadowmap)
//CUBEPROJ(projected cubemap)
//SPOT(projected circle
//CUBESHADOW

#if 0 && defined(GL_ARB_texture_gather) && defined(PCF) 
#extension GL_ARB_texture_gather : enable
#endif

#ifdef UPPERLOWER
#define UPPER
#define LOWER
#endif

//if there's no vertex normals known, disable some stuff.
//FIXME: this results in dupe permutations.
#ifdef NOBUMP
#undef SPECULAR
#undef BUMP
#undef OFFSETMAPPING
#endif

#if !defined(TESS_CONTROL_SHADER)
	varying vec2 tcbase;
	varying vec3 lightvector;
	#if defined(VERTEXCOLOURS)
		varying vec4 vc;
	#endif
	#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
		varying vec3 eyevector;
	#endif
	#ifdef REFLECTCUBEMASK
		varying mat3 invsurface;
	#endif
	#if defined(PCF) || defined(CUBE) || defined(SPOT)
		varying vec4 vtexprojcoord;
	#endif
#endif


#ifdef VERTEX_SHADER
#ifdef TESS
varying vec3 vertex, normal;
#endif
#include "sys/skeletal.h"
void main ()
{
	vec3 n, s, t, w;
	gl_Position = skeletaltransform_wnst(w,n,s,t);
	tcbase = v_texcoord;	//pass the texture coords straight through
	vec3 lightminusvertex = l_lightposition - w.xyz;
#ifdef NOBUMP
	//the only important thing is distance
	lightvector = lightminusvertex;
#else
	//the light direction relative to the surface normal, for bumpmapping.
	lightvector.x = dot(lightminusvertex, s.xyz);
	lightvector.y = dot(lightminusvertex, t.xyz);
	lightvector.z = dot(lightminusvertex, n.xyz);
#endif
#if defined(VERTEXCOLOURS)
	vc = v_colour;
#endif
#if defined(SPECULAR)||defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	vec3 eyeminusvertex = e_eyepos - w.xyz;
	eyevector.x = dot(eyeminusvertex, s.xyz);
	eyevector.y = dot(eyeminusvertex, t.xyz);
	eyevector.z = dot(eyeminusvertex, n.xyz);
#endif
#ifdef REFLECTCUBEMASK
	invsurface[0] = v_svector;
	invsurface[1] = v_tvector;
	invsurface[2] = v_normal;
#endif
#if defined(PCF) || defined(SPOT) || defined(CUBE)
	//for texture projections/shadowmapping on dlights
	vtexprojcoord = (l_cubematrix*vec4(w.xyz, 1.0));
#endif

#ifdef TESS
	vertex = w;
	normal = n;
#endif
}
#endif






#if defined(TESS_CONTROL_SHADER)
layout(vertices = 3) out;

in vec3 vertex[];
out vec3 t_vertex[];
in vec3 normal[];
out vec3 t_normal[];
in vec2 tcbase[];
out vec2 t_tcbase[];
in vec3 lightvector[];
out vec3 t_lightvector[];
#if defined(VERTEXCOLOURS)
in vec4 vc[];
out vec4 t_vc[];
#endif
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
in vec3 eyevector[];
out vec3 t_eyevector[];
#endif
void main()
{
	//the control shader needs to pass stuff through
#define id gl_InvocationID
	t_vertex[id] = vertex[id];
	t_normal[id] = normal[id];
	t_tcbase[id] = tcbase[id];
	t_lightvector[id] = lightvector[id];
#if defined(VERTEXCOLOURS)
	t_vc[id] = vc[id];
#endif
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	t_eyevector[id] = eyevector[id];
#endif

	gl_TessLevelOuter[0] = float(r_tessellation_level);
	gl_TessLevelOuter[1] = float(r_tessellation_level);
	gl_TessLevelOuter[2] = float(r_tessellation_level);
	gl_TessLevelInner[0] = float(r_tessellation_level);
}
#endif









#if defined(TESS_EVALUATION_SHADER)
layout(triangles) in;

in vec3 t_vertex[];
in vec3 t_normal[];
in vec2 t_tcbase[];
in vec3 t_lightvector[];
#if defined(VERTEXCOLOURS)
in vec4 t_vc[];
#endif
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
in vec3 t_eyevector[];
#endif

#define LERP(a) (gl_TessCoord.x*a[0] + gl_TessCoord.y*a[1] + gl_TessCoord.z*a[2])
void main()
{
#define factor 1.0
	tcbase = LERP(t_tcbase);
	vec3 w = LERP(t_vertex);

	vec3 t0 = w - dot(w-t_vertex[0],t_normal[0])*t_normal[0];
	vec3 t1 = w - dot(w-t_vertex[1],t_normal[1])*t_normal[1];
	vec3 t2 = w - dot(w-t_vertex[2],t_normal[2])*t_normal[2];
	w = w*(1.0-factor) + factor*(gl_TessCoord.x*t0+gl_TessCoord.y*t1+gl_TessCoord.z*t2);

#if defined(PCF) || defined(SPOT) || defined(CUBE)
	//for texture projections/shadowmapping on dlights
	vtexprojcoord = (l_cubematrix*vec4(w.xyz, 1.0));
#endif

	//FIXME: we should be recalcing these here, instead of just lerping them
	lightvector = LERP(t_lightvector);
#if defined(VERTEXCOLOURS)
	vc = LERP(t_vc);
#endif
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	eyevector = LERP(t_eyevector);
#endif

	gl_Position = m_modelviewprojection * vec4(w,1.0);
}
#endif











#ifdef FRAGMENT_SHADER

vec3 LightingFuncShlick(vec3 N, vec3 V, vec3 L, float roughness, vec3 Cdiff, vec3 F0)
{
	vec3 H = normalize(V+L);
	float NL = clamp(dot(N,L), 0.001, 1.0);
	float LH = clamp(dot(L,H), 0.0, 1.0);
	float NH = clamp(dot(N,H), 0.0, 1.0);
	float NV = clamp(abs(dot(N,V)), 0.001, 1.0);
	float VH = clamp(dot(V,H), 0.0, 1.0);
	float PI = 3.14159f;

	//Fresnel term
	//the fresnel models glancing light.
	//(Schlick)
	vec3 F = F0 + (1.0-F0)*pow(1.0-VH, 5.0);

	//Schlick
	float k = roughness*0.79788456080286535587989211986876;
	float G = (LH/(LH*(1.0-k)+k)) * (NH/(NH*(1.0-k)+k));

	//microfacet distribution
	float a = roughness*roughness;
	a *= a;
	float t = (NH*NH*(a-1.0)+1.0);

	float D = a/(PI*t*t);

	if (r_glsl_fresnel == 1)
		return vec3(F);
	if (r_glsl_fresnel == 2)
		return vec3(G);
	if (r_glsl_fresnel == 3)
		return vec3(D);

	return ((1.0-F)*(Cdiff/PI) + 
		  (F*G*D)/(4*NL*NV)) * NL;
}

//This is copyright by John Hable, but licensed as public domain.
vec3 LightingFuncGGX(vec3 N, vec3 V, vec3 L, float roughness, vec3 F0)
{
	float alpha = roughness*roughness;

	vec3 H = normalize(V+L);

	float dotNL = clamp(dot(N,L), 0.0, 1.0);
	float dotLH = clamp(dot(L,H), 0.0, 1.0);
	float dotNH = clamp(dot(N,H), 0.0, 1.0);

	float D, vis;

	// D
	float alphaSqr = alpha*alpha;
	float pi = 3.14159f;
	float denom = dotNH * dotNH *(alphaSqr-1.0) + 1.0f;
	D = alphaSqr/(pi * denom * denom);

	// F
	float dotLH5 = pow(1.0f-dotLH,5);
	vec3 F = F0 + (1.0-F0)*(dotLH5);

	// V
	float k = alpha/2.0f;
	float k2 = k*k;
	float invK2 = 1.0f-k2;
	vis = 1.0/(dotLH*dotLH*invK2 + k2);

	vec3 specular = dotNL * D * F * vis;
	return specular;
}



#include "sys/fog.h"
#include "sys/pcf.h"
#ifdef OFFSETMAPPING
#include "sys/offsetmapping.h"
#endif

void main ()
{
#ifdef ORTHO
	float colorscale = 1.0;
#else
	float colorscale = max(1.0 - (dot(lightvector, lightvector)/(l_lightradius*l_lightradius)), 0.0);
#endif
#ifdef PCF
	/*filter the light by the shadowmap. logically a boolean, but we allow fractions for softer shadows*/
	colorscale *= ShadowmapFilter(s_shadowmap, vtexprojcoord);
#endif
#if defined(SPOT)
	/*filter the colour by the spotlight. discard anything behind the light so we don't get a mirror image*/
	if (vtexprojcoord.w < 0.0) discard;
	vec2 spot = ((vtexprojcoord.st)/vtexprojcoord.w);
	colorscale*=1.0-(dot(spot,spot));
#endif

	if (colorscale > 0)
	{

//read raw texture samples (offsetmapping munges the tex coords first)
#ifdef OFFSETMAPPING
	vec2 tcoffsetmap = offsetmap(s_normalmap, tcbase, eyevector);
#define tcbase tcoffsetmap
#endif
#if defined(FLAT)
	vec4 bases = vec4(FLAT, FLAT, FLAT, 1.0);
#else
	vec4 bases = texture2D(s_diffuse, tcbase);
	#ifdef VERTEXCOLOURS
		bases.rgb *= bases.a;
	#endif
#endif
#ifdef UPPER
	vec4 uc = texture2D(s_upper, tcbase);
	bases.rgb += uc.rgb*e_uppercolour*uc.a;
#endif
#ifdef LOWER
	vec4 lc = texture2D(s_lower, tcbase);
	bases.rgb += lc.rgb*e_lowercolour*lc.a;
#endif
#if defined(BUMP) || defined(SPECULAR) || defined(REFLECTCUBEMASK)
	vec3 bumps = normalize(vec3(texture2D(s_normalmap, tcbase)) - 0.5);
#elif defined(REFLECTCUBEMASK)
	vec3 bumps = vec3(0.0,0.0,1.0);
#endif
#ifdef SPECULAR
	vec4 specs = texture2D(s_specular, tcbase);
#endif

	vec3 diff;
#ifdef NOBUMP
	//surface can only support ambient lighting, even for lights that try to avoid it.
	diff = bases.rgb * (l_lightcolourscale.x+l_lightcolourscale.y);
#else
	vec3 nl = normalize(lightvector);
	#ifdef BUMP
		diff = bases.rgb * (l_lightcolourscale.x + l_lightcolourscale.y * max(dot(bumps, nl), 0.0));
	#else
		//we still do bumpmapping even without bumps to ensure colours are always sane. light.exe does it too.
		diff = bases.rgb * (l_lightcolourscale.x + l_lightcolourscale.y * max(dot(vec3(0.0, 0.0, 1.0), nl), 0.0));
	#endif
#endif

#if 1//PBR
	#if 0//PBR_ORM
		const vec3 dielectricSpecular = vec3(0.04, 0.04, 0.04);
		const vec3 black = vec3(0.0, 0.0, 0.0);
		vec3 F0 = mix(dielectricSpecular, bases.rgb, specs.b);
		bases.rgb = mix(bases.rgb * (1.0 - dielectricSpecular.r), black, specs.b);
		float	roughness = specs.g;
	#else
		vec3 F0 = specs.rgb;
		bases.rgb = bases.rgb * (1.0 - max(max(specs.r, specs.g), specs.b));
		float	roughness = 1.0-specs.a;
	#endif

	if (r_glsl_fresnel >= 4 && r_glsl_fresnel <= 5)
		roughness = r_glsl_fresnel;
	diff = LightingFuncShlick(bumps, normalize(eyevector), nl, roughness, bases.rgb, F0);
//	diff *= specs.r;

#elif defined(SPECULAR)
	vec3 halfdir = normalize(normalize(eyevector) + nl);
	float spec = pow(max(dot(halfdir, bumps), 0.0), FTE_SPECULAR_EXPONENT * specs.a)*float(SPECMUL);
	diff += l_lightcolourscale.z * spec;// * bases.rgb;
#endif

#ifdef REFLECTCUBEMASK
	vec3 rtc = reflect(-eyevector, bumps);
	rtc = rtc.x*invsurface[0] + rtc.y*invsurface[1] + rtc.z*invsurface[2];
	rtc = (m_model * vec4(rtc.xyz,0.0)).xyz;
	diff += texture2D(s_reflectmask, tcbase).rgb * textureCube(s_reflectcube, rtc).rgb;
#endif

#ifdef CUBE
	/*filter the colour by the cubemap projection*/
	diff *= textureCube(s_projectionmap, vtexprojcoord.xyz).rgb;
#endif

#if defined(PROJECTION)
	/*2d projection, not used*/
//	diff *= texture2d(s_projectionmap, shadowcoord);
#endif
#if defined(VERTEXCOLOURS)
	diff *= vc.rgb * vc.a;
#endif

	gl_FragColor.rgb = fog3additive(diff*colorscale*l_lightcolour);
	}
	else
		gl_FragColor.rgb = vec3(0.0);
}
#endif

