# Prototype 0.1
## Entities - Prototype 0.1:
- [_] Remove game_locked_Door
- [_] Rename egui_mainmenu to gui_mainmenu
- [X] Remove most redundant HL1 stock entities. Time to clear our code.
## Inventory Menu:
- [_] Make an unequip option? The player would move faster when unequiped. However, 
- [_] Display items from top to bottom, make the list scrollable.

## Items:
- [_] Implement Syphon Filter like "item tagging" where the text displays above an item when close to it. Make this a cvar difficulty setting. 
- [_] Add APAP Pill Bottle item. Recovers Stamina by 20 points.
- [_] Add a smaller health item. Recovers Health by 10 points.
- [_] Add 9mm Ammo Clip item. Can reload 14 bullets.

## Weapons:
- [_] Let the knife secondary attack use Stamina.
- [_] Acquire Flashlight model and implement a light being attached to a bone.
- [_] Allow for a quick weapon switch between Flashlight and Equiped weapon. Otherwise it's not fun to play.
- [_] Let reloading use a clip from the inventory.
- [_] Have an animation for when we're out of clips, but the gun is on-screen.
- [_] If an empty clip, play an empty clip sound if trying to shoot.

## Content:
### Sound:
- [_] Ricochet sounds, for when bullet hits walls, wood, glass, metal, dirt, water, etc.
- [_] Replace footstep audio files with our own.

### Graphics:
- [_] Player model animations, for cutscenes, and for death.

# Prototype 0.2
## GUI (General):
- [_] Use nice images for buttons, maybe hover glow or something?

## Gameplay (General):
- [_] Implement proning, hopefully also rids us of the silly crouch jump on top of things movement.
- [_] Investigate headshots, and implement properly.
  - Adjust damage values, also in Traceattack.c for when a specific bodypart has been hit.
    - It multiplies the damage usually by 0.4* etc, which means if a 9mm does like 9 damage... It takes a good 40 hits to kill lol
## Status Menu:
- [_] Poisoned, you can be poisoned, yes. So a textual indicator (with symbols preferably) to show what is up. Poisoned, or... what have ya.

## Inventory Menu:
- [_] Implement item "inspection". So one can take a closer look at an item, and possibly acquire an item if clicking on something? 
      Like a letter which may need to be opened, before you can read it. But also, to observe if there's for example some cryptical text on it.