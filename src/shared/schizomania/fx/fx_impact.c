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

#ifdef CLIENT
var int FX_IMPACT_BLACKBITS;
var int FX_IMPACT_SMOKE_BROWN;
var int FX_IMPACT_SMOKE_GREY;
var int FX_IMPACT_SPARK;

var int DECAL_IMPACT_DEFAULT;
var int DECAL_IMPACT_ALIEN;
var int DECAL_IMPACT_FLESH;
var int DECAL_IMPACT_FOLIAGE;
var int DECAL_IMPACT_COMPUTER;
var int DECAL_IMPACT_DIRT;
var int DECAL_IMPACT_VENT;
var int DECAL_IMPACT_GRATE;
var int DECAL_IMPACT_METAL;
var int DECAL_IMPACT_GLASS;
var int DECAL_IMPACT_SAND;
var int DECAL_IMPACT_SLOSH;
var int DECAL_IMPACT_SNOW;
var int DECAL_IMPACT_TILE;
var int DECAL_IMPACT_WOOD;
var int DECAL_IMPACT_CONCRETE;

void
FX_Impact_Init(void)
{
	precache_sound("weapons/ric1.wav");
	precache_sound("weapons/ric2.wav");
	precache_sound("weapons/ric3.wav");
	precache_sound("weapons/ric4.wav");
	precache_sound("weapons/ric5.wav");

	FX_IMPACT_BLACKBITS = particleeffectnum("fx_impact.blackbits");
	FX_IMPACT_SMOKE_GREY = particleeffectnum("fx_impact.smoke_grey");
	FX_IMPACT_SMOKE_BROWN = particleeffectnum("fx_impact.smoke_brown");
	FX_IMPACT_SPARK = particleeffectnum("fx_impact.spark");

	/* engine-side particle system decals for non HL1 BSP */
	DECAL_IMPACT_DEFAULT = particleeffectnum("decal_impact.default");
	DECAL_IMPACT_ALIEN = particleeffectnum("decal_impact.alien");
	DECAL_IMPACT_FLESH = particleeffectnum("decal_impact.flesh");
	DECAL_IMPACT_FOLIAGE = particleeffectnum("decal_impact.foliage");
	DECAL_IMPACT_COMPUTER = particleeffectnum("decal_impact.computer");
	DECAL_IMPACT_DIRT = particleeffectnum("decal_impact.dirt");
	DECAL_IMPACT_VENT = particleeffectnum("decal_impact.vent");
	DECAL_IMPACT_GRATE = particleeffectnum("decal_impact.grate");
	DECAL_IMPACT_METAL = particleeffectnum("decal_impact.metal");
	DECAL_IMPACT_GLASS = particleeffectnum("decal_impact.glass");
	DECAL_IMPACT_SAND = particleeffectnum("decal_impact.sand");
	DECAL_IMPACT_SLOSH = particleeffectnum("decal_impact.slosh");
	DECAL_IMPACT_SNOW = particleeffectnum("decal_impact.snow");
	DECAL_IMPACT_TILE = particleeffectnum("decal_impact.tile");
	DECAL_IMPACT_WOOD = particleeffectnum("decal_impact.wood");
	DECAL_IMPACT_CONCRETE = particleeffectnum("decal_impact.concrete");
}
#endif

void
FX_Impact(int iType, vector vecPos, vector vNormal)
{
#ifdef SERVER
	WriteByte(MSG_MULTICAST, SVC_CGAMEPACKET);
	WriteByte(MSG_MULTICAST, EV_IMPACT);
	WriteByte(MSG_MULTICAST, (float)iType);
	WriteCoord(MSG_MULTICAST, vecPos[0]); 
	WriteCoord(MSG_MULTICAST, vecPos[1]); 
	WriteCoord(MSG_MULTICAST, vecPos[2]);
	WriteCoord(MSG_MULTICAST, vNormal[0]); 
	WriteCoord(MSG_MULTICAST, vNormal[1]); 
	WriteCoord(MSG_MULTICAST, vNormal[2]);
	msg_entity = self;
	multicast(vecPos, MULTICAST_PVS);
#else
	/* decals */
	if (serverkeyfloat("*bspversion") == BSPVER_HL)
	switch (iType) {
	case IMPACT_GLASS:
		Decals_Place(vecPos, sprintf("{break%d", floor(random(1,4))));
		break;
	case IMPACT_MELEE:
		Decals_Place(vecPos, sprintf("{shot%d", floor(random(1,6))));
		break;
	default:
		Decals_Place(vecPos, sprintf("{bigshot%d", floor(random(1,6))));
		break;
	}
	else
		// Decals.
		switch (iType) {
		case IMPACT_GLASS:
			pointparticles(DECAL_IMPACT_GLASS, vecPos, vNormal, 1);
			break;
		case IMPACT_WOOD:
			pointparticles(DECAL_IMPACT_WOOD, vecPos, vNormal, 1);
			break;
		case IMPACT_METAL:
			pointparticles(DECAL_IMPACT_METAL, vecPos, vNormal, 1);
			break;
		case IMPACT_FLESH:
			pointparticles(DECAL_IMPACT_FLESH, vecPos, vNormal, 1);
			break;
		default:
			pointparticles(DECAL_IMPACT_DEFAULT, vecPos, vNormal, 1);
			break;
		}

		// Spark/Smoke particles.
		switch (iType) {
			case IMPACT_MELEE:
			case IMPACT_EXPLOSION:
				break;
			case IMPACT_GLASS:
				pointparticles(FX_IMPACT_BLACKBITS, vecPos, vNormal, 1);
				break;
			case IMPACT_WOOD:
				pointparticles(FX_IMPACT_SPARK, vecPos, vNormal, 1);
				pointparticles(FX_IMPACT_BLACKBITS, vecPos, vNormal, 1);
				pointparticles(FX_IMPACT_SMOKE_BROWN, vecPos, vNormal, 1);
				break;
			case IMPACT_METAL:
				pointparticles(FX_IMPACT_SPARK, vecPos, vNormal, 1);
				pointparticles(FX_IMPACT_BLACKBITS, vecPos, vNormal, 1);
				break;
			case IMPACT_FLESH:
				FX_Blood(vecPos, vNormal);
				break;
			case IMPACT_DEFAULT:
			default:
				pointparticles(FX_IMPACT_SPARK, vecPos, vNormal, 1);
				pointparticles(FX_IMPACT_BLACKBITS, vecPos, vNormal, 1);
				pointparticles(FX_IMPACT_SMOKE_GREY, vecPos, vNormal, 1);
				break;
		}

		// Smoke.
		switch (iType) {
			case IMPACT_FLESH:
				break;
			default:
				pointsound(vecPos, sprintf("weapons/ric%d.wav", floor((random() * 5) + 1)), 1, ATTN_STATIC);
				break;
		}
#endif
} 
