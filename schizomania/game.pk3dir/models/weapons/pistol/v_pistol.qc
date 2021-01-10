output v_pistol.vvm
materialprefix /textures/models/weapons/pistol/


origin 64 -20 -24
rotate 270 -90 0
scale 1.5

scene "iqe/v_pistol_muzzleflash.iqe" noanim 1 

scene "iqe/v_pistol_muzzleflash.iqe" nomesh 1 name "idle1" fps 30 start 168 end 196

event reset
    event 2 1337 "weapon_pistol.fire"
    event 2 1338 "muzzleflash1.vvm"
    scene "iqe/v_pistol_muzzleflash.iqe" nomesh 1 name "attack1" fps 30 start 2 end 10

scene "iqe/v_pistol_muzzleflash.iqe" nomesh 1 name "attack2" fps 30 start 196 end 214

event reset
    event 10 1337 "weapon_pistol.reload"
    scene "iqe/v_pistol_muzzleflash.iqe" nomesh 1 name "reload1" fps 30 start 10 end 56

event reset
    event 135 1337 "weapon_pistol.deploy"
    scene "iqe/v_pistol_muzzleflash.iqe" nomesh 1 name "draw1" fps 30 start 135 end 167

event reset
    event 126 1337 "weapon_pistol.holster"
    scene "iqe/v_pistol_muzzleflash.iqe" nomesh 1 name "holster1" fps 20 start 126 end 135

