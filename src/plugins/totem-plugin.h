/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * heavily based on code from Rhythmbox and Gedit
 *
 * Copyright (C) 2002-2005 Paolo Maggi
 * Copyright (C) 2007 Bastien Nocera <hadess@hadess.net>
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301  USA.
 *
 * Monday 7th February 2005: Christian Schaller: Add excemption clause.
 * See license_change file for details.
 *
 */

#ifndef __TOTEM_PLUGIN_H__
#define __TOTEM_PLUGIN_H__

#include <glib-object.h>
#include <gtk/gtk.h>

#include "totem.h"

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define TOTEM_TYPE_PLUGIN              (totem_plugin_get_type())
#define TOTEM_PLUGIN(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), TOTEM_TYPE_PLUGIN, TotemPlugin))
#define TOTEM_PLUGIN_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), TOTEM_TYPE_PLUGIN, TotemPlugin const))
#define TOTEM_PLUGIN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), TOTEM_TYPE_PLUGIN, TotemPluginClass))
#define TOTEM_IS_PLUGIN(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), TOTEM_TYPE_PLUGIN))
#define TOTEM_IS_PLUGIN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), TOTEM_TYPE_PLUGIN))
#define TOTEM_PLUGIN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), TOTEM_TYPE_PLUGIN, TotemPluginClass))

/*
 * Main object structure
 */
typedef struct
{
	GObject parent;
} TotemPlugin;

typedef void		(*TotemPluginActivationFunc)		(TotemPlugin *plugin, TotemObject *totem);
typedef GtkWidget *	(*TotemPluginWidgetFunc)		(TotemPlugin *plugin);
typedef gboolean	(*TotemPluginBooleanFunc)		(TotemPlugin *plugin);

/*
 * Class definition
 */
typedef struct
{
	GObjectClass parent_class;

	/* Virtual public methods */

	TotemPluginActivationFunc	activate;
	TotemPluginActivationFunc	deactivate;
	TotemPluginWidgetFunc		create_configure_dialog;

	/* Plugins should not override this, it's handled automatically by
	   the TotemPluginClass */
	TotemPluginBooleanFunc		is_configurable;
} TotemPluginClass;

/*
 * Public methods
 */
GType 		 totem_plugin_get_type 		(void) G_GNUC_CONST;

void 		 totem_plugin_activate		(TotemPlugin *plugin,
						 TotemObject *shell);
void 		 totem_plugin_deactivate	(TotemPlugin *plugin,
						 TotemObject *totem);

gboolean	 totem_plugin_is_configurable	(TotemPlugin *plugin);
GtkWidget	*totem_plugin_create_configure_dialog
						(TotemPlugin *plugin);

char *		 totem_plugin_find_file		(TotemPlugin *plugin,
						 const char *file);

GList *          totem_get_plugin_paths            (void);

/*
 * Utility macro used to register plugins
 *
 * use: TOTEM_PLUGIN_REGISTER(TOTEMSamplePlugin, totem_sample_plugin)
 */

#define TOTEM_PLUGIN_REGISTER(PluginName, plugin_name)				\
										\
static GType plugin_name##_type = 0;						\
static GTypeModule *plugin_module_type = 0;		                \
										\
GType										\
plugin_name##_get_type (void)							\
{										\
	return plugin_name##_type;						\
}										\
										\
static void     plugin_name##_init              (PluginName        *self);	\
static void     plugin_name##_class_init        (PluginName##Class *klass);	\
static gpointer plugin_name##_parent_class = NULL;				\
static void     plugin_name##_class_intern_init (gpointer klass)		\
{										\
	plugin_name##_parent_class = g_type_class_peek_parent (klass);		\
	plugin_name##_class_init ((PluginName##Class *) klass);			\
}										\
										\
G_MODULE_EXPORT GType								\
register_totem_plugin (GTypeModule *module)					\
{										\
	static const GTypeInfo our_info =					\
	{									\
		sizeof (PluginName##Class),					\
		NULL, /* base_init */						\
		NULL, /* base_finalize */					\
		(GClassInitFunc) plugin_name##_class_intern_init,		\
		NULL,								\
		NULL, /* class_data */						\
		sizeof (PluginName),						\
		0, /* n_preallocs */						\
		(GInstanceInitFunc) plugin_name##_init				\
	};									\
										\
	/* Initialise the i18n stuff */						\
	bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);			\
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");			\
										\
	plugin_module_type = module;						\
	plugin_name##_type = g_type_module_register_type (module,		\
					    TOTEM_TYPE_PLUGIN,			\
					    #PluginName,			\
					    &our_info,				\
					    0);					\
	return plugin_name##_type;						\
}

#define TOTEM_PLUGIN_REGISTER_TYPE(type_name)					\
	type_name##_register_type (plugin_module_type)

#define TOTEM_PLUGIN_DEFINE_TYPE(TypeName, type_name, TYPE_PARENT)		\
static void type_name##_init (TypeName *self); 					\
static void type_name##_class_init (TypeName##Class *klass); 			\
static gpointer type_name##_parent_class = ((void *)0); 			\
static GType type_name##_type_id = 0;						\
										\
static void 									\
type_name##_class_intern_init (gpointer klass) 					\
{ 										\
	type_name##_parent_class = g_type_class_peek_parent (klass);		\
	type_name##_class_init ((TypeName##Class*) klass); 			\
}										\
										\
										\
GType 										\
type_name##_get_type (void)							\
{										\
	g_assert (type_name##_type_id != 0);					\
										\
	return type_name##_type_id;						\
}										\
										\
GType 										\
type_name##_register_type (GTypeModule *module) 				\
{ 										\
										\
	if ((type_name##_type_id == 0)) { 					\
		static const GTypeInfo g_define_type_info = { 			\
			sizeof (TypeName##Class), 				\
			(GBaseInitFunc) ((void *)0), 				\
			(GBaseFinalizeFunc) ((void *)0), 			\
			(GClassInitFunc) type_name##_class_intern_init, 	\
			(GClassFinalizeFunc) ((void *)0), 			\
			((void *)0), 						\
			sizeof (TypeName), 					\
			0, 							\
			(GInstanceInitFunc) type_name##_init,			\
			((void *)0) 						\
		}; 								\
		type_name##_type_id = 						\
			g_type_module_register_type (module, 			\
						     TYPE_PARENT, 		\
						     #TypeName,			\
						     &g_define_type_info, 	\
						     (GTypeFlags) 0); 		\
	} 									\
										\
	return type_name##_type_id;						\
}

G_END_DECLS

#endif  /* __TOTEM_PLUGIN_H__ */