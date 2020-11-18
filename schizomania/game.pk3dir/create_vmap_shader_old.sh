#!/bin/sh
# Copyright (c) 2016-2019 Vera Visions LLC. All rights reserved.

makestuff ()
{
cd ./textures
LEGACY_OUT="tex_legacy.shader"

echo "// THIS FILE HAS BEEN AUTOMATICALLY GENERATED!" > "$LEGACY_OUT"
echo "// Please refer to the original documentation." >> "$LEGACY_OUT"
echo "// This is for development purposes ONLY." >> "$LEGACY_OUT"
echo "" >> "$LEGACY_OUT"

find */ -name '*.mat'| while read SHADER_N; do
	echo "$SHADER_N"
	echo "textures/$SHADER_N" >> "$LEGACY_OUT";
	cat "$SHADER_N" >> "$LEGACY_OUT";
	echo "" >> "$LEGACY_OUT";
done;

sed -i '/SchizoMania Material/d' ./$LEGACY_OUT
sed -i 's/.mat//g' ./$LEGACY_OUT
sed -i '/if $programs/','/else/d' ./$LEGACY_OUT
sed -i '/endif/d' ./$LEGACY_OUT
sed -i '/nodraw2/d' ./$LEGACY_OUT
sed -i '/program /d' ./$LEGACY_OUT
sed -i '/normalmap/d' ./$LEGACY_OUT
sed -i '/alphaGen portal/d' ./$LEGACY_OUT
sed -i '/deformVertexes autoSprite/d' ./$LEGACY_OUT
cd ../..
}

cd ./game.pk3dir
makestuff
# cd ./tw_textures_mip.pk3dir
# makestuff

cat ./game.pk3dir/textures/tex_legacy.shader > ./scripts/tex_legacy.shader
# cat ./tw_textures_mip.pk3dir/textures/tex_legacy.shader >> ./scripts/tex_legacy.shader

rm ./game.pk3dir/textures/tex_legacy.shader
# rm ./tw_textures_mip.pk3dir/textures/tex_legacy.shader

echo "Done. File dumped in ./scripts/$LEGACY_OUT"