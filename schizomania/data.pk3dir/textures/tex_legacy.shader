// THIS FILE HAS BEEN AUTOMATICALLY GENERATED!
// Please refer to the original documentation.
// This is for development purposes ONLY.

textures/edit/edit_5
{
	diffusemap textures/edit/edit_5.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/edit/edit_4
{
	diffusemap textures/edit/edit_4.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/edit/edit_3
{
	diffusemap textures/edit/edit_3.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/edit/edit_1
{
	diffusemap textures/edit/edit_1.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/edit/edit_6
{
	diffusemap textures/edit/edit_6.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/edit/edit_2
{
	diffusemap textures/edit/edit_2.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/skies/smudge
{
	qer_editorImage textures/skies/smudge.tga
	skyParms - 256 -

	surfaceParm sky
	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm nodlight
	noPicMip
	nomipmaps
	{
		map $cube:textures/skies/smudge/bg
		map $blackimage
		map $blackimage
	}
}

textures/sky/sky_normal
{
q3map_lightmapFilterRadius 0 8
q3map_sunExt 5 6 8 450 315 90 3 32
q3map_skyLight 75 6
surfaceparm sky
surfaceparm noimpact
surfaceparm nolightmap
skyparms textures/sky/sky_normal.tga 512 -
nopicmip
nomipmaps
{
map textures/sky/sky_normall.tga
tcMod scroll 0.0015 -0.003
rgbGen identityLighting
}
}
textures/sky/sky
{
	qer_editorImage textures/skies/smudge.tga
	skyParms - 256 -

	surfaceParm sky
	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm nodlight
	noPicMip
	nomipmaps
	{
		map $cube:textures/skies/smudge/bg
		map $blackimage
		map $blackimage
	}
}

