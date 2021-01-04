# TODO list.
Here we have a todo list, aiming towards the completion of a complete map
in which all game mechanics come on board.

This list (if I don't forget to) will be updated regularly, since it is for
my own ADHD good.

## Entities - Prototype 0.1:
- Remove game_locked_Door
- Rename egui_mainmenu to gui_mainmenu
- Remove most redundant HL1 stock entities. Time to clear our code.

## Weapons - Prototype 0.1:
- Knife
  - Work on better sounds, where possible.

- Pistol
  - Implement properly.
  - Export model to .iqe and generate a .vvm

- Flashlight
  - Improve the flickering when battery runs low. (Pick a better lightstyle.)
  - Make this an actual weapon? That'd be nice, right?

## General Code Tasks:
- Implement Scripted Sequences with dialogues. (I suppose, an entity which'll send a dialogue event mechanism, back and forth? :) )
## GUI - Prototype 0.1:
### Possible, but not required:
- Use images for buttons. (Maybe a hover glow? effect)
- Use sound for the hover, and click etc!
- Render a player mesh, and health/ammo status.
    -- In the future, make him draw a weapon, or play a heavy breathing animation in case he is hurt etc.
- Make item list scrollable.

## Assets (This list is obviously to be updated a lot..):
- Acquire gfx for preferably a red,white-ish, black, based in-game menu.
- Acquire sfx for in-game menu.
- Acquire a few Mixamo models, for AI, and NPC's. (Also thus, Brian, the player model)
- Acquire basic sounds for doors, footsteps, ambiance.

## Map: test_prototype_indoor:
- To be redesigned due to current issues with the map design.

## Map: test_prototype_outdoor:
- It is there, but left unfinished, expected during Prototype 0.2, or 0.3.. goals. :)

# Technical Research List:
- How to do a proper zombie walk animaton, use offsets so it "moves backwards", to counter the slide effect.
- Shadows need to be disabled since the brush used to cast extra light for streetlamps, is somehow tagged along with it.
  We gotta fix that..
- Body part specific damage, head, arms, legs etc.
  - Adjust damage values, also in Traceattack.c for when a specific bodypart has been hit.
    - It multiplies the damage usually by 0.4* etc, which means if a 9mm does like 9 damage... It takes a good 40 hits to kill lol
