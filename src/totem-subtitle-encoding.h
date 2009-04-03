/* Encoding stuff */

#ifndef TOTEM_SUBTITLE_ENCODING_H
#define TOTEM_SUBTITLE_ENCODING_H

#include <gtk/gtk.h>

G_MODULE_EXPORT void totem_subtitle_encoding_init (GtkComboBox *combo);
G_MODULE_EXPORT void totem_subtitle_encoding_set (GtkComboBox *combo, const char *encoding);
G_MODULE_EXPORT const char * totem_subtitle_encoding_get_selected (GtkComboBox *combo);

#endif /* SUBTITLE_ENCODING_H */
