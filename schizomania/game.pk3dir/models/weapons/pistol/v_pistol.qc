output v_pistol.vvm
materialprefix /textures/models/weapons/pistol/


origin 64 -20 -24
rotate 270 -90 0
scale 1.5

scene "iqe/v_pistol.iqe" noanim 1 

scene "iqe/v_pistol.iqe" nomesh 1 name "idle1" fps 30 start 168 end 196
scene "iqe/v_pistol.iqe" nomesh 1 name "attack1" fps 30 start 2 end 10
scene "iqe/v_pistol.iqe" nomesh 1 name "attack2" fps 30 start 196 end 214
scene "iqe/v_pistol.iqe" nomesh 1 name "reload1" fps 30 start 10 end 56

event reset
    scene "iqe/v_pistol.iqe" nomesh 1 name "draw1" fps 30 start 135 end 167
event 0 5004 "weapon_pistol.deploy 1"

event reset
    scene "iqe/v_pistol.iqe" nomesh 1 name "holster1" fps 20 start 126 end 135
event 0 5004 "weapon_pistol.holster 1"
