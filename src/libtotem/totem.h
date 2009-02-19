/* 
 * Copyright (C) 2001,2002,2003,2004,2005 Bastien Nocera <hadess@hadess.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
 *
 * The Totem project hereby grant permission for non-gpl compatible GStreamer
 * plugins to be used and distributed together with GStreamer and Totem. This
 * permission are above and beyond the permissions granted by the GPL license
 * Totem is covered by.
 *
 * Monday 7th February 2005: Christian Schaller: Add exception clause.
 * See license_change file for details.
 *
 */

#ifndef __TOTEM_H__
#define __TOTEM_H__

#include <glib-object.h>
#include <gtk/gtk.h>
#include <totem-disc.h>
#include "totem-playlist.h"

#define TOTEM_GCONF_PREFIX "/apps/totem"

G_BEGIN_DECLS

typedef enum {
	TOTEM_REMOTE_COMMAND_UNKNOWN,
	TOTEM_REMOTE_COMMAND_PLAY,
	TOTEM_REMOTE_COMMAND_PAUSE,
	TOTEM_REMOTE_COMMAND_STOP,
	TOTEM_REMOTE_COMMAND_PLAYPAUSE,
	TOTEM_REMOTE_COMMAND_NEXT,
	TOTEM_REMOTE_COMMAND_PREVIOUS,
	TOTEM_REMOTE_COMMAND_SEEK_FORWARD,
	TOTEM_REMOTE_COMMAND_SEEK_BACKWARD,
	TOTEM_REMOTE_COMMAND_VOLUME_UP,
	TOTEM_REMOTE_COMMAND_VOLUME_DOWN,
	TOTEM_REMOTE_COMMAND_FULLSCREEN,
	TOTEM_REMOTE_COMMAND_QUIT,
	TOTEM_REMOTE_COMMAND_ENQUEUE,
	TOTEM_REMOTE_COMMAND_REPLACE,
	TOTEM_REMOTE_COMMAND_SHOW,
	TOTEM_REMOTE_COMMAND_TOGGLE_CONTROLS,
	TOTEM_REMOTE_COMMAND_SHOW_PLAYING,
	TOTEM_REMOTE_COMMAND_SHOW_VOLUME,
	TOTEM_REMOTE_COMMAND_UP,
	TOTEM_REMOTE_COMMAND_DOWN,
	TOTEM_REMOTE_COMMAND_LEFT,
	TOTEM_REMOTE_COMMAND_RIGHT,
	TOTEM_REMOTE_COMMAND_SELECT,
	TOTEM_REMOTE_COMMAND_DVD_MENU,
	TOTEM_REMOTE_COMMAND_ZOOM_UP,
	TOTEM_REMOTE_COMMAND_ZOOM_DOWN,
	TOTEM_REMOTE_COMMAND_EJECT,
	TOTEM_REMOTE_COMMAND_PLAY_DVD,
	TOTEM_REMOTE_COMMAND_MUTE,
	TOTEM_REMOTE_COMMAND_TOGGLE_ASPECT
} TotemRemoteCommand;

typedef enum {
	TOTEM_REMOTE_SETTING_SHUFFLE,
	TOTEM_REMOTE_SETTING_REPEAT
} TotemRemoteSetting;

G_MODULE_EXPORT GType totem_remote_command_get_type	(void);
G_MODULE_EXPORT GQuark totem_remote_command_quark	(void);
#define TOTEM_TYPE_REMOTE_COMMAND	(totem_remote_command_get_type())
#define TOTEM_REMOTE_COMMAND		totem_remote_command_quark ()

G_MODULE_EXPORT GType totem_disc_media_type_get_type	(void);
G_MODULE_EXPORT GQuark totem_disc_media_type_quark	(void);
#define TOTEM_TYPE_DISC_MEDIA_TYPE	(totem_disc_media_type_get_type())
#define TOTEM_DISC_MEDIA_TYPE		totem_disc_media_type_quark ()

#define SHOW_PLAYING_NO_TRACKS "NONE"

#define TOTEM_TYPE_OBJECT              (totem_object_get_type ())
#define TOTEM_OBJECT(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), totem_object_get_type (), TotemObject))
#define TOTEM_OBJECT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), totem_object_get_type (), TotemObjectClass))
#define TOTEM_IS_OBJECT(obj)           (G_TYPE_CHECK_INSTANCE_TYPE (obj, totem_object_get_type ()))
#define TOTEM_IS_OBJECT_CLASS(klass)   (G_CHECK_INSTANCE_GET_CLASS ((klass), totem_object_get_type ()))

typedef struct TotemObject Totem;
typedef struct TotemObject TotemObject;

typedef struct {
	GObjectClass parent_class;

	void (*file_opened)			(Totem *totem, const char *mrl);
	void (*file_closed)			(Totem *totem);
	void (*metadata_updated)		(Totem *totem,
						 const char *artist,
						 const char *title,
						 const char *album,
						 guint track_num);
} TotemObjectClass;

G_MODULE_EXPORT GType	totem_object_get_type			(void);
G_MODULE_EXPORT void    totem_object_plugins_init		(TotemObject *totem);
G_MODULE_EXPORT void    totem_object_plugins_shutdown		(void);
G_MODULE_EXPORT void	totem_file_opened			(TotemObject *totem,
						 const char *mrl);
G_MODULE_EXPORT void	totem_file_closed			(TotemObject *totem);
G_MODULE_EXPORT void	totem_metadata_updated			(TotemObject *totem,
						 const char *artist,
						 const char *title,
						 const char *album,
						 guint track_num);

G_MODULE_EXPORT void	totem_action_exit			(Totem *totem) G_GNUC_NORETURN;
G_MODULE_EXPORT void	totem_action_play			(Totem *totem);
G_MODULE_EXPORT void	totem_action_stop			(Totem *totem);
G_MODULE_EXPORT void	totem_action_play_pause			(Totem *totem);
G_MODULE_EXPORT void	totem_action_pause			(Totem *totem);
G_MODULE_EXPORT void	totem_action_fullscreen_toggle		(Totem *totem);
G_MODULE_EXPORT void	totem_action_fullscreen			(Totem *totem, gboolean state);
G_MODULE_EXPORT void	totem_action_next			(Totem *totem);
G_MODULE_EXPORT void	totem_action_previous			(Totem *totem);
G_MODULE_EXPORT void	totem_action_seek_time			(Totem *totem, gint64 sec);
G_MODULE_EXPORT void	totem_action_seek_relative		(Totem *totem, gint64 offset);
G_MODULE_EXPORT void	totem_action_volume_relative		(Totem *totem, double off_pct);
G_MODULE_EXPORT void	totem_action_volume_toggle_mute		(Totem *totem);
G_MODULE_EXPORT gboolean totem_action_set_mrl			(Totem *totem,
						 const char *mrl,
						 const char *subtitle);
G_MODULE_EXPORT void	totem_action_set_mrl_and_play		(Totem *totem,
						 const char *mrl, 
						 const char *subtitle);

G_MODULE_EXPORT gboolean totem_action_set_mrl_with_warning	(Totem *totem,
						 const char *mrl,
						 const char *subtitle,
						 gboolean warn);

G_MODULE_EXPORT void	totem_action_play_media			(Totem *totem,
						 TotemDiscMediaType type,
						 const char *device);

G_MODULE_EXPORT void	totem_action_toggle_aspect_ratio	(Totem *totem);
G_MODULE_EXPORT void	totem_action_set_aspect_ratio		(Totem *totem, int ratio);
G_MODULE_EXPORT int	totem_action_get_aspect_ratio		(Totem *totem);
G_MODULE_EXPORT void	totem_action_toggle_controls		(Totem *totem);
G_MODULE_EXPORT void	totem_action_next_angle			(Totem *totem);

G_MODULE_EXPORT void	totem_action_set_scale_ratio		(Totem *totem, gfloat ratio);
G_MODULE_EXPORT void    totem_action_error                      (const char *title,
						 const char *reason,
						 Totem *totem);
G_MODULE_EXPORT void    totem_action_play_media_device		(Totem *totem,
						 const char *device);

G_MODULE_EXPORT gboolean totem_is_fullscreen			(Totem *totem);
G_MODULE_EXPORT gboolean totem_is_playing			(Totem *totem);
G_MODULE_EXPORT gboolean totem_is_paused			(Totem *totem);
G_MODULE_EXPORT gboolean totem_is_seekable			(Totem *totem);
G_MODULE_EXPORT GtkWindow *totem_get_main_window		(Totem *totem);
G_MODULE_EXPORT GtkUIManager *totem_get_ui_manager		(Totem *totem);
G_MODULE_EXPORT GtkWidget *totem_get_video_widget		(Totem *totem);
G_MODULE_EXPORT char *totem_get_video_widget_backend_name	(Totem *totem);

/* Current media information */
G_MODULE_EXPORT char *	totem_get_short_title			(Totem *totem);
G_MODULE_EXPORT gint64	totem_get_current_time			(Totem *totem);

/* Playlist handling */
G_MODULE_EXPORT guint	totem_get_playlist_length		(Totem *totem);
G_MODULE_EXPORT void	totem_action_set_playlist_index		(Totem *totem,
						 guint index);
G_MODULE_EXPORT int	totem_get_playlist_pos			(Totem *totem);
G_MODULE_EXPORT char *	totem_get_title_at_playlist_pos		(Totem *totem,
						 guint index);
G_MODULE_EXPORT void totem_add_to_playlist_and_play		(Totem *totem,
						 const char *uri,
						 const char *display_name,
						 gboolean add_to_recent);
G_MODULE_EXPORT char *  totem_get_current_mrl			(Totem *totem);
G_MODULE_EXPORT void	totem_set_current_subtitle		(Totem *totem,
						 const char *subtitle_uri);
/* Sidebar handling */
G_MODULE_EXPORT void    totem_add_sidebar_page			(Totem *totem,
						 const char *page_id,
						 const char *title,
						 GtkWidget *main_widget);
G_MODULE_EXPORT void    totem_remove_sidebar_page		(Totem *totem,
						 const char *page_id);

/* Remote actions */
G_MODULE_EXPORT void    totem_action_remote			(Totem *totem,
						 TotemRemoteCommand cmd,
						 const char *url);
G_MODULE_EXPORT void	totem_action_remote_set_setting		(Totem *totem,
						 TotemRemoteSetting setting,
						 gboolean value);
G_MODULE_EXPORT gboolean totem_action_remote_get_setting	(Totem *totem,
						 TotemRemoteSetting setting);

#endif /* __TOTEM_H__ */
