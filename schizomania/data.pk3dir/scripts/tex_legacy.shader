// THIS FILE HAS BEEN AUTOMATICALLY GENERATED!
// Please refer to the original documentation.
// This is for development purposes ONLY.

textures/data.pk3dir/textures/common/cushion
{
    diffusemap textures/common/cushion.tga
    {
        qer_nocarve
        qer_trans 0.50
        surfaceparm nodraw
        surfaceparm nolightmap
        surfaceparm trans
        surfaceparm nomarks
        surfaceparm nodamage
    }
}
textures/data.pk3dir/textures/common/donotenter
{
    diffusemap textures/common/donotenter.tga
    {
        qer_trans 0.50
        surfaceparm nodraw
        surfaceparm nonsolid
        surfaceparm trans
        surfaceparm nomarks
        surfaceparm donotenter
    }
}
textures/data.pk3dir/textures/common/areaportal
{
    diffusemap textures/common/areaportal.tga
    {
        qer_trans 0.50
        surfaceparm nodraw
        surfaceparm nolightmap
        surfaceparm nonsolid
        surfaceparm structural
        surfaceparm trans
        surfaceparm nomarks
        surfaceparm areaportal
    }
}
textures/data.pk3dir/textures/common/origin
{
    diffusemap textures/common/origin.tga
    {
        qer_nocarve
        surfaceparm nodraw
        surfaceparm nolightmap
        surfaceparm nonsolid
        surfaceparm trans
        surfaceparm origin
    }
}
textures/data.pk3dir/textures/common/hint
{
    diffusemap textures/common/hint.tga // should NOT use surfaceparm hint.. strange but true
    {
        qer_nocarve
        qer_trans 0.30
        surfaceparm nodraw
        surfaceparm nonsolid
        surfaceparm structural
        surfaceparm trans
        surfaceparm noimpact
        surfaceparm hint	// ydnar: yes it should.
    }
}
textures/data.pk3dir/textures/common/clip
{
    diffusemap textures/common/clip.tga
    {
        qer_trans 0.40
        surfaceparm nodraw
        surfaceparm nolightmap
        surfaceparm nonsolid
        surfaceparm trans
        surfaceparm nomarks
        surfaceparm noimpact
        surfaceparm playerclip
    }
}
textures/data.pk3dir/textures/common/caulk
{
    diffusemap textures/common/caulk.tga
    {
        surfaceparm nodraw
        surfaceparm nolightmap
        surfaceparm nomarks
    }
}
textures/data.pk3dir/textures/common/trigger
{
    diffusemap textures/common/trigger.tga
    {
        qer_trans 0.50
        qer_nocarve
        surfaceparm nodraw
    }
}
textures/data.pk3dir/textures/common/full_clip
{
    diffusemap textures/common/full_clip.tga // silly shader, use weapclip instead
    {
        qer_trans 0.40
        surfaceparm nodraw
        surfaceparm playerclip
    }
}
textures/data.pk3dir/textures/common/clusterportal
{
    diffusemap textures/common/clusterportal.tga
    {
        qer_trans 0.50
        surfaceparm nodraw
        surfaceparm nolightmap
        surfaceparm nonsolid
        surfaceparm trans
        surfaceparm nomarks
        surfaceparm clusterportal
    }
}
textures/data.pk3dir/textures/skies/smudge
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

textures/data.pk3dir/textures/edit/edit_5
{
	diffusemap textures/edit/edit_5.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/data.pk3dir/textures/edit/base_1
{
	diffusemap textures/edit/base_1.tga
	{
		map $diffuse
		map $lightmap
	}
}

textures/data.pk3dir/textures/edit/edit_4
{
	diffusemap textures/edit/edit_4.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/data.pk3dir/textures/edit/edit_3
{
	diffusemap textures/edit/edit_3.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/data.pk3dir/textures/edit/edit_1
{
	diffusemap textures/edit/edit_1.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/data.pk3dir/textures/edit/base_2
{
	diffusemap textures/edit/base_2.tga
	{
		map $diffuse
		map $lightmap
	}
}

textures/data.pk3dir/textures/edit/edit_6
{
	diffusemap textures/edit/edit_6.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/data.pk3dir/textures/edit/edit_2
{
	diffusemap textures/edit/edit_2.tga
	{
		map $diffuse
		map $lightmap
	}
}
textures/data.pk3dir/textures/sky/sky_normal
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
textures/data.pk3dir/textures/sky/sky
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

