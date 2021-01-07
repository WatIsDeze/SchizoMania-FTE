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

void
Bot_PickName(entity target)
{
	int n = 0;
	entity pbot = world;
	for (int i = 1; (pbot = edict_num(i)); i++) {
		if (clienttype(pbot) == CLIENTTYPE_BOT) {
			n++;
		}
	}
	forceinfokey(target, "name", sprintf("Bot %i", n));
}

entity
Bot_AddQuick(void)
{
	/* we've got no nodes, so generate some fake waypoints */
	if (!g_nodes_present) {
		return world;
	}

	entity newbot;
	entity oself;

	oself = self;
	self = world;
	self = spawnclient();

	if (!self) {
		print("^1Bot_AddQuick^7: Can't add bot. Server is full\n");
		self = oself;
		return world;
	}

	Bot_PickName(self);
	ClientConnect();
	PutClientInServer();

	newbot = self;
	self = oself;
	return newbot;
}
