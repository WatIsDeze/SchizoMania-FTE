# TODO list.
Here we have a todo list, aiming towards the completion of a complete map
in which all game mechanics come on board.

This list (if I don't forget to) will be updated regularly, since it is for
my own ADHD good.

## Entities - Prototype 0.1:
- [_] Remove game_locked_Door
- [_] Rename egui_mainmenu to gui_mainmenu
- [_] Remove most redundant HL1 stock entities. Time to clear our code.

## Weapons - Prototype 0.1:
- [_] Knife
  - [_] Work on better sounds, where possible.

- [_] Pistol
  - [_] Implement properly.
  - [_] Export model to .iqe and generate a .vvm
  - [_] Add sounds.

- [_] Flashlight
  - [_] Wait a few miliseconds, so the light turns on accordingly to the audio.
  - [_] Improve the flickering when battery runs low. (Pick a better lightstyle.)
  - [_] Make this an actual weapon? That'd be nice, right?
  - [_] Replace stock Valve sounds.

## Code Tasks (general) - Prototype 0.1:
- [_] Use Item Sound.
- [_] Drop Item Sound.
- [_] Pickup Item Sound.
- [_] Implement Scripted Sequences with dialogues. (I suppose, an entity which'll send a dialogue event mechanism, back and forth? :) )
## GUI - Prototype 0.1:
### Possible, but not required:
- [_] Use images for buttons. (Maybe a hover glow? effect)
- [_] Use sound for the hover, and click etc!
- [_] Render a player mesh, and health/ammo status.
    -- In the future, make him draw a weapon, or play a heavy breathing animation in case he is hurt etc.
- [_] Make item list scrollable.

## Assets (This list is obviously to be updated a lot..):
- [_] Acquire gfx for preferably a red,white-ish, black, based in-game menu.
- [_] Acquire sfx for in-game menu.
- [_] Acquire a few Mixamo models, for AI, and NPC's. (Also thus, Brian, the player model)
  - [_] Player model, for death animations and scenes.
  - [_] Assets for a misty monster.
- [_] Acquire basic sounds for doors, footsteps, ambiance.
  - [_] Still need to replace all our footsteps...

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
