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

/*QUAKED trigger_playerfreeze (1 0 0) (-8 -8 -8) (8 8 8)
"targetname"    Name
"killtarget"    Target to kill when triggered.

Trigger that freezes all clients, until it is triggered again.
Freezing a player means they're unable to move, they can still look around.

Ideas: Add ability to supress looking around, firing weapons, using items
and so on.
*/

class trigger_playerfreeze:CBaseTrigger
{
	void(void) trigger_playerfreeze;

	virtual void(void) customphysics;
	virtual void(entity,int) Trigger;
	virtual void(void) Respawn;
};

void
trigger_playerfreeze::customphysics(void)
{
	if (m_iValue == 0)
		return;

	/* some games might unset this flag every single frame */
	for (entity f = world; (f = find(f, ::classname, "player"));) {
		f.flags |= FL_FROZEN;
	}
}

void
trigger_playerfreeze::Trigger(entity act, int state)
{
	if (GetMaster() == FALSE)
		return;

	m_iValue = 1 - m_iValue;

	if (m_iValue == 0) {
		dprint("^2trigger_playerfreeze::^3Trigger^7: " \
		       "Unfreezing clients\n");

		/* force unfreeze */
		for (entity f = world; (f = find(f, ::classname, "player"));) {
			f.flags &= ~FL_FROZEN;
		}
	} else {
		dprint("^2trigger_playerfreeze::^3Trigger^7: " \
		       "Freezing clients\n");
	}
}

void
trigger_playerfreeze::Respawn(void)
{
	m_iValue = 0;
}

void
trigger_playerfreeze::trigger_playerfreeze(void)
{
	CBaseTrigger::CBaseTrigger();
}
