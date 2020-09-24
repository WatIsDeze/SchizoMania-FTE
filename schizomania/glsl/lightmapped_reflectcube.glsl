//======= Copyright (c) 2015-2020 Vera Visions LLC. All rights reserved. =======
//
// Purpose: 
//
// Lightmapped surface that contains an environment cube as a reflection.
// Alpha channel of the diffuse decides reflectivity.
//==============================================================================

!!ver 110
!!permu FOG
!!permu BUMP
!!permu DELUXE
!!samps diffuse=0 normalmap=1 box:samplerCube=2 lightmap deluxemap

!!permu FAKESHADOWS
!!cvardf r_glsl_pcf
!!samps =FAKESHADOWS shadowmap

!!cvardf dev_skipnormal

#include "sys/defs.h"

varying vec2 tex_c;
varying vec3 eyevector;
varying mat3 invsurface;

varying vec2 lm0;
#ifdef LIGHTSTYLED
varying vec2 lm1, lm2, lm3;
#endif

#ifdef FAKESHADOWS
	varying vec4 vtexprojcoord;
#endif

#ifdef VERTEX_SHADER
	void lightmapped_init(void)
	{
		lm0 = v_lmcoord;
		#ifdef LIGHTSTYLED
		lm1 = v_lmcoord2;
		lm2 = v_lmcoord3;
		lm3 = v_lmcoord4;
		#endif
	}

	void main (void)
	{
		lightmapped_init();
		invsurface[0] = v_svector;
		invsurface[1] = v_tvector;
		invsurface[2] = v_normal;

		vec3 eyeminusvertex = e_eyepos - v_position.xyz;
		eyevector.x = dot(eyeminusvertex, v_svector.xyz);
		eyevector.y = dot(eyeminusvertex, v_tvector.xyz);
		eyevector.z = dot(eyeminusvertex, v_normal.xyz);

		tex_c = v_texcoord;
		gl_Position = ftetransform();
		
		#ifdef FAKESHADOWS
		vtexprojcoord = (l_cubematrix*vec4(v_position.xyz, 1.0));
		#endif
	}
#endif

#ifdef FRAGMENT_SHADER
	#include "sys/fog.h"
	#include "sys/pcf.h"

	vec3 lightmap_fragment (vec3 normal_f)
	{
		vec3 lightmaps;

#ifdef LIGHTSTYLED
		lightmaps  = texture2D(s_lightmap0, lm0).rgb * e_lmscale[0].rgb * dot(normal_f, (texture2D(s_deluxemap0, lm0).rgb - 0.5) * 2.0);
		lightmaps += texture2D(s_lightmap1, lm1).rgb * e_lmscale[1].rgb * dot(normal_f, (texture2D(s_deluxemap1, lm1).rgb - 0.5) * 2.0);
		lightmaps += texture2D(s_lightmap2, lm2).rgb * e_lmscale[2].rgb * dot(normal_f, (texture2D(s_deluxemap2, lm2).rgb - 0.5) * 2.0);
		lightmaps += texture2D(s_lightmap3, lm3).rgb * e_lmscale[3].rgb * dot(normal_f, (texture2D(s_deluxemap3, lm3).rgb - 0.5) * 2.0);
#else
		lightmaps  = texture2D(s_lightmap, lm0).rgb * e_lmscale.rgb * dot(normal_f, (texture2D(s_deluxemap, lm0).rgb - 0.5) * 2.0);
#endif
		return lightmaps;
	}

	void main (void)
	{
		vec3 cube_c;
		vec4 out_f = vec4(1.0, 1.0, 1.0, 1.0);
		vec4 diffuse_f = texture2D(s_t0, tex_c);
		vec3 normal_f = normalize(texture2D(s_normalmap, tex_c).rgb - 0.5);
		vec3 env_f;

		diffuse_f.rgb *= lightmap_fragment(normal_f);

		#ifdef FAKESHADOWS
		diffuse_f.rgb *= ShadowmapFilter(s_shadowmap, vtexprojcoord);
		#endif

		cube_c = reflect(normalize(-eyevector), normal_f.rgb);
		cube_c = cube_c.x * invsurface[0] + cube_c.y * invsurface[1] + cube_c.z * invsurface[2];
		cube_c = (m_model * vec4(cube_c.xyz, 0.0)).xyz;
		env_f = textureCube(s_box, cube_c).rgb * (e_lmscale.rgb * 0.25);
		out_f.rgb = mix(env_f, diffuse_f.rgb, diffuse_f.a);

		// Add fog to the final fragment
		gl_FragColor = fog4(out_f);
	}
#endif