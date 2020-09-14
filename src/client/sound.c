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

var int g_voxcount;
var int g_voxpos;
var float g_voxtime = 0.0f;

class CCSAmbientSound {
	float m_flVolume;
	float m_flAttn;
	float m_flPitch;
	string m_strSample;
};

void
Sound_ParseLoopingEntity(entity sndent, float isNew)
{
	float flFlags;
	CCSAmbientSound new = (CCSAmbientSound)sndent;

	if (isNew) {
		spawnfunc_CCSAmbientSound();
	}

	flFlags = readfloat();

	if (flFlags & 1) {
		new.origin[0] = readcoord();
		new.origin[1] = readcoord();
		new.origin[2] = readcoord();
		setorigin(new, new.origin);
		new.m_flVolume = readfloat();
		new.m_flAttn = readbyte();
		new.m_flPitch = readfloat();
	}

	if (flFlags & 2) {
		new.m_strSample = readstring();
	}
	sound(new, CHAN_VOICE, new.m_strSample, new.m_flVolume, new.m_flAttn, new.m_flPitch);
}

sound_t *g_voxque;

void
Sound_PlayVOX(string msg)
{
	if (g_voxcount) {
		return;
	}

	g_voxcount = tokenize(msg);
	g_voxque = memalloc(sizeof(sound_t) * g_voxcount);

	for (int i = 0; i < g_voxcount; i++) {
		g_voxque[i].m_strSnd = sprintf("vox/%s.wav", argv(i));
		g_voxque[i].m_flLength = soundlength(g_voxque[i].m_strSnd);
	}
	g_voxtime = time;
}

void
Sound_ProcessWordQue(void)
{
	if (cltime < 2 || !g_voxcount) {
		return;
	}

	if (g_voxtime < time) {
		localcmd(sprintf("play %s\n", g_voxque[g_voxpos].m_strSnd));
		g_voxpos++;

		if (g_voxpos == g_voxcount) {
			memfree(g_voxque);
			g_voxcount = 0;
			g_voxpos = 0;
		} else {
			g_voxtime = time + g_voxque[g_voxpos - 1].m_flLength;
		}
	}
}

void
Sound_InitVOX(void)
{
	precache_sound("vox/accelerating.wav");
	precache_sound("vox/accelerator.wav");
	precache_sound("vox/accepted.wav");
	precache_sound("vox/access.wav");
	precache_sound("vox/acknowledged.wav");
	precache_sound("vox/acknowledge.wav");
	precache_sound("vox/acquired.wav");
	precache_sound("vox/acquisition.wav");
	precache_sound("vox/across.wav");
	precache_sound("vox/activated.wav");
	precache_sound("vox/activate.wav");
	precache_sound("vox/activity.wav");
	precache_sound("vox/adios.wav");
	precache_sound("vox/administration.wav");
	precache_sound("vox/advanced.wav");
	precache_sound("vox/after.wav");
	precache_sound("vox/agent.wav");
	precache_sound("vox/alarm.wav");
	precache_sound("vox/alert.wav");
	precache_sound("vox/alien.wav");
	precache_sound("vox/aligned.wav");
	precache_sound("vox/all.wav");
	precache_sound("vox/alpha.wav");
	precache_sound("vox/amigo.wav");
	precache_sound("vox/ammunition.wav");
	precache_sound("vox/am.wav");
	precache_sound("vox/and.wav");
	precache_sound("vox/announcement.wav");
	precache_sound("vox/anomalous.wav");
	precache_sound("vox/antenna.wav");
	precache_sound("vox/an.wav");
	precache_sound("vox/any.wav");
	precache_sound("vox/apprehend.wav");
	precache_sound("vox/approach.wav");
	precache_sound("vox/area.wav");
	precache_sound("vox/are.wav");
	precache_sound("vox/armed.wav");
	precache_sound("vox/armor.wav");
	precache_sound("vox/armory.wav");
	precache_sound("vox/arm.wav");
	precache_sound("vox/arrest.wav");
	precache_sound("vox/ass.wav");
	precache_sound("vox/atomic.wav");
	precache_sound("vox/attention.wav");
	precache_sound("vox/at.wav");
	precache_sound("vox/authorized.wav");
	precache_sound("vox/authorize.wav");
	precache_sound("vox/automatic.wav");
	precache_sound("vox/a.wav");
	precache_sound("vox/away.wav");
	precache_sound("vox/backman.wav");
	precache_sound("vox/back.wav");
	precache_sound("vox/bad.wav");
	precache_sound("vox/bag.wav");
	precache_sound("vox/bailey.wav");
	precache_sound("vox/barracks.wav");
	precache_sound("vox/base.wav");
	precache_sound("vox/bay.wav");
	precache_sound("vox/been.wav");
	precache_sound("vox/before.wav");
	precache_sound("vox/be.wav");
	precache_sound("vox/beyond.wav");
	precache_sound("vox/biohazard.wav");
	precache_sound("vox/biological.wav");
	precache_sound("vox/birdwell.wav");
	precache_sound("vox/bizwarn.wav");
	precache_sound("vox/black.wav");
	precache_sound("vox/blast.wav");
	precache_sound("vox/blocked.wav");
	precache_sound("vox/bloop.wav");
	precache_sound("vox/blue.wav");
	precache_sound("vox/bottom.wav");
	precache_sound("vox/bravo.wav");
	precache_sound("vox/breached.wav");
	precache_sound("vox/breach.wav");
	precache_sound("vox/break.wav");
	precache_sound("vox/bridge.wav");
	precache_sound("vox/bust.wav");
	precache_sound("vox/button.wav");
	precache_sound("vox/but.wav");
	precache_sound("vox/buzwarn.wav");
	precache_sound("vox/b.wav");
	precache_sound("vox/bypass.wav");
	precache_sound("vox/cable.wav");
	precache_sound("vox/called.wav");
	precache_sound("vox/call.wav");
	precache_sound("vox/canal.wav");
	precache_sound("vox/captain.wav");
	precache_sound("vox/capture.wav");
	precache_sound("vox/cap.wav");
	precache_sound("vox/ceiling.wav");
	precache_sound("vox/celsius.wav");
	precache_sound("vox/center.wav");
	precache_sound("vox/centi.wav");
	precache_sound("vox/central.wav");
	precache_sound("vox/chamber.wav");
	precache_sound("vox/charlie.wav");
	precache_sound("vox/checkpoint.wav");
	precache_sound("vox/check.wav");
	precache_sound("vox/chemical.wav");
	precache_sound("vox/cleanup.wav");
	precache_sound("vox/clearance.wav");
	precache_sound("vox/clear.wav");
	precache_sound("vox/close.wav");
	precache_sound("vox/coded.wav");
	precache_sound("vox/code.wav");
	precache_sound("vox/collider.wav");
	precache_sound("vox/command.wav");
	precache_sound("vox/_comma.wav");
	precache_sound("vox/communication.wav");
	precache_sound("vox/complex.wav");
	precache_sound("vox/computer.wav");
	precache_sound("vox/condition.wav");
	precache_sound("vox/containment.wav");
	precache_sound("vox/contamination.wav");
	precache_sound("vox/control.wav");
	precache_sound("vox/coolant.wav");
	precache_sound("vox/coomer.wav");
	precache_sound("vox/core.wav");
	precache_sound("vox/correct.wav");
	precache_sound("vox/corridor.wav");
	precache_sound("vox/crew.wav");
	precache_sound("vox/cross.wav");
	precache_sound("vox/cryogenic.wav");
	precache_sound("vox/c.wav");
	precache_sound("vox/dadeda.wav");
	precache_sound("vox/damaged.wav");
	precache_sound("vox/damage.wav");
	precache_sound("vox/danger.wav");
	precache_sound("vox/day.wav");
	precache_sound("vox/deactivated.wav");
	precache_sound("vox/decompression.wav");
	precache_sound("vox/decontamination.wav");
	precache_sound("vox/deeoo.wav");
	precache_sound("vox/defense.wav");
	precache_sound("vox/degrees.wav");
	precache_sound("vox/delta.wav");
	precache_sound("vox/denied.wav");
	precache_sound("vox/deployed.wav");
	precache_sound("vox/deploy.wav");
	precache_sound("vox/destroyed.wav");
	precache_sound("vox/destroy.wav");
	precache_sound("vox/detain.wav");
	precache_sound("vox/detected.wav");
	precache_sound("vox/detonation.wav");
	precache_sound("vox/device.wav");
	precache_sound("vox/did.wav");
	precache_sound("vox/die.wav");
	precache_sound("vox/dimensional.wav");
	precache_sound("vox/dirt.wav");
	precache_sound("vox/disengaged.wav");
	precache_sound("vox/dish.wav");
	precache_sound("vox/disposal.wav");
	precache_sound("vox/distance.wav");
	precache_sound("vox/distortion.wav");
	precache_sound("vox/doctor.wav");
	precache_sound("vox/doop.wav");
	precache_sound("vox/door.wav");
	precache_sound("vox/do.wav");
	precache_sound("vox/down.wav");
	precache_sound("vox/dual.wav");
	precache_sound("vox/duct.wav");
	precache_sound("vox/d.wav");
	precache_sound("vox/east.wav");
	precache_sound("vox/echo.wav");
	precache_sound("vox/ed.wav");
	precache_sound("vox/effect.wav");
	precache_sound("vox/egress.wav");
	precache_sound("vox/eighteen.wav");
	precache_sound("vox/eight.wav");
	precache_sound("vox/eighty.wav");
	precache_sound("vox/electric.wav");
	precache_sound("vox/electromagnetic.wav");
	precache_sound("vox/elevator.wav");
	precache_sound("vox/eleven.wav");
	precache_sound("vox/eliminate.wav");
	precache_sound("vox/emergency.wav");
	precache_sound("vox/energy.wav");
	precache_sound("vox/engaged.wav");
	precache_sound("vox/engage.wav");
	precache_sound("vox/engine.wav");
	precache_sound("vox/enter.wav");
	precache_sound("vox/entry.wav");
	precache_sound("vox/environment.wav");
	precache_sound("vox/error.wav");
	precache_sound("vox/escape.wav");
	precache_sound("vox/evacuate.wav");
	precache_sound("vox/e.wav");
	precache_sound("vox/exchange.wav");
	precache_sound("vox/exit.wav");
	precache_sound("vox/expect.wav");
	precache_sound("vox/experimental.wav");
	precache_sound("vox/experiment.wav");
	precache_sound("vox/explode.wav");
	precache_sound("vox/explosion.wav");
	precache_sound("vox/exposure.wav");
	precache_sound("vox/exterminate.wav");
	precache_sound("vox/extinguisher.wav");
	precache_sound("vox/extinguish.wav");
	precache_sound("vox/extreme.wav");
	precache_sound("vox/facility.wav");
	precache_sound("vox/fahrenheit.wav");
	precache_sound("vox/failed.wav");
	precache_sound("vox/failure.wav");
	precache_sound("vox/farthest.wav");
	precache_sound("vox/fast.wav");
	precache_sound("vox/feet.wav");
	precache_sound("vox/field.wav");
	precache_sound("vox/fifteen.wav");
	precache_sound("vox/fifth.wav");
	precache_sound("vox/fifty.wav");
	precache_sound("vox/final.wav");
	precache_sound("vox/fine.wav");
	precache_sound("vox/fire.wav");
	precache_sound("vox/first.wav");
	precache_sound("vox/five.wav");
	precache_sound("vox/flooding.wav");
	precache_sound("vox/floor.wav");
	precache_sound("vox/fool.wav");
	precache_sound("vox/forbidden.wav");
	precache_sound("vox/force.wav");
	precache_sound("vox/forms.wav");
	precache_sound("vox/for.wav");
	precache_sound("vox/found.wav");
	precache_sound("vox/fourteen.wav");
	precache_sound("vox/fourth.wav");
	precache_sound("vox/fourty.wav");
	precache_sound("vox/four.wav");
	precache_sound("vox/foxtrot.wav");
	precache_sound("vox/freeman.wav");
	precache_sound("vox/freezer.wav");
	precache_sound("vox/from.wav");
	precache_sound("vox/front.wav");
	precache_sound("vox/fuel.wav");
	precache_sound("vox/f.wav");
	precache_sound("vox/get.wav");
	precache_sound("vox/going.wav");
	precache_sound("vox/goodbye.wav");
	precache_sound("vox/good.wav");
	precache_sound("vox/gordon.wav");
	precache_sound("vox/got.wav");
	precache_sound("vox/government.wav");
	precache_sound("vox/go.wav");
	precache_sound("vox/granted.wav");
	precache_sound("vox/great.wav");
	precache_sound("vox/green.wav");
	precache_sound("vox/grenade.wav");
	precache_sound("vox/guard.wav");
	precache_sound("vox/gulf.wav");
	precache_sound("vox/gun.wav");
	precache_sound("vox/guthrie.wav");
	precache_sound("vox/g.wav");
	precache_sound("vox/handling.wav");
	precache_sound("vox/hangar.wav");
	precache_sound("vox/has.wav");
	precache_sound("vox/have.wav");
	precache_sound("vox/hazard.wav");
	precache_sound("vox/head.wav");
	precache_sound("vox/health.wav");
	precache_sound("vox/heat.wav");
	precache_sound("vox/helicopter.wav");
	precache_sound("vox/helium.wav");
	precache_sound("vox/hello.wav");
	precache_sound("vox/help.wav");
	precache_sound("vox/here.wav");
	precache_sound("vox/hide.wav");
	precache_sound("vox/highest.wav");
	precache_sound("vox/high.wav");
	precache_sound("vox/hit.wav");
	precache_sound("vox/hole.wav");
	precache_sound("vox/hostile.wav");
	precache_sound("vox/hotel.wav");
	precache_sound("vox/hot.wav");
	precache_sound("vox/hours.wav");
	precache_sound("vox/hour.wav");
	precache_sound("vox/hundred.wav");
	precache_sound("vox/hydro.wav");
	precache_sound("vox/idiot.wav");
	precache_sound("vox/illegal.wav");
	precache_sound("vox/immediately.wav");
	precache_sound("vox/immediate.wav");
	precache_sound("vox/inches.wav");
	precache_sound("vox/india.wav");
	precache_sound("vox/ing.wav");
	precache_sound("vox/inoperative.wav");
	precache_sound("vox/inside.wav");
	precache_sound("vox/inspection.wav");
	precache_sound("vox/inspector.wav");
	precache_sound("vox/interchange.wav");
	precache_sound("vox/intruder.wav");
	precache_sound("vox/invallid.wav");
	precache_sound("vox/invasion.wav");
	precache_sound("vox/in.wav");
	precache_sound("vox/is.wav");
	precache_sound("vox/it.wav");
	precache_sound("vox/i.wav");
	precache_sound("vox/johnson.wav");
	precache_sound("vox/juliet.wav");
	precache_sound("vox/key.wav");
	precache_sound("vox/kill.wav");
	precache_sound("vox/kilo.wav");
	precache_sound("vox/kit.wav");
	precache_sound("vox/lab.wav");
	precache_sound("vox/lambda.wav");
	precache_sound("vox/laser.wav");
	precache_sound("vox/last.wav");
	precache_sound("vox/launch.wav");
	precache_sound("vox/leak.wav");
	precache_sound("vox/leave.wav");
	precache_sound("vox/left.wav");
	precache_sound("vox/legal.wav");
	precache_sound("vox/level.wav");
	precache_sound("vox/lever.wav");
	precache_sound("vox/lieutenant.wav");
	precache_sound("vox/lie.wav");
	precache_sound("vox/life.wav");
	precache_sound("vox/light.wav");
	precache_sound("vox/lima.wav");
	precache_sound("vox/liquid.wav");
	precache_sound("vox/loading.wav");
	precache_sound("vox/located.wav");
	precache_sound("vox/locate.wav");
	precache_sound("vox/location.wav");
	precache_sound("vox/locked.wav");
	precache_sound("vox/locker.wav");
	precache_sound("vox/lockout.wav");
	precache_sound("vox/lock.wav");
	precache_sound("vox/lower.wav");
	precache_sound("vox/lowest.wav");
	precache_sound("vox/magnetic.wav");
	precache_sound("vox/maintenance.wav");
	precache_sound("vox/main.wav");
	precache_sound("vox/malfunction.wav");
	precache_sound("vox/man.wav");
	precache_sound("vox/mass.wav");
	precache_sound("vox/materials.wav");
	precache_sound("vox/maximum.wav");
	precache_sound("vox/may.wav");
	precache_sound("vox/medical.wav");
	precache_sound("vox/men.wav");
	precache_sound("vox/mercy.wav");
	precache_sound("vox/mesa.wav");
	precache_sound("vox/message.wav");
	precache_sound("vox/meter.wav");
	precache_sound("vox/micro.wav");
	precache_sound("vox/middle.wav");
	precache_sound("vox/mike.wav");
	precache_sound("vox/miles.wav");
	precache_sound("vox/military.wav");
	precache_sound("vox/million.wav");
	precache_sound("vox/milli.wav");
	precache_sound("vox/minefield.wav");
	precache_sound("vox/minimum.wav");
	precache_sound("vox/minutes.wav");
	precache_sound("vox/mister.wav");
	precache_sound("vox/mode.wav");
	precache_sound("vox/motorpool.wav");
	precache_sound("vox/motor.wav");
	precache_sound("vox/move.wav");
	precache_sound("vox/must.wav");
	precache_sound("vox/nearest.wav");
	precache_sound("vox/nice.wav");
	precache_sound("vox/nineteen.wav");
	precache_sound("vox/ninety.wav");
	precache_sound("vox/nine.wav");
	precache_sound("vox/nominal.wav");
	precache_sound("vox/north.wav");
	precache_sound("vox/not.wav");
	precache_sound("vox/november.wav");
	precache_sound("vox/no.wav");
	precache_sound("vox/now.wav");
	precache_sound("vox/number.wav");
	precache_sound("vox/objective.wav");
	precache_sound("vox/observation.wav");
	precache_sound("vox/officer.wav");
	precache_sound("vox/of.wav");
	precache_sound("vox/ok.wav");
	precache_sound("vox/one.wav");
	precache_sound("vox/on.wav");
	precache_sound("vox/open.wav");
	precache_sound("vox/operating.wav");
	precache_sound("vox/operations.wav");
	precache_sound("vox/operative.wav");
	precache_sound("vox/option.wav");
	precache_sound("vox/order.wav");
	precache_sound("vox/organic.wav");
	precache_sound("vox/oscar.wav");
	precache_sound("vox/outside.wav");
	precache_sound("vox/out.wav");
	precache_sound("vox/overload.wav");
	precache_sound("vox/override.wav");
	precache_sound("vox/over.wav");
	precache_sound("vox/pacify.wav");
	precache_sound("vox/pain.wav");
	precache_sound("vox/pal.wav");
	precache_sound("vox/panel.wav");
	precache_sound("vox/percent.wav");
	precache_sound("vox/perimeter.wav");
	precache_sound("vox/_period.wav");
	precache_sound("vox/permitted.wav");
	precache_sound("vox/personnel.wav");
	precache_sound("vox/pipe.wav");
	precache_sound("vox/plant.wav");
	precache_sound("vox/platform.wav");
	precache_sound("vox/please.wav");
	precache_sound("vox/point.wav");
	precache_sound("vox/portal.wav");
	precache_sound("vox/power.wav");
	precache_sound("vox/presence.wav");
	precache_sound("vox/press.wav");
	precache_sound("vox/primary.wav");
	precache_sound("vox/proceed.wav");
	precache_sound("vox/processing.wav");
	precache_sound("vox/progress.wav");
	precache_sound("vox/proper.wav");
	precache_sound("vox/propulsion.wav");
	precache_sound("vox/prosecute.wav");
	precache_sound("vox/protective.wav");
	precache_sound("vox/push.wav");
	precache_sound("vox/quantum.wav");
	precache_sound("vox/quebec.wav");
	precache_sound("vox/questioning.wav");
	precache_sound("vox/question.wav");
	precache_sound("vox/quick.wav");
	precache_sound("vox/quit.wav");
	precache_sound("vox/radiation.wav");
	precache_sound("vox/radioactive.wav");
	precache_sound("vox/rads.wav");
	precache_sound("vox/rapid.wav");
	precache_sound("vox/reached.wav");
	precache_sound("vox/reach.wav");
	precache_sound("vox/reactor.wav");
	precache_sound("vox/red.wav");
	precache_sound("vox/relay.wav");
	precache_sound("vox/released.wav");
	precache_sound("vox/remaining.wav");
	precache_sound("vox/renegade.wav");
	precache_sound("vox/repair.wav");
	precache_sound("vox/reports.wav");
	precache_sound("vox/report.wav");
	precache_sound("vox/required.wav");
	precache_sound("vox/research.wav");
	precache_sound("vox/resevoir.wav");
	precache_sound("vox/resistance.wav");
	precache_sound("vox/right.wav");
	precache_sound("vox/rocket.wav");
	precache_sound("vox/roger.wav");
	precache_sound("vox/romeo.wav");
	precache_sound("vox/room.wav");
	precache_sound("vox/round.wav");
	precache_sound("vox/run.wav");
	precache_sound("vox/safety.wav");
	precache_sound("vox/safe.wav");
	precache_sound("vox/sargeant.wav");
	precache_sound("vox/satellite.wav");
	precache_sound("vox/save.wav");
	precache_sound("vox/science.wav");
	precache_sound("vox/scream.wav");
	precache_sound("vox/screen.wav");
	precache_sound("vox/search.wav");
	precache_sound("vox/secondary.wav");
	precache_sound("vox/seconds.wav");
	precache_sound("vox/second.wav");
	precache_sound("vox/sector.wav");
	precache_sound("vox/secured.wav");
	precache_sound("vox/secure.wav");
	precache_sound("vox/security.wav");
	precache_sound("vox/selected.wav");
	precache_sound("vox/select.wav");
	precache_sound("vox/service.wav");
	precache_sound("vox/seventeen.wav");
	precache_sound("vox/seventy.wav");
	precache_sound("vox/seven.wav");
	precache_sound("vox/severe.wav");
	precache_sound("vox/sewage.wav");
	precache_sound("vox/sewer.wav");
	precache_sound("vox/shield.wav");
	precache_sound("vox/shipment.wav");
	precache_sound("vox/shock.wav");
	precache_sound("vox/shoot.wav");
	precache_sound("vox/shower.wav");
	precache_sound("vox/shut.wav");
	precache_sound("vox/side.wav");
	precache_sound("vox/sierra.wav");
	precache_sound("vox/sight.wav");
	precache_sound("vox/silo.wav");
	precache_sound("vox/sixteen.wav");
	precache_sound("vox/sixty.wav");
	precache_sound("vox/six.wav");
	precache_sound("vox/slime.wav");
	precache_sound("vox/slow.wav");
	precache_sound("vox/soldier.wav");
	precache_sound("vox/someone.wav");
	precache_sound("vox/something.wav");
	precache_sound("vox/some.wav");
	precache_sound("vox/son.wav");
	precache_sound("vox/sorry.wav");
	precache_sound("vox/south.wav");
	precache_sound("vox/squad.wav");
	precache_sound("vox/square.wav");
	precache_sound("vox/stairway.wav");
	precache_sound("vox/status.wav");
	precache_sound("vox/sterile.wav");
	precache_sound("vox/sterilization.wav");
	precache_sound("vox/storage.wav");
	precache_sound("vox/subsurface.wav");
	precache_sound("vox/sub.wav");
	precache_sound("vox/sudden.wav");
	precache_sound("vox/suit.wav");
	precache_sound("vox/superconducting.wav");
	precache_sound("vox/supercooled.wav");
	precache_sound("vox/supply.wav");
	precache_sound("vox/surface.wav");
	precache_sound("vox/surrender.wav");
	precache_sound("vox/surrounded.wav");
	precache_sound("vox/surround.wav");
	precache_sound("vox/switch.wav");
	precache_sound("vox/systems.wav");
	precache_sound("vox/system.wav");
	precache_sound("vox/tactical.wav");
	precache_sound("vox/take.wav");
	precache_sound("vox/talk.wav");
	precache_sound("vox/tango.wav");
	precache_sound("vox/tank.wav");
	precache_sound("vox/target.wav");
	precache_sound("vox/team.wav");
	precache_sound("vox/temperature.wav");
	precache_sound("vox/temporal.wav");
	precache_sound("vox/ten.wav");
	precache_sound("vox/terminal.wav");
	precache_sound("vox/terminated.wav");
	precache_sound("vox/termination.wav");
	precache_sound("vox/test.wav");
	precache_sound("vox/that.wav");
	precache_sound("vox/then.wav");
	precache_sound("vox/there.wav");
	precache_sound("vox/the.wav");
	precache_sound("vox/third.wav");
	precache_sound("vox/thirteen.wav");
	precache_sound("vox/thirty.wav");
	precache_sound("vox/this.wav");
	precache_sound("vox/those.wav");
	precache_sound("vox/thousand.wav");
	precache_sound("vox/threat.wav");
	precache_sound("vox/three.wav");
	precache_sound("vox/through.wav");
	precache_sound("vox/time.wav");
	precache_sound("vox/topside.wav");
	precache_sound("vox/top.wav");
	precache_sound("vox/touch.wav");
	precache_sound("vox/towards.wav");
	precache_sound("vox/to.wav");
	precache_sound("vox/track.wav");
	precache_sound("vox/train.wav");
	precache_sound("vox/transportation.wav");
	precache_sound("vox/truck.wav");
	precache_sound("vox/tunnel.wav");
	precache_sound("vox/turn.wav");
	precache_sound("vox/turret.wav");
	precache_sound("vox/twelve.wav");
	precache_sound("vox/twenty.wav");
	precache_sound("vox/two.wav");
	precache_sound("vox/unauthorized.wav");
	precache_sound("vox/under.wav");
	precache_sound("vox/uniform.wav");
	precache_sound("vox/unlocked.wav");
	precache_sound("vox/until.wav");
	precache_sound("vox/upper.wav");
	precache_sound("vox/up.wav");
	precache_sound("vox/uranium.wav");
	precache_sound("vox/usa.wav");
	precache_sound("vox/used.wav");
	precache_sound("vox/user.wav");
	precache_sound("vox/use.wav");
	precache_sound("vox/us.wav");
	precache_sound("vox/vacate.wav");
	precache_sound("vox/valid.wav");
	precache_sound("vox/vapor.wav");
	precache_sound("vox/ventillation.wav");
	precache_sound("vox/vent.wav");
	precache_sound("vox/victor.wav");
	precache_sound("vox/violated.wav");
	precache_sound("vox/violation.wav");
	precache_sound("vox/voltage.wav");
	precache_sound("vox/vox_login.wav");
	precache_sound("vox/walk.wav");
	precache_sound("vox/wall.wav");
	precache_sound("vox/wanted.wav");
	precache_sound("vox/want.wav");
	precache_sound("vox/warm.wav");
	precache_sound("vox/warning.wav");
	precache_sound("vox/warn.wav");
	precache_sound("vox/waste.wav");
	precache_sound("vox/water.wav");
	precache_sound("vox/weapon.wav");
	precache_sound("vox/west.wav");
	precache_sound("vox/we.wav");
	precache_sound("vox/whiskey.wav");
	precache_sound("vox/white.wav");
	precache_sound("vox/wilco.wav");
	precache_sound("vox/will.wav");
	precache_sound("vox/without.wav");
	precache_sound("vox/with.wav");
	precache_sound("vox/woop.wav");
	precache_sound("vox/xeno.wav");
	precache_sound("vox/yankee.wav");
	precache_sound("vox/yards.wav");
	precache_sound("vox/year.wav");
	precache_sound("vox/yellow.wav");
	precache_sound("vox/yes.wav");
	precache_sound("vox/yourself.wav");
	precache_sound("vox/your.wav");
	precache_sound("vox/you.wav");
	precache_sound("vox/zero.wav");
	precache_sound("vox/zone.wav");
	precache_sound("vox/zulu.wav");
}
