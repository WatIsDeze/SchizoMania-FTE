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

/* 
 * How Counter-Strike's accuracy works (from my understanding)
 * this was deducted from the decrypted CS:S script files:
 * https://gamebanana.com/gamefiles/2293
 * 
 * Each and every bullet fired contributes to the shotmultiplier value,
 * which decreases back to 0 slowly over time.
 * 
 * Meanwhile, accuracy gets calculated by taking said value and dividing it
 * by the weapon-specific divider. Each gun has a different one.
 * The higher the divider value, the more accurate the weapon is in contrast
 * to other weapons.
*/

/* called whenever a cstrike gun fires a successful shot */
void
SCMA_ShotMultiplierAdd(player pl, int shots)
{
	/* more than 12 is enough, you can barely hit the barn */
	pl.scma_shotmultiplier = bound(0, pl.scma_shotmultiplier + shots, 12);

	pl.scma_shottime = 0.2f;
	pl.punchangle[0] = -4 * (pl.scma_shotmultiplier / 6);
	pl.punchangle[1] = random(-1, 1);
}

/* generate an accuracy value that we'll pass onto TraceAttack */
float
SCMA_CalculateAccuracy(player pl, float divisor)
{
	float m = 1.0f;

	if (!(pl.flags & FL_ONGROUND)) {
		m = 2.0f;
	} else if (pl.flags & FL_CROUCHING) {
		m = 0.5f;
	} else if (vlen(pl.velocity) > 120) {
		m = 1.5f;
	}

	if (divisor == -1) {
		/* snipers shoot way less accurate overall. */
		return (pl.viewzoom < 1.0f) ? (0.0f) : (0.05 * m);
	} else {
		return  (pl.scma_shotmultiplier / divisor) * m;
	}
}

/* called whenever cstrike guns aren't firing */
void
SCMA_ShotMultiplierUpdate(player pl)
{
	if ((pl.scma_shotmultiplier > 0) && (pl.scma_shottime <= 0.0f)) {
		pl.scma_shottime = pl.w_attack_next + 0.01;
		pl.scma_shotmultiplier--;
	}

	pl.scma_shottime = max(0, pl.scma_shottime - input_timelength);
}
void
w_scma_weaponrelease(void)
{
	player pl = (player)self;
	SCMA_ShotMultiplierUpdate(pl);
}
