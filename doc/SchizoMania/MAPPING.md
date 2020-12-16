Build settings currently used:
Fast Fullbright:
1:[vmap] -custinfoparms -threads 4 -samplesize 8 "[MapFile]"
2:[vmap] -vis -v -fast "[MapFile]"

Fast:
1: [vmap] -custinfoparms -threads 4 -samplesize 8 "[MapFile]"
2: [vmap] -vis -v -fast "[MapFile]"
3: [vmap] -light -custinfoparms -v -bounce 8 -bouncegrid -samplesize 2 -faster -threads 4 -samples 4 -shade -shadeangle 60 -patchshadows "[MapFile]"

Full:
1:[vmap] -custinfoparms -meta -threads 4 -samplesize 1 "[MapFile]"
2:[vmap] -vis "[MapFile]"
3:[vmap] -light -custinfoparms -bounce 8 -samplesize 1 -dirty -threads 4 -samples 4 -shade -shadeangle 60 -patchshadows "[MapFile]"