# SchizoMania-FTE
Fun times with FTEQW engine and FreeCS QC as a base for modding. Let's see if we can potentially do what we want with this engine.

# Some random info:
## BSP Compiling settings.

For best quality, production usage, we use:
- [vmap] -custinfoparms -threads 4 -samplesize 1 "[MapFile]"
- [vmap] -vis "[MapFile]"
- [vmap] -light -custinfoparms -samplesize 1 -dirty -deluxe-threads 4 -samples 4 -shade -shadeangle 60 -patchshadows "[MapFile]"