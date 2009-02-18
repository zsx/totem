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

#ifndef HAVE_BACON_VIDEO_WIDGET_H
#define HAVE_BACON_VIDEO_WIDGET_H

#include <gtk/gtk.h>
/* for optical disc enumeration type */
#include <totem-disc.h>

G_BEGIN_DECLS
#define BACON_TYPE_VIDEO_WIDGET		     (bacon_video_widget_get_type ())
#define BACON_VIDEO_WIDGET(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), bacon_video_widget_get_type (), BaconVideoWidget))
#define BACON_VIDEO_WIDGET_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), bacon_video_widget_get_type (), BaconVideoWidgetClass))
#define BACON_IS_VIDEO_WIDGET(obj)           (G_TYPE_CHECK_INSTANCE_TYPE (obj, bacon_video_widget_get_type ()))
#define BACON_IS_VIDEO_WIDGET_CLASS(klass)   (G_CHECK_INSTANCE_GET_CLASS ((klass), bacon_video_widget_get_type ()))
#define BVW_ERROR bacon_video_widget_error_quark ()

typedef struct BaconVideoWidgetPrivate BaconVideoWidgetPrivate;
typedef struct BaconVideoWidgetCommon BaconVideoWidgetCommon;

typedef struct {
	GtkEventBox parent;
	BaconVideoWidgetCommon *com;
	BaconVideoWidgetPrivate *priv;
} BaconVideoWidget;

typedef struct {
	GtkEventBoxClass parent_class;

	void (*error) (GtkWidget *bvw, const char *message,
                       gboolean playback_stopped, gboolean fatal);
	void (*eos) (GtkWidget *bvw);
	void (*got_metadata) (GtkWidget *bvw);
	void (*got_redirect) (GtkWidget *bvw, const char *mrl);
	void (*title_change) (GtkWidget *bvw, const char *title);
	void (*channels_change) (GtkWidget *bvw);
	void (*tick) (GtkWidget *bvw, gint64 current_time, gint64 stream_length,
			double current_position, gboolean seekable);
	void (*buffering) (GtkWidget *bvw, guint progress);
} BaconVideoWidgetClass;

typedef enum {
	/* Plugins */
	BVW_ERROR_AUDIO_PLUGIN,
	BVW_ERROR_NO_PLUGIN_FOR_FILE,
	BVW_ERROR_VIDEO_PLUGIN,
	BVW_ERROR_AUDIO_BUSY,
	/* File */
	BVW_ERROR_BROKEN_FILE,
	BVW_ERROR_FILE_GENERIC,
	BVW_ERROR_FILE_PERMISSION,
	BVW_ERROR_FILE_ENCRYPTED,
	BVW_ERROR_FILE_NOT_FOUND,
	/* Devices */
	BVW_ERROR_DVD_ENCRYPTED,
	BVW_ERROR_INVALID_DEVICE,
	BVW_ERROR_DEVICE_BUSY,
	/* Network */
	BVW_ERROR_UNKNOWN_HOST,
	BVW_ERROR_NETWORK_UNREACHABLE,
	BVW_ERROR_CONNECTION_REFUSED,
	/* Generic */
	BVW_ERROR_UNVALID_LOCATION,
	BVW_ERROR_GENERIC,
	BVW_ERROR_CODEC_NOT_HANDLED,
	BVW_ERROR_AUDIO_ONLY,
	BVW_ERROR_CANNOT_CAPTURE,
	BVW_ERROR_READ_ERROR,
	BVW_ERROR_PLUGIN_LOAD,
	BVW_ERROR_EMPTY_FILE
} BvwError;

G_MODULE_EXPORT GQuark bacon_video_widget_error_quark		 (void) G_GNUC_CONST;
G_MODULE_EXPORT GType bacon_video_widget_get_type                (void);
G_MODULE_EXPORT GOptionGroup* bacon_video_widget_get_option_group (void);
/* This can be used if the app does not use popt */
G_MODULE_EXPORT void bacon_video_widget_init_backend		 (int *argc, char ***argv);

typedef enum {
	BVW_USE_TYPE_VIDEO,
	BVW_USE_TYPE_AUDIO,
	BVW_USE_TYPE_CAPTURE,
	BVW_USE_TYPE_METADATA
} BvwUseType;

G_MODULE_EXPORT GtkWidget *bacon_video_widget_new		 (int width, int height,
						  BvwUseType type,
						  GError **error);

G_MODULE_EXPORT char *bacon_video_widget_get_backend_name (BaconVideoWidget *bvw);

/* Actions */
#define bacon_video_widget_open(bvw, mrl, error) bacon_video_widget_open_with_subtitle(bvw, mrl, NULL, error)
G_MODULE_EXPORT gboolean bacon_video_widget_open_with_subtitle	 (BaconVideoWidget *bvw,
						  const char *mrl,
						  const char *subtitle_uri,
						  GError **error);
G_MODULE_EXPORT gboolean bacon_video_widget_play                 (BaconVideoWidget *bvw,
						  GError **error);
G_MODULE_EXPORT void bacon_video_widget_pause			 (BaconVideoWidget *bvw);
G_MODULE_EXPORT gboolean bacon_video_widget_is_playing           (BaconVideoWidget *bvw);

/* Seeking and length */
G_MODULE_EXPORT gboolean bacon_video_widget_is_seekable          (BaconVideoWidget *bvw);
G_MODULE_EXPORT gboolean bacon_video_widget_seek		 (BaconVideoWidget *bvw,
						  double position,
						  GError **error);
G_MODULE_EXPORT gboolean bacon_video_widget_seek_time		 (BaconVideoWidget *bvw,
						  gint64 time,
						  GError **error);
G_MODULE_EXPORT gboolean bacon_video_widget_can_direct_seek	 (BaconVideoWidget *bvw);
G_MODULE_EXPORT double bacon_video_widget_get_position           (BaconVideoWidget *bvw);
G_MODULE_EXPORT gint64 bacon_video_widget_get_current_time       (BaconVideoWidget *bvw);
G_MODULE_EXPORT gint64 bacon_video_widget_get_stream_length      (BaconVideoWidget *bvw);

G_MODULE_EXPORT void bacon_video_widget_stop                     (BaconVideoWidget *bvw);
G_MODULE_EXPORT void bacon_video_widget_close                    (BaconVideoWidget *bvw);

/* Audio volume */
G_MODULE_EXPORT gboolean bacon_video_widget_can_set_volume       (BaconVideoWidget *bvw);
G_MODULE_EXPORT void bacon_video_widget_set_volume               (BaconVideoWidget *bvw,
						  double volume);
G_MODULE_EXPORT double bacon_video_widget_get_volume             (BaconVideoWidget *bvw);

/* Properties */
G_MODULE_EXPORT void bacon_video_widget_set_logo		 (BaconVideoWidget *bvw,
						  char *filename);
G_MODULE_EXPORT void bacon_video_widget_set_logo_pixbuf		 (BaconVideoWidget *bvw,
						  GdkPixbuf *logo);
G_MODULE_EXPORT void  bacon_video_widget_set_logo_mode		 (BaconVideoWidget *bvw,
						  gboolean logo_mode);
G_MODULE_EXPORT gboolean bacon_video_widget_get_logo_mode	 (BaconVideoWidget *bvw);

G_MODULE_EXPORT void bacon_video_widget_set_fullscreen		 (BaconVideoWidget *bvw,
						  gboolean fullscreen);

G_MODULE_EXPORT void bacon_video_widget_set_show_cursor          (BaconVideoWidget *bvw,
						  gboolean use_cursor);
G_MODULE_EXPORT gboolean bacon_video_widget_get_show_cursor      (BaconVideoWidget *bvw);

G_MODULE_EXPORT gboolean bacon_video_widget_get_auto_resize	 (BaconVideoWidget *bvw);
G_MODULE_EXPORT void bacon_video_widget_set_auto_resize		 (BaconVideoWidget *bvw,
						  gboolean auto_resize);

G_MODULE_EXPORT void bacon_video_widget_set_connection_speed     (BaconVideoWidget *bvw,
						  int speed);
G_MODULE_EXPORT int bacon_video_widget_get_connection_speed      (BaconVideoWidget *bvw);

G_MODULE_EXPORT gchar **bacon_video_widget_get_mrls		 (BaconVideoWidget *bvw,
						  TotemDiscMediaType type,
						  const char *device,
						  GError **error);
G_MODULE_EXPORT void bacon_video_widget_set_subtitle_font	 (BaconVideoWidget *bvw,
						  const char *font);
G_MODULE_EXPORT void bacon_video_widget_set_subtitle_encoding	 (BaconVideoWidget *bvw,
						  const char *encoding);

/* Metadata */
typedef enum {
	BVW_INFO_TITLE,
	BVW_INFO_ARTIST,
	BVW_INFO_YEAR,
	BVW_INFO_COMMENT,
	BVW_INFO_ALBUM,
	BVW_INFO_DURATION,
	BVW_INFO_TRACK_NUMBER,
	BVW_INFO_COVER,
	/* Video */
	BVW_INFO_HAS_VIDEO,
	BVW_INFO_DIMENSION_X,
	BVW_INFO_DIMENSION_Y,
	BVW_INFO_VIDEO_BITRATE,
	BVW_INFO_VIDEO_CODEC,
	BVW_INFO_FPS,
	/* Audio */
	BVW_INFO_HAS_AUDIO,
	BVW_INFO_AUDIO_BITRATE,
	BVW_INFO_AUDIO_CODEC,
	BVW_INFO_AUDIO_SAMPLE_RATE,
	BVW_INFO_AUDIO_CHANNELS
} BaconVideoWidgetMetadataType;

G_MODULE_EXPORT void bacon_video_widget_get_metadata		 (BaconVideoWidget *bvw,
						  BaconVideoWidgetMetadataType
						  type,
						  GValue *value);

/* Visualisation functions */
typedef enum {
	VISUAL_SMALL = 0,
	VISUAL_NORMAL,
	VISUAL_LARGE,
	VISUAL_EXTRA_LARGE,
	NUM_VISUAL_QUALITIES
} VisualsQuality;

G_MODULE_EXPORT void bacon_video_widget_set_show_visuals	  (BaconVideoWidget *bvw,
						   gboolean show_visuals);
G_MODULE_EXPORT GList *bacon_video_widget_get_visuals_list	  (BaconVideoWidget *bvw);
G_MODULE_EXPORT gboolean bacon_video_widget_set_visuals		  (BaconVideoWidget *bvw,
						   const char *name);
G_MODULE_EXPORT void bacon_video_widget_set_visuals_quality	  (BaconVideoWidget *bvw,
						   VisualsQuality quality);

/* Picture settings */
typedef enum {
	BVW_VIDEO_BRIGHTNESS,
	BVW_VIDEO_CONTRAST,
	BVW_VIDEO_SATURATION,
	BVW_VIDEO_HUE
} BaconVideoWidgetVideoProperty;

typedef enum {
	BVW_RATIO_AUTO = 0,
	BVW_RATIO_SQUARE = 1,
	BVW_RATIO_FOURBYTHREE = 2,
	BVW_RATIO_ANAMORPHIC = 3,
	BVW_RATIO_DVB = 4
} BaconVideoWidgetAspectRatio;

G_MODULE_EXPORT gboolean bacon_video_widget_can_deinterlace	 (BaconVideoWidget *bvw);
G_MODULE_EXPORT void bacon_video_widget_set_deinterlacing        (BaconVideoWidget *bvw,
						  gboolean deinterlace);
G_MODULE_EXPORT gboolean bacon_video_widget_get_deinterlacing    (BaconVideoWidget *bvw);

G_MODULE_EXPORT void bacon_video_widget_set_aspect_ratio         (BaconVideoWidget *bvw,
						  BaconVideoWidgetAspectRatio
						  ratio);
G_MODULE_EXPORT BaconVideoWidgetAspectRatio bacon_video_widget_get_aspect_ratio
						 (BaconVideoWidget *bvw);

G_MODULE_EXPORT void bacon_video_widget_set_scale_ratio          (BaconVideoWidget *bvw,
						  float ratio);

G_MODULE_EXPORT void bacon_video_widget_set_zoom		 (BaconVideoWidget *bvw,
						  int zoom);
G_MODULE_EXPORT int bacon_video_widget_get_zoom			 (BaconVideoWidget *bvw);

G_MODULE_EXPORT int bacon_video_widget_get_video_property        (BaconVideoWidget *bvw,
						  BaconVideoWidgetVideoProperty
						  type);
G_MODULE_EXPORT void bacon_video_widget_set_video_property       (BaconVideoWidget *bvw,
						  BaconVideoWidgetVideoProperty
						  type,
						  int value);

/* DVD functions */
typedef enum {
	BVW_DVD_ROOT_MENU,
	BVW_DVD_TITLE_MENU,
	BVW_DVD_SUBPICTURE_MENU,
	BVW_DVD_AUDIO_MENU,
	BVW_DVD_ANGLE_MENU,
	BVW_DVD_CHAPTER_MENU,
	BVW_DVD_NEXT_CHAPTER,
	BVW_DVD_PREV_CHAPTER,
	BVW_DVD_NEXT_TITLE,
	BVW_DVD_PREV_TITLE,
	BVW_DVD_NEXT_ANGLE,
	BVW_DVD_PREV_ANGLE,
	BVW_DVD_ROOT_MENU_UP,
	BVW_DVD_ROOT_MENU_DOWN,
	BVW_DVD_ROOT_MENU_LEFT,
	BVW_DVD_ROOT_MENU_RIGHT,
	BVW_DVD_ROOT_MENU_SELECT
} BaconVideoWidgetDVDEvent;

G_MODULE_EXPORT void bacon_video_widget_dvd_event                (BaconVideoWidget *bvw,
						  BaconVideoWidgetDVDEvent
						  type);
G_MODULE_EXPORT GList *bacon_video_widget_get_languages          (BaconVideoWidget *bvw);
G_MODULE_EXPORT int bacon_video_widget_get_language              (BaconVideoWidget *bvw);
G_MODULE_EXPORT void bacon_video_widget_set_language             (BaconVideoWidget *bvw,
		                                  int language);

G_MODULE_EXPORT GList *bacon_video_widget_get_subtitles          (BaconVideoWidget *bvw);
G_MODULE_EXPORT int bacon_video_widget_get_subtitle              (BaconVideoWidget *bvw);
G_MODULE_EXPORT void bacon_video_widget_set_subtitle             (BaconVideoWidget *bvw,
		                                  int subtitle);

G_MODULE_EXPORT gboolean bacon_video_widget_has_next_track	 (BaconVideoWidget *bvw);
G_MODULE_EXPORT gboolean bacon_video_widget_has_previous_track	 (BaconVideoWidget *bvw);

/* Screenshot functions */
G_MODULE_EXPORT gboolean bacon_video_widget_can_get_frames       (BaconVideoWidget *bvw,
						  GError **error);
G_MODULE_EXPORT GdkPixbuf *bacon_video_widget_get_current_frame (BaconVideoWidget *bvw);

/* Audio-out functions */
typedef enum {
	BVW_AUDIO_SOUND_STEREO,
	BVW_AUDIO_SOUND_4CHANNEL,
	BVW_AUDIO_SOUND_41CHANNEL,
	BVW_AUDIO_SOUND_5CHANNEL,
	BVW_AUDIO_SOUND_51CHANNEL,
	BVW_AUDIO_SOUND_AC3PASSTHRU
} BaconVideoWidgetAudioOutType;

G_MODULE_EXPORT BaconVideoWidgetAudioOutType bacon_video_widget_get_audio_out_type
						 (BaconVideoWidget *bvw);
G_MODULE_EXPORT gboolean bacon_video_widget_set_audio_out_type   (BaconVideoWidget *bvw,
						  BaconVideoWidgetAudioOutType
						  type);

G_END_DECLS

#endif				/* HAVE_BACON_VIDEO_WIDGET_H */
