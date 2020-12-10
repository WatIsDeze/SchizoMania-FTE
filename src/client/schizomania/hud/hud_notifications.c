/*
 * Copyright (c) 2020 Mike Poortman <someemail@mail.com>
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
//=========================================================================
// HUD NOTIFICATION IMPLEMENTATION.
//
// Events, such as during the introduction scene where the player gets
// instructions about the gameplay controls. Or, when picking up an item,
// and other interactions that may want to inform the player.
//
// It works as a stash list, it'll work all the events in FIFO order.
// In case an animation is finished, it's state is set to inactive and
// a new slot frees up again for a new notification push.
//=========================================================================
// Notification sizes.
#define HUD_NOTIFICATION_SMALL 0
#define HUD_NOTIFICATION_LARGE 1

// Notification struct and list.
typedef struct
{
	string m_strMessage;

    int m_iStyle;
    int m_iIsActive;

    float m_flAlpha;
	float m_flTotalTime;
    float m_flFadeTime;
    float m_flDuration;
} HUDNotification_t;
HUDNotification_t g_hudnotifications[5];

// Counter used to identify which last slot is free.
static int g_hudnotification_count;

//=======================
// void HUDNotification_Init(void) 
//
// Ensures our list has free slots.
//=======================
void
HUDNotification_Init()
{
    for (int i = 0; i < 5; i++) {
        g_hudnotifications[i].m_iIsActive = FALSE;
    }
}

//=======================
// void HUDNotification_PushNotification(string message, float duration, int style) 
//
// Adds a hud notification to the stack, with the given duration and style.
//
// Style options:
// - HUD_NOTIFICATION_SMALL useful for one lines, like picking up items.
// - HUD_NOTIFICATION_LARGE useful for larger information such as player instructions.
//=======================
void 
HUDNotification_PushNotification(string message, float duration, int style) 
{
    // Find a notification slot that isn't active.
    int position = -1;
    for (int i = 0; i < 5; i++) {
        if (g_hudnotifications[i].m_iIsActive == FALSE) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        dprint(sprintf("Too many hud notifications stashed, disregarding message: '%s'\n", message));
        return;
    }
    g_hudnotifications[position].m_iStyle      = style;
    g_hudnotifications[position].m_iIsActive   = TRUE;
 	g_hudnotifications[position].m_strMessage  = message;
    g_hudnotifications[position].m_flDuration  = duration;
	g_hudnotifications[position].m_flTotalTime = 0;
	g_hudnotifications[position].m_flFadeTime  = 0;

}

//=======================
// void HUDNotification_DrawString(vector pos, string msg, vector col, float alpha)
//
// Draws the given string accordingly with new lines support.
//
// TODO: Implement a max size rect, so it automatically goes to new lines
// if the last word exceeds the allowed limits.
//=======================
void
HUDNotification_DrawString(vector pos, string msg, vector col, float alpha)
{
	vector rpos;
	int c = tokenizebyseparator(msg, "\n");
	
    // Hack:
    // Clamp alpha to prevent it from bugging it.
    if (alpha < 0)
        alpha = 0;
    if (alpha > 1)
        alpha = 1;

	for (int i = 0; i < c; i++) {
		float strwidth = stringwidth(argv(i), TRUE, [18,18]);
		pos[1] += 18 * i;
		drawstring(pos, argv(i), '18 18', col, alpha,
			0);
	}
}

//=======================
// void HUDNotification_DrawNotification(int i)
//
// Draws the given notification.
//
// Automatically handles the time, and resets the state when
// the notification has completed.
//=======================
void
HUDNotification_DrawNotification(int i)
{
    float totalTime = g_hudnotifications[i].m_flTotalTime;
    float fadeTime = g_hudnotifications[i].m_flFadeTime;
    float duration = g_hudnotifications[i].m_flDuration;

    vector pos;
    float a = 0.0f;    

    if (totalTime < duration) {
        // Fade in.
        if (totalTime < 0.35) {
            g_hudnotifications[i].m_flAlpha += (1.0 / 0.35) * clframetime;
        }

        // Fade out.
        if (totalTime > duration - 0.35) {
            g_hudnotifications[i].m_flAlpha -= (1.0 / 0.35) * clframetime;
        }

        // Render appropriate background.
        if (g_hudnotifications[i].m_iStyle == HUD_NOTIFICATION_SMALL) {
            drawpic([0, 0], "textures/hud/hud_notification_lt_small.tga", [512, 192], [1,1,1], g_hudnotifications[i].m_flAlpha, 0);
        }
        if (g_hudnotifications[i].m_iStyle == HUD_NOTIFICATION_LARGE) {
            drawpic([0, 0], "textures/hud/hud_notification_lt_large.tga", [512, 512], [1,1,1], g_hudnotifications[i].m_flAlpha, 0);
        }

        // Last but not least, our sweet text.
        HUDNotification_DrawString([24, 24], g_hudnotifications[i].m_strMessage, [1, 1, 1], g_hudnotifications[i].m_flAlpha);
    } else {
        g_hudnotifications[i].m_iIsActive = FALSE;
    }
}

//=======================
// void HUDNotification_Draw(void)
//
// Called each frame to render notifications.
// Stops at the first sign of finding an active notification.
// The other in-line will have to wait :)
//=======================
void
HUDNotification_Draw(void)
{
	drawfont = FONT_HUD_NOTIFICATION;
	for (int i = 0; i < 5; i++) {
        if (g_hudnotifications[i].m_iIsActive == TRUE) {
            HUDNotification_DrawNotification(i);
            g_hudnotifications[i].m_flTotalTime += clframetime;
            break;
        }
	}
	drawfont = FONT_CON;
}
