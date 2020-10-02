// THIS FILE HAS BEEN AUTOMATICALLY GENERATED!
// Please refer to the original documentation.
// This is for development purposes ONLY.

textures/data.pk3dir/textures/measure/desk
{
	diffusemap textures/measure/desk.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/counter
{
	diffusemap textures/measure/counter.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall128b
{
	diffusemap textures/measure/wall128b.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall64a
{
	diffusemap textures/measure/wall64a.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/rail
{
	diffusemap textures/measure/rail.tga
}

textures/data.pk3dir/textures/measure/floor
{
	diffusemap textures/measure/floor.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall128
{
	diffusemap textures/measure/wall128.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/door
{
	diffusemap textures/measure/door.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall128pl
{
	diffusemap textures/measure/wall128pl.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall32
{
	diffusemap textures/measure/wall32.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/ceiling
{
	diffusemap textures/measure/ceiling.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/stairs1
{
	diffusemap textures/measure/stairs1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall128gr
{
	diffusemap textures/measure/wall128gr.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/ladder
{
	diffusemap textures/measure/ladder.tga
}

textures/data.pk3dir/textures/measure/wall64
{
	diffusemap textures/measure/wall64.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall128g
{
	diffusemap textures/measure/wall128g.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/measure/wall128_blend
{
	vmap_lightmapMergable
	qer_editorImage "textures/measure/wall128b.tga"
	polygonOffset 1

	{
		map "textures/measure/wall128.tga"
		map "textures/measure/wall128b.tga"
		map $whiteimage
		map $whiteimage
	}
}

textures/data.pk3dir/textures/measure/player
{
	diffusemap textures/measure/player.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/liquid/water1
{
	qer_editorImage "textures/liquid/water5.tga"
	sort banner
	qer_trans 0.8
	surfaceParm nonsolid
	surfaceParm trans
	surfaceParm water
	surfaceParm nodlight

	diffusemap "textures/liquid/water5.tga"
	{
		map $blackimage
		map $refraction
	}
}

textures/data.pk3dir/textures/liquid/water2
{
	qer_editorImage "textures/liquid/water2.tga"
	sort banner
	qer_trans 0.8
	surfaceParm nonsolid
	surfaceParm trans
	surfaceParm water
	surfaceParm nodlight

	{
		map $reflection
		map $refraction
		map "textures/liquid/water1_n.tga"
	}
}

textures/data.pk3dir/textures/dev/info_node_air
{
	diffusemap textures/dev/info_node_air.tga
	
	{
		map $diffuse
		blendFunc blend
	}
}

textures/data.pk3dir/textures/dev/info_node
{
	diffusemap textures/dev/info_node.tga
	
	{
		map $diffuse
		blendFunc blend
	}
}

textures/data.pk3dir/textures/dev/scripted_sequence
{
	diffusemap textures/dev/scripted_sequence.tga
	
	{
		map $diffuse
		blendFunc blend
	}
}

textures/data.pk3dir/textures/common/clipvehicle
{
	qer_editorImage "textures/common/clipvehicle.tga"
	qer_trans 0.50
	surfaceParm vehicleclip
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/hitmesh
{
	qer_editorImage "textures/common/hitmesh.tga"
	surfaceParm nolightmap
	surfaceParm nomarks
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm noimpact
	surfaceParm nodlight
	nomipmaps
}

textures/data.pk3dir/textures/common/clipglass
{
	qer_editorImage "textures/common/clip.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm glass
	nomipmaps
}

textures/data.pk3dir/textures/common/clipplayer
{
	qer_editorImage "textures/common/clipplayer.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm playerclip
	nomipmaps
}

textures/data.pk3dir/textures/common/lightgrid
{
	qer_editorImage "textures/common/lightgrid.tga"
	surfaceParm nodraw
	surfaceParm nolightmap
	surfaceParm nonsolid
	surfaceParm detail
	surfaceParm nomarks
	surfaceParm trans
	surfaceParm lightgrid
	nomipmaps
}

textures/data.pk3dir/textures/common/climb
{
	qer_editorImage "textures/common/climb.tga"
	qer_trans 0.50
	surfaceParm climb
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm nonsolid
	nomipmaps
}

textures/data.pk3dir/textures/common/skyportal
{
	qer_editorImage "textures/common/skyportal.tga"
	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm sky
	surfaceParm nodlight
	nomipmaps
	skyParms - 512 -
}

textures/data.pk3dir/textures/common/clipsnow
{
	qer_editorImage "textures/common/clip.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm snow
	nomipmaps
}

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
textures/data.pk3dir/textures/common/alpha_0
{
	qer_editorImage "textures/common/alpha_0.tga"
	vmap_alphaMod volume
	vmap_alphaMod set 0.0
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/skip
{
	qer_editorImage "textures/common/skip.tga"
	qer_trans 0.50
	qer_noCarve
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm structural
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/nodraw
{
	qer_editorImage "textures/common/nodraw.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	surfaceParm nomarks
	nomipmaps
}

textures/data.pk3dir/textures/common/alpha_25
{
	qer_editorImage "textures/common/alpha_25.tga"
	vmap_alphaMod volume
	vmap_alphaMod set 0.25
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/donotenter
{
	qer_editorImage "textures/common/donotenter.tga"
	qer_trans 0.50
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm detail
	surfaceparm donotenter
	nomipmaps
}

textures/data.pk3dir/textures/common/areaportal
{
	qer_editorImage "textures/common/areaportal.tga"
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm structural
	surfaceParm trans
	surfaceParm nomarks
	surfaceParm areaportal
}

textures/data.pk3dir/textures/common/caulkslime
{
	qer_editorImage "textures/common/caulkslime.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	surfaceParm slime
	nomipmaps
}

textures/data.pk3dir/textures/common/blank
{
	{
		map $whiteimage
		rgbGen vertex
		alphaGen vertex
	}
}

textures/data.pk3dir/textures/common/alpha_100
{
	qer_editorImage "textures/common/alpha_100.tga"
	vmap_alphaMod volume
	vmap_alphaMod set 1.0
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/origin
{
	qer_editorImage "textures/common/origin.tga"
	qer_trans 0.50
	qer_noCarve
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm origin
	nomipmaps
}

textures/data.pk3dir/textures/common/hint
{
	qer_editorImage "textures/common/hint.tga"
	qer_trans 0.50
	qer_noCarve	
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm structural
	surfaceParm trans
	surfaceParm noimpact
	nomipmaps
}

textures/data.pk3dir/textures/common/terrain
{
	qer_editorImage "textures/common/terrain.tga"
	vmap_terrain
	surfaceParm nodraw
	surfaceParm nomarks
	surfaceParm nolightmap
	nomipmaps
}

textures/data.pk3dir/textures/common/alpha_75
{
	qer_editorImage "textures/common/alpha_75.tga"
	vmap_alphaMod volume
	vmap_alphaMod set 0.75
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/caulkwater
{
	qer_editorImage "textures/common/caulkwater.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	surfaceParm water
	nomipmaps

	fogParms ( 0 0 0 ) 128
	surfaceParm fog
}

textures/data.pk3dir/textures/common/blocklight
{
	qer_editorImage "textures/common/blocklight.tga"
	surfaceParm nonsolid
	surfaceParm nomarks
	nomipmaps
}

textures/data.pk3dir/textures/common/clipdirt
{
	qer_editorImage "textures/common/clip.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm dirt
	nomipmaps
}

textures/data.pk3dir/textures/common/alpha_50
{
	qer_editorImage "textures/common/alpha_50.tga"
	vmap_alphaMod volume
	vmap_alphaMod set 0.5
	surfaceParm nodraw
	surfaceParm nonsolid
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/clip
{
	qer_editorImage "textures/common/clip.tga"
	surfaceParm nodraw
	surfaceParm trans
	nomipmaps
}

textures/data.pk3dir/textures/common/caulk
{
	qer_editorImage "textures/common/caulk.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm nomarks
	surfaceParm nolightmap
	nomipmaps
}

textures/data.pk3dir/textures/common/trigger
{
	qer_editorImage "textures/common/trigger.tga"
	qer_trans 0.50
	qer_noCarve
	surfaceParm nodraw
	nomipmaps
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
textures/data.pk3dir/textures/common/clipwood
{
	qer_editorImage "textures/common/clipwood.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm wood
	nomipmaps
}

textures/data.pk3dir/textures/common/terrain2
{
	qer_editorImage "textures/common/terrain.tga"
	vmap_terrain
	surfaceParm dust
	surfaceParm nodraw
	surfaceParm nomarks
	surfaceParm nolightmap
	nomipmaps
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
textures/data.pk3dir/textures/common/cliptile
{
	qer_editorImage "textures/common/clip.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm tile
	nomipmaps
}

textures/data.pk3dir/textures/common/rtsurface
{
	qer_editorImage "textures/common/rtsurface.tga"
	{
		map $rt:base
	}
}

textures/data.pk3dir/textures/common/clipmetal
{
	qer_editorImage "textures/common/clipmetal.tga"
	qer_trans 0.50
	surfaceParm nodraw
	surfaceParm trans
	surfaceParm metal
	nomipmaps
}

textures/data.pk3dir/textures/skies/ulukai
// SchizoMania Material
{
	qer_editorImage textures/skies/ulukai.tga
	skyParms textures/skies/ulukai/ulukai 1024 -
	vmap_globalTexture

	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm sky
	surfaceParm nodlight

	vmap_skylight 800 4
	//vmap_sunExt 1 0.084 0.084 140 -35 25 3 16
	nopicmip
	nomipmaps

	{
		map $cube:textures/skies/ulukai/ulukai
		map $blackimage
		map $blackimage
	}
}

textures/data.pk3dir/textures/skies/smudge
{
	qer_editorImage textures/skies/smudge.tga
	skyParms - 256 -
	vmap_globalTexture

	surfaceParm sky
	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm nodlight

	nopicmip
	nomipmaps

	{
		map $cube:textures/skies/smudge/bg
		map $blackimage
		map $blackimage
	}
}

textures/data.pk3dir/textures/skies/dune
{
	qer_editorImage textures/skies/dune.tga
	skyParms - 256 -
	vmap_globalTexture

	surfaceParm sky
	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm nodlight

	nopicmip
	nomipmaps

	{
		map $cube:textures/skies/dune_hdr/40th/bg
		map $cube:textures/skies/dune_hdr/250th/bg
		map $cube:textures/skies/dune_hdr/1600th/bg
		map textures/skies/clouds/dunecloud.tga
		map textures/skies/clouds/dunecloud_layer.tga
	}
}

textures/data.pk3dir/textures/skies/recotta
{
	qer_editorImage textures/skies/recotta.tga
	skyParms textures/skies/recotta/bg 256 -
	vmap_globalTexture

	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm sky
	surfaceParm nodlight

	vmap_skylight 800 4
	vmap_sunExt 1 0.084 0.084 140 -35 25 3 16
	nopicmip
	nomipmaps

	{
		map $cube:textures/skies/recotta/bg
		map textures/skies/clouds/dunecloud.tga
		map $blackimage
	}
}

textures/data.pk3dir/textures/skies/yukongold
{
	qer_editorImage textures/skies/yukongold.tga
	skyParms - 256 -
	vmap_globalTexture

	surfaceParm sky
	surfaceParm noimpact
	surfaceParm nolightmap
	surfaceParm nodlight

	nopicmip
	nomipmaps
	
	{
		map textures/skies/clouds/dustycloud.tga
		map $blackimage
		map $cube:textures/skies/yukongold/bg
		map $cube:textures/skies/yukongold/fg
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
textures/data.pk3dir/textures/scma/red_slate_roof_tiles_01
{
	diffusemap textures/scma/red_slate_roof_tiles_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/wall_01
{
	diffusemap textures/scma/wall_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/concrete2
{
	diffusemap textures/scma/concrete2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/light_01
{
	diffusemap textures/scma/light_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/door_rail
{
	diffusemap textures/scma/door_rail.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/floor_tiles_09
{
	diffusemap textures/scma/floor_tiles_09.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/tile01
{
	diffusemap textures/scma/tile01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/concrete3
{
	diffusemap textures/scma/concrete3.tga
	
	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/concrete6
{
	diffusemap textures/scma/concrete6.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/grass_02
{
	diffusemap textures/scma/grass_02.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/sand_01
{
	diffusemap textures/scma/sand_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/wall_03
{
	diffusemap textures/scma/wall_03.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/wall_01_bricks
{
	diffusemap textures/scma/wall_01_bricks.tga
	diffusemap textures/scma/wall_01_bricks_normal.tga
	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/tilesplain0119
{
	diffusemap textures/scma/tilesplain0119.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/wall_04
{
	diffusemap textures/scma/wall_04.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/step02
{
	diffusemap textures/scma/step02.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/floor_tiles_08
{
	diffusemap textures/scma/floor_tiles_08.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/wood_01
{
	diffusemap textures/scma/wood_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/woodfloor01
{
	diffusemap textures/scma/woodfloor01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/planks_dirty_greenish
{
	diffusemap textures/scma/planks_dirty_greenish.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/metal_a2
{
	diffusemap textures/scma/metal_a2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/step01
{
	diffusemap textures/scma/step01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/step03
{
	diffusemap textures/scma/step03.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/carpet_01
{
	diffusemap textures/scma/carpet_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/concrete1w
{
	diffusemap textures/scma/concrete1w.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/light-switch_01
{
	diffusemap textures/scma/light-switch_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/glass_01
{
	diffusemap textures/scma/glass_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/vent
{
	diffusemap textures/scma/vent.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/floor_tiles_06
{
	diffusemap textures/scma/floor_tiles_06.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/grass_01
{
	diffusemap textures/scma/grass_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/planks_dirty_blackish
{
	diffusemap textures/scma/planks_dirty_blackish.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/concrete4
{
	diffusemap textures/scma/concrete4.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/concrete5
{
	diffusemap textures/scma/concrete5.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/ceiling_01
{
	diffusemap textures/scma/ceiling_01.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/planks_blue
{
	diffusemap textures/scma/planks_blue.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/tile02
{
	diffusemap textures/scma/tile02.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/electrical-outlet
{
	diffusemap textures/scma/electrical-outlet.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/scma/door_texture_2
{
	diffusemap textures/scma/door_texture_2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/decals/puddle01
{
	surfaceParm nomarks
	surfaceParm nonsolid
	surfaceParm trans
	surfaceParm nodlight
	diffusemap textures/decals/puddle01.tga

	polygonOffset 1
	{
		blendFunc GL_ONE GL_ONE
	}
}

textures/data.pk3dir/textures/next/dirty3
{
	diffusemap textures/next/dirty3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker8
{
	diffusemap textures/next/bunker8.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/plywood4
{
	diffusemap textures/next/plywood4.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/plywood2
{
	diffusemap textures/next/plywood2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/dirty4
{
	diffusemap textures/next/dirty4.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker1
{
	diffusemap textures/next/bunker1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/asphalt1
{
	diffusemap textures/next/asphalt1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/rusty3
{
	diffusemap textures/next/rusty3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/tarmac2
{
	diffusemap textures/next/tarmac2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth1
{
	diffusemap textures/next/earth1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/vent5
{
	diffusemap textures/next/vent5.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/tarmac1
{
	diffusemap textures/next/tarmac1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker4
{
	diffusemap textures/next/bunker4.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/rusty6
{
	diffusemap textures/next/rusty6.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/vent2
{
	diffusemap textures/next/vent2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/rusty1
{
	diffusemap textures/next/rusty1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/plywood1
{
	diffusemap textures/next/plywood1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth6
{
	diffusemap textures/next/earth6.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker9
{
	diffusemap textures/next/bunker9.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/vent1
{
	diffusemap textures/next/vent1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/asphalt3
{
	diffusemap textures/next/asphalt3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker3
{
	diffusemap textures/next/bunker3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/rusty2
{
	diffusemap textures/next/rusty2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/dirty2
{
	diffusemap textures/next/dirty2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker2
{
	diffusemap textures/next/bunker2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth5
{
	diffusemap textures/next/earth5.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/vent4
{
	diffusemap textures/next/vent4.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker5
{
	diffusemap textures/next/bunker5.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth9
{
	diffusemap textures/next/earth9.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/dirty1
{
	diffusemap textures/next/dirty1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/asphalt2
{
	diffusemap textures/next/asphalt2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/plywood5
{
	diffusemap textures/next/plywood5.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/cracked1
{
	diffusemap textures/next/cracked1.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/rusty5
{
	diffusemap textures/next/rusty5.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth7
{
	diffusemap textures/next/earth7.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/vent3
{
	diffusemap textures/next/vent3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/cracked2
{
	diffusemap textures/next/cracked2.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth8
{
	diffusemap textures/next/earth8.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/rusty7
{
	diffusemap textures/next/rusty7.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker7
{
	diffusemap textures/next/bunker7.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth4
{
	diffusemap textures/next/earth4.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth3
{
	diffusemap textures/next/earth3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/bunker6
{
	diffusemap textures/next/bunker6.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/plywood3
{
	diffusemap textures/next/plywood3.tga

	{
		map $diffuse
	}
}

textures/data.pk3dir/textures/next/earth2
{
	diffusemap textures/next/earth2.tga

	{
		map $diffuse
		map $reflectcube
	}
}

textures/data.pk3dir/textures/next/rusty4
{
	diffusemap textures/next/rusty4.tga

	{
		map $diffuse
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

