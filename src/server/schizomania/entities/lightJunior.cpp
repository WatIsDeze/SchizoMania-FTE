/*QUAKED lightJunior (0 0.7 0.3) (-6 -6 -6) (6 6 6) LINEAR NOANGLE UNUSED1 UNUSED2 NOGRIDLIGHT
Non-displayed point light source THAT ONLY AFFECTS ENTITIES (lightgrid). The -pointscale and -scale arguments to Q3Map2 affect the brightness of these lights. The -skyscale argument affects brightness of entity sun lights.
-------- KEYS --------
_light OR light : Overrides the default 300 intensity.
_color : Weighted RGB value of light color (default 1.0 1.0 1.0 = white).
target : Lights pointed at a target will be spotlights.
radius : Overrides the default 64 unit radius of a spotlight at the target point.
-------- Q3MAP2 KEYS --------
_sun : Set this key to 1 on a spotlight to make an infinite sun light.
fade : Fades light attenuation. Only affects linear lights.
scale : Scales light attenuation, from SOF2/JK2. Scales the "light" value.
-------- SPAWNFLAGS --------
LINEAR : Use a linear falloff. Default is inverse distance squared (more realistic).
NOANGLE : Ignore angle attenuation.
NOGRIDLIGHT : Do not affect the lightgrid (dynamic entity lighting). Setting this spawnflag will disable this light entirely.*/
