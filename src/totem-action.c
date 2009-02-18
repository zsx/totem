#include "config.h"

#include <glib/gi18n.h>

#include "bacon-video-widget.h"
#include "totem-statusbar.h"
#include "totem-uri.h"
#include "totem-time-label.h"
#include "totem.h"
#include "totem-private.h"

static void
totem_seek_time_rel (Totem *totem, gint64 time, gboolean relative)
{
	GError *err = NULL;
	gint64 sec;

	if (totem->mrl == NULL)
		return;
	if (bacon_video_widget_is_seekable (totem->bvw) == FALSE)
		return;

	totem_statusbar_set_seeking (TOTEM_STATUSBAR (totem->statusbar), TRUE);
	totem_time_label_set_seeking (TOTEM_TIME_LABEL (totem->fs->time_label), TRUE);

	if (relative != FALSE) {
		gint64 oldmsec;
		oldmsec = bacon_video_widget_get_current_time (totem->bvw);
		sec = MAX (0, oldmsec + time);
	} else {
		sec = time;
	}

	bacon_video_widget_seek_time (totem->bvw, sec, &err);

	totem_statusbar_set_seeking (TOTEM_STATUSBAR (totem->statusbar), FALSE);
	totem_time_label_set_seeking (TOTEM_TIME_LABEL (totem->fs->time_label), FALSE);

	if (err != NULL)
	{
		char *msg, *disp;

		disp = totem_uri_escape_for_display (totem->mrl);
		msg = g_strdup_printf(_("Totem could not play '%s'."), disp);
		g_free (disp);

		totem_action_stop (totem);
		totem_action_error (msg, err->message, totem);
		g_free (msg);
		g_error_free (err);
	}
}

/**
 * totem_action_seek_time:
 * @totem: a #TotemObject
 * @sec: the time to seek to
 *
 * Seeks to an absolute time in the stream, or displays an
 * error dialog if that's not possible.
 **/
void
totem_action_seek_time (Totem *totem, gint64 sec)
{
	totem_seek_time_rel (totem, sec, FALSE);
}

/**
 * totem_action_seek_relative:
 * @totem: a #TotemObject
 * @offset: the time offset to seek to
 *
 * Seeks to an @offset from the current position in the stream,
 * or displays an error dialog if that's not possible.
 **/
void
totem_action_seek_relative (Totem *totem, gint64 offset)
{
	totem_seek_time_rel (totem, offset, TRUE);
}

/**
 * totem_is_playing:
 * @totem: a #TotemObject
 *
 * Returns %TRUE if Totem is playing a stream.
 *
 * Return value: %TRUE if Totem is playing a stream
 **/
gboolean
totem_is_playing (Totem *totem)
{
	g_return_val_if_fail (TOTEM_IS_OBJECT (totem), FALSE);

	if (totem->bvw == NULL)
		return FALSE;

	return bacon_video_widget_is_playing (totem->bvw) != FALSE;
}

/**
 * totem_is_seekable:
 * @totem: a #TotemObject
 *
 * Returns %TRUE if the current stream is seekable.
 *
 * Return value: %TRUE if the current stream is seekable
 **/
gboolean
totem_is_seekable (Totem *totem)
{
	g_return_val_if_fail (TOTEM_IS_OBJECT (totem), FALSE);

	if (totem->bvw == NULL)
		return FALSE;

	return bacon_video_widget_is_seekable (totem->bvw) != FALSE;
}

/**
 * totem_is_fullscreen:
 * @totem: a #TotemObject
 *
 * Returns %TRUE if Totem is fullscreened.
 *
 * Return value: %TRUE if Totem is fullscreened
 **/
gboolean
totem_is_fullscreen (Totem *totem)
{
	g_return_val_if_fail (TOTEM_IS_OBJECT (totem), FALSE);

	return (totem->controls_visibility == TOTEM_CONTROLS_FULLSCREEN);
}

