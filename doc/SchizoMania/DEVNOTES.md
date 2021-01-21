# TODO list.
Here we have a todo list, aiming towards the completion of a complete map
in which all game mechanics come on board.

This list (if I don't forget to) will be updated regularly, since it is for
my own ADHD good.

## Code Tasks (general) - Prototype 0.2:
- [_] Implement Syphon Filter like "item tagging" where the text displays above an item when close to it. Make this a cvar difficulty setting.

## Code Tasks (general) - Prototype 0.1:
- [_] Implement Scripted Sequences with dialogues. (I suppose, an entity which'll send a dialogue event mechanism, back and forth? :) )
- [_] Rename GF_HOVER_FULLBRIGHT to GF_USEABLE? Also, somehow find a way to not need a "custom" entity for this. Would require breaking all rules though...
- [_] 50% there. Implement proper crosshair system.

## Game & Code? Tasks (general) - Prototype 0.1:
- [X] Health system, green = fine, yellow = caution, orange = extra caution, red = danger.
- [_] Poisoned, you can be poisoned, yes. So a textual indicator (with symbols preferably) to show what is up. Poisoned, or... what have ya.
- [X] Display the character in the menu, in case...
- [_] Implement item "inspection". So one can take a closer look at an item, and possibly acquire an item if clicking on something? 
      Like a letter which may need to be opened, before you can read it. But also, to observe if there's for example some cryptical text on it.
- [_] Implement APAP Pill Bottle

## Entities - Prototype 0.1:
- [_] Remove game_locked_Door
- [_] Rename egui_mainmenu to gui_mainmenu
- [X] Remove most redundant HL1 stock entities. Time to clear our code.

## AI - Prototype 0.1:
- [X] Pull in latest FreeCS changes and see if we can do anything with that botlib of theirs.


## Items - Prototype 0.1:
- [_] 9mm Ammo Clips.
- [_] Health medicine.
- [_] ..
- [_] ..
- [_] ..

## Weapons - Prototype 0.1:
- [_] Fix accuracy issues when shooting.

- [_] Knife
  - [_] Work on better sounds, where possible.
  - [?] Implement model events for audio.

- [_] Pistol
  - [-] Implement properly.
    - [X] Add Muzzleflash
    - [X] Add shell dropping effect.
    - [_] Can only reload when in posession of magazines... 
      - [_] Each reload costs an entire clip. Like the old day RE etc games.
    - [_] Fix animations so that when we're out of ammo, it shows.
  - [X] Export model to .iqe and generate a .vvm
  - [X] Add sounds.

- [_] Flashlight
  - [_] Wait a few miliseconds, so the light turns on accordingly to the audio.
  - [_] Improve the flickering when battery runs low. (Pick a better lightstyle.)
  - [_] Make this an actual weapon? That'd be nice, right?
  - [_] Replace stock Valve sounds.

## Content Tasks (Make us Valve independent!) 0.1:
These are some random ideas, which will be implemented if possible.
Other than that it is a bit of a list of ... anything.
- [_] Ricochet sounds.
- [_] Use Item Sound.
- [X] Drop Item Sound.
- [X] Pickup Item Sound.
- [_] Smoke/Sparks for bullet hits, need replacing.
- [_] Bullet ricochet sounds..
- [_] Hand animation for picking up items, or droppen them??

- [_] Ammo clips for pistol, reloading by item menu?
  - [_] Maybe let R button remove a clip by default?

## GUI - Prototype 0.1:
### Item Menu (More of a... well, all you have menu for the player)
- [X] Display player model. (Not a requirement, but fun to have.)
- [/] Display player health, and current weapon that is equiped, and amount of ammo.
- [_] Make use button disable when an item can't be "used".
- [_] Make equip button disable when an item can't be "equiped".
- [_] Make unequip an option in case an item already IS equiped.
- [_] Use images for buttons. (Maybe a hover glow? effect) Could be nice.
- [X] Use sound for the hover, and click etc!
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
- Proning, instead of only crouching. Can we do this? Pretty sure we can but, how much work is it?
- Body part specific damage, head, arms, legs etc.
  - Adjust damage values, also in Traceattack.c for when a specific bodypart has been hit.
    - It multiplies the damage usually by 0.4* etc, which means if a 9mm does like 9 damage... It takes a good 40 hits to kill lol
