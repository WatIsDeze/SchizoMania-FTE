!!ver 100 150
!!permu TESS
!!permu FULLBRIGHT
!!permu UPPERLOWER
!!permu FRAMEBLEND
!!permu SKELETAL
!!permu FOG
!!permu BUMP
!!permu REFLECTCUBEMASK
!!cvarf r_glsl_offsetmapping_scale
!!cvarf gl_specular
!!cvardf gl_affinemodels=0
!!cvardf r_tessellation_level=5
!!samps diffuse normalmap specular fullbright upper lower paletted reflectmask reflectcube

#include "sys/defs.h"

//standard shader used for models.
//must support skeletal and 2-way vertex blending or Bad Things Will Happen.
//the vertex shader is responsible for calculating lighting values.

#if gl_affinemodels==1 && __VERSION__ >= 130
#define affine noperspective
#else
#define affine
#endif


//#define PBR_SPEC
#define PBR_METAL

//'standard' physically-based rendering has two kinds of texture.
//metal: spec.r=occlusion, spec.g=roughness, spec.b=metalicity, spec.a=unused, 
//spec: spec.rgb=f0, spec.a=1-roughness. fb.a=ambient occlusion
//we don't support occlusion with the specular pathway.
#if defined(PBR_METAL) || defined(PBR_SPEC)
	#define PBR
#endif




#ifdef VERTEX_SHADER
#include "sys/skeletal.h"

affine varying vec2 tc;
#ifdef PBR
	varying vec3 lightvector;
#else
	varying vec3 light;
#endif
#if defined(PBR) || defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	varying vec3 eyevector;
#endif
#ifdef REFLECTCUBEMASK
	varying mat3 invsurface;
#endif
#ifdef TESS
	varying vec3 vertex;
#endif
#if defined(TESS) || defined(PBR)
	varying vec3 normal;
#endif

void main ()
{
	vec3 n, s, t, w;
	gl_Position = skeletaltransform_wnst(w,n,s,t);
#if defined(SPECULAR)||defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	vec3 eyeminusvertex = e_eyepos - w.xyz;
	eyevector.x = dot(eyeminusvertex, s.xyz);
	eyevector.y = dot(eyeminusvertex, t.xyz);
	eyevector.z = dot(eyeminusvertex, n.xyz);
#endif
#ifdef REFLECTCUBEMASK
	invsurface[0] = s;
	invsurface[1] = t;
	invsurface[2] = n;
#endif

	tc = v_texcoord;

#ifdef PBR
	lightvector.x = dot(e_light_dir, s.xyz);
	lightvector.y = dot(e_light_dir, t.xyz);
	lightvector.z = dot(e_light_dir, n.xyz);
	normal = n;
#else
	float d = dot(n,e_light_dir);
	if (d < 0.0)		//vertex shader. this might get ugly, but I don't really want to make it per vertex.
		d = 0.0;	//this avoids the dark side going below the ambient level.
	light = e_light_ambient + (d*e_light_mul);
#endif

//FIXME: Software rendering imitation should possibly push out normals by half a pixel or something to approximate software's over-estimation of distant model sizes (small models are drawn using JUST their verticies using the nearest pixel, which results in larger meshes)

#ifdef TESS
	normal = n;
	vertex = w;
#endif
}
#endif










#if defined(TESS_CONTROL_SHADER)
layout(vertices = 3) out;

in vec3 vertex[];
out vec3 t_vertex[];
in vec3 normal[];
out vec3 t_normal[];
affine in vec2 tc[];
affine out vec2 t_tc[];
in vec3 light[];
out vec3 t_light[];
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
in vec3 eyevector[];
out vec3 t_eyevector[];
#endif
#ifdef REFLECTCUBEMASK
in mat3 invsurface[];
out mat3 t_invsurface[];
#endif
void main()
{
	//the control shader needs to pass stuff through
#define id gl_InvocationID
	t_vertex[id] = vertex[id];
	t_normal[id] = normal[id];
	t_tc[id] = tc[id];
	t_light[id] = light[id];
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	t_eyevector[id] = eyevector[id];
#endif
#ifdef REFLECTCUBEMASK
	t_invsurface[id][0] = invsurface[id][0];
	t_invsurface[id][1] = invsurface[id][1];
	t_invsurface[id][2] = invsurface[id][2];
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
affine in vec2 t_tc[];
affine out vec2 tc;
in vec3 t_light[];
out vec3 light;
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
in vec3 t_eyevector[];
out vec3 eyevector;
#endif
#ifdef REFLECTCUBEMASK
in mat3 t_invsurface[];
out mat3 invsurface;
#endif

#define LERP(a) (gl_TessCoord.x*a[0] + gl_TessCoord.y*a[1] + gl_TessCoord.z*a[2])
void main()
{
#define factor 1.0
	tc = LERP(t_tc);
	vec3 w = LERP(t_vertex);

	vec3 t0 = w - dot(w-t_vertex[0],t_normal[0])*t_normal[0];
	vec3 t1 = w - dot(w-t_vertex[1],t_normal[1])*t_normal[1];
	vec3 t2 = w - dot(w-t_vertex[2],t_normal[2])*t_normal[2];
	w = w*(1.0-factor) + factor*(gl_TessCoord.x*t0+gl_TessCoord.y*t1+gl_TessCoord.z*t2);

	//FIXME: we should be recalcing these here, instead of just lerping them
	light = LERP(t_light);
#if defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	eyevector = LERP(t_eyevector);
#endif
#ifdef REFLECTCUBEMASK
	invsurface[0] = LERP(t_invsurface[0]);
	invsurface[1] = LERP(t_invsurface[1]);
	invsurface[2] = LERP(t_invsurface[2]);
#endif

	gl_Position = m_modelviewprojection * vec4(w,1.0);
}
#endif










#ifdef FRAGMENT_SHADER

#include "sys/fog.h"

#if defined(SPECULAR)
uniform float cvar_gl_specular;
#endif

#ifdef OFFSETMAPPING
#include "sys/offsetmapping.h"
#endif

#ifdef EIGHTBIT
#define s_colourmap s_t0
uniform sampler2D s_colourmap;
#endif

affine varying vec2 tc;
varying vec3 lightvector;
varying vec3 light;
#if defined(PBR) || defined(SPECULAR) || defined(OFFSETMAPPING) || defined(REFLECTCUBEMASK)
	varying vec3 eyevector;
#endif
#ifdef REFLECTCUBEMASK
	varying mat3 invsurface;
#endif


vec3 LightingFuncShlick(vec3 N, vec3 V, vec3 L, float roughness, vec3 Cdiff, vec3 F0)
{
	vec3 H = normalize(V+L);
	float NL = clamp(dot(N,L), 0.001, 1.0);
	float LH = clamp(dot(L,H), 0.0, 1.0);
	float NH = clamp(dot(N,H), 0.0, 1.0);
	float NV = clamp(abs(dot(N,V)), 0.001, 1.0);
	float VH = clamp(dot(V,H), 0.0, 1.0);
	float PI = 3.14159f;

	//Fresnel Schlick
	vec3 F = F0 + (1.0-F0)*pow(1.0-VH, 5.0);

	//Schlick
	float k = roughness*0.79788456080286535587989211986876;
	float G = (LH/(LH*(1.0-k)+k)) * (NH/(NH*(1.0-k)+k));

	float a = roughness*roughness;
	a *= a;
	float t = (NH*NH*(a-1.0)+1.0);
	float D = a/(PI*t*t);

/*	if (r_glsl_fresnel == 1)
		return vec3(F);
	if (r_glsl_fresnel == 2)
		return vec3(G);
	if (r_glsl_fresnel == 3)
		return vec3(D);
*/
	return ((1.0-F)*(Cdiff/PI) + 
		  (F*G*D)/(4*NL*NV)*NL);
}

//This is copyright by John Hable, but licensed as public domain.
vec3 LightingFuncGGX(vec3 N, vec3 V, vec3 L, float roughness, vec3 diffuse, vec3 F0)
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

	return (1.0+dotNL)*0.5 * (diffuse + (D * F * vis)) ;
}


void main ()
{
	vec4 col, sp;

#ifdef OFFSETMAPPING
	vec2 tcoffsetmap = offsetmap(s_normalmap, tc, eyevector);
#define tc tcoffsetmap
#endif

#ifdef EIGHTBIT
	vec3 lightlev = light;
	//FIXME: with this extra flag, half the permutations are redundant.
	lightlev *= 0.5;	//counter the fact that the colourmap contains overbright values and logically ranges from 0 to 2 intead of to 1.
	float pal = texture2D(s_paletted, tc).r;	//the palette index. hopefully not interpolated.
//	lightlev -= 1.0 / 128.0;	//software rendering appears to round down, so make sure we favour the lower values instead of rounding to the nearest
	col.r = texture2D(s_colourmap, vec2(pal, 1.0-lightlev.r)).r;	//do 3 lookups. this is to cope with lit files, would be a waste to not support those.
	col.g = texture2D(s_colourmap, vec2(pal, 1.0-lightlev.g)).g;	//its not very softwarey, but re-palettizing is ugly.
	col.b = texture2D(s_colourmap, vec2(pal, 1.0-lightlev.b)).b;	//without lits, it should be identical.
	col.a = (pal<1.0)?1.0:0.0;
#else
	col = texture2D(s_diffuse, tc);
	#ifdef UPPER
		vec4 uc = texture2D(s_upper, tc);
		col.rgb += uc.rgb*e_uppercolour*uc.a;
	#endif
	#ifdef LOWER
		vec4 lc = texture2D(s_lower, tc);
		col.rgb += lc.rgb*e_lowercolour*lc.a;
	#endif

	#ifdef PBR
		#if defined(BUMP)
			vec3 bumps = normalize(vec3(texture2D(s_normalmap, tc)) - 0.5);
		#else
			vec3 bumps = vec3(0.0, 0.0, 1.0);
		#endif
		#if defined(SPECULAR)
			vec4 specs = texture2D(s_specular, tc);
		#else
			vec4 specs = vec4(1.0, 1.0, 1.0, 1.0);	//occlusion, metalness, roughness
		#endif

		#ifdef PBR_SPEC
			vec3 F0 = specs.rgb;
			float	roughness = specs.a;
		#else //PBR_METAL
			const vec3 dielectricSpecular = vec3(0.04, 0.04, 0.04);	//non-metals have little specular (but they do have some)
			const vec3 black = vec3(0, 0, 0);					//pure metals are asumed to be pure specular

			vec3 F0 = mix(dielectricSpecular, col.rgb, specs.b);
			col.rgb = mix(col.rgb * (1.0 - dielectricSpecular.r), black, specs.b);
			float	roughness = 1.0-specs.g;
		#endif

		vec3 nl = normalize(lightvector);
		col.rgb = LightingFuncShlick(bumps, normalize(eyevector), nl, roughness, col.rgb, F0);
//		col.rgb = eyevector;//vec3(dot(nl, bumps));
//col.rgb = vec3(0);
col.rgb = vec3(dot(nl, bumps));
//col.rgb = texture2D(s_normalmap, tc).rgb;//vec3(dot(eyevector, bumps));
	#elif defined(BUMP) && defined(SPECULAR)
		vec3 bumps = normalize(vec3(texture2D(s_normalmap, tc)) - 0.5);
		vec4 specs = texture2D(s_specular, tc);

		vec3 halfdir = normalize(normalize(eyevector) + vec3(0.0, 0.0, 1.0));
		float spec = pow(max(dot(halfdir, bumps), 0.0), FTE_SPECULAR_EXPONENT * specs.a);
		col.rgb += FTE_SPECULAR_MULTIPLIER * spec * specs.rgb;
	#elif defined(REFLECTCUBEMASK)
		vec3 bumps = vec3(0, 0, 1);
	#endif

	#ifdef REFLECTCUBEMASK
		vec3 rtc = reflect(-eyevector, bumps);
		rtc = rtc.x*invsurface[0] + rtc.y*invsurface[1] + rtc.z*invsurface[2];
		rtc = (m_model * vec4(rtc.xyz,0.0)).xyz;
		col.rgb += texture2D(s_reflectmask, tc).rgb * textureCube(s_reflectcube, rtc).rgb;
	#endif

//	col.rgb *= light;

	#ifdef PBR_METAL
//		col.rgb *= specs.r;	//ambient occlusion
	#endif
	#ifdef FULLBRIGHT
		vec4 fb = texture2D(s_fullbright, tc);
		#ifdef PBR_SPEC
			col.rgb *= fb.a;	//ambient occlusion
			col.rgb += fb.rgb * e_glowmod.rgb;
		#else
//			col.rgb = mix(col.rgb, fb.rgb, fb.a);
			col.rgb += fb.rgb * fb.a * e_glowmod.rgb;
		#endif
	#endif
#endif

	gl_FragColor = fog4(col * e_colourident);
}
#endif

