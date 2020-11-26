/*
 * Copyright (c) 2016-2020 Marco Hladik <marco@icculus.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*QUAKED item_battery (0 0 0.8) (-16 -16 0) (16 16 36)

SCHIZOMANIA ENTITY

Allows for a message dialogue to display. Makes for a conversation with
NPC entities possible.

*/
class egui_dialogue:CBaseEntity
{
	void(void) egui_dialogue;
	virtual void(void) Respawn;
};

//=======================
// void Respawn(void)
//
// Respawn.
//=======================
void egui_dialogue::Respawn(void)
{
	SetSolid(SOLID_TRIGGER);
	SetMovetype(MOVETYPE_TOSS);
	SetSize([-16,-16,0],[16,16,16]);
	// SetOrigin(m_oldOrigin);
	// SetModel(m_oldModel);

	// think = __NULL__;
	// nextthink = -1;

	// if (!real_owner)
	// 	Sound_Play(this, CHAN_ITEM, "item.respawn");

	// droptofloor();
}

//=======================
// void egui_dialogue(void)
//
// Constructor.
//=======================
void egui_dialogue::egui_dialogue(void)
{
    // Call Super class constructor. 
	CBaseEntity::CBaseEntity();
    classname = "egui_dialogue";

    // Respawn.
	egui_dialogue::Respawn();
}
