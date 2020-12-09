# TODO list.
Here we have a todo list, aiming towards the completion of a complete map
in which all game mechanics come on board.

This list (if I don't forget to) will be updated regularly, since it is for
my own ADHD good.

# Things to do (low priority list):
- Move item hover code to View+UpdateWeapon

# Things to research/question (medium priority):
- How to do a proper zombie walk animaton, use offsets so it "moves backwards", to counter the slide effect.
- Currently, shadows are disabled since the brush used to cast extra light for streetlamps, is somehow tagged along with it.
  We gotta fix that..

# Prototype - Alpha - 0.1
## Improvements:
- Currently picking up an item out of a drawers is hell to design properly.
- Replace the drawers in the bathroom with a cupboard, but func_door_rotating seems to not appreciate that much.

## Weapons:
- Flashlight - Improve flickering per battery power stage.
- Adjust damage values, also in Traceattack.c for when a specific bodypart has been hit.
    -- It multiplies the damage usually by 0.4* etc, which means if a 9mm does like 9 damage... It takes a good 40 hits to kill lol
- Implement knife, pistol, rifle.

## Inventory/Player in-game menu:
- Use images for buttons. (Maybe a hover glow? effect)
- Use sound for the hover, and click etc!
- Render a player mesh, and health/ammo status.
    -- In the future, make him draw a weapon, or play a heavy breathing animation in case he is hurt etc.
- Make item list scrollable.

## Map: test_prototype_indoor:
- Basic fade screen intro, with animations of the player waking up hungover and confused lololol.
- Finish bathroom cupboard, add a medkit.

### Events:
- #1 Must pickup all items before entering livingroom, maybe make the player complain about having lost his shit.
- #2 Enter the livingroom, stare out the window for a view secs before he decides to leave the appartment.
- #3 Uh oh, zombie ahead! Scary effects, breaking light, electricity, flashing light.
- #4 [Something related to another appartment?]?
- #5 Uh oh, zombie down the stairs! Tries to creep up on ya from the right!

## Code for test_prototype:
- Implement Scripted Sequences with dialogues. (I suppose, an entity which'll send a dialogue event, back and forth? :) )

## Assets:
- Acquire gfx for preferably a blue-ish, black, based in-game menu.
- Acquire sfx for in-game menu.
- Acquire a few Mixamo models, for AI, and NPC's. (Also thus, Brian, the player model)
- Acquire first person view models for a knife, and a pistol. Maybe use Mixamo meshes for the arms/hands?
- Acquire basic sounds for doors, footsteps, ambiance.
