/*
====================
Event_MuzzleFlash

Spawns a muzzleflash tempentity. Looking fancy
====================
*/
void
Event_MuzzleFlash(void)
{
	static void Event_MuzzleFlash_Death(void) {
		remove(self);
	}

	// Find muzzleflash tag position.
	float tagIndex = gettagindex(pSeat->m_eViewModel, "muzzleflash");
	vector vMuzzlePos = gettaginfo(pSeat->m_eViewModel, tagIndex);
	
	// Spawn TE.
	entity eMuzzle = spawn();
	setorigin(eMuzzle, vMuzzlePos);
#if 1
	setmodel(eMuzzle, "models/weapons/muzzleflashes/muzzleflash1.vvm");
#endif
	eMuzzle.movetype = MOVETYPE_NONE;
	eMuzzle.drawmask = MASK_ENGINE;
	eMuzzle.renderflags = RF_DEPTHHACK;
	eMuzzle.effects |= EF_NOSHADOW | EF_FULLBRIGHT;
	eMuzzle.angles = [view_angles[0], view_angles[1], 0];
	eMuzzle.think = Event_MuzzleFlash_Death;
	eMuzzle.nextthink = time + 0.025f; 
}

/*
====================
Event_PlaySound

Plays a sound, really fancy too.
====================
*/
void
Event_PlaySound(entity ent, string soundShader, int channel)
{
	Sound_Play(ent, channel, soundShader);
}

/*
====================
Game_ClientModelEvent

Fetches any model events that are game specific, otherwise passes them on
to the default function. (Which, well, won't do much..)
====================
*/
void
Game_ClientModelEvent(float flTimeStamp, int iCode, string strData)
{
	switch (iCode) {
	
	// Event_PlaySound.
	case 1337:
			Event_PlaySound(pSeat->m_ePlayer, strData, CHAN_WEAPON);
		break;
	
	// Event_MuzzleFlash
	case 1338:
			Event_MuzzleFlash();
		break;
	default:
		dprint(sprintf("^xF42 CLIENT - Unknown Game Model Event: ^xFFF %d\n", iCode));
		Event_ProcessModel(flTimeStamp, iCode, strData);
	}
}
