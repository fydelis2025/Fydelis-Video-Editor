#ifndef FYDELIS_MEDIA_LIBRARY_H
#define FYDELIS_MEDIA_LIBRARY_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FYDELIS_TYPE_MEDIA_LIBRARY fydelis_media_library_get_type()
G_DECLARE_FINAL_TYPE(FydelisMediaLibrary, fydelis_media_library, FYDELIS, MEDIA_LIBRARY, GtkBox)

struct _FydelisMediaLibrary {
    GtkBox parent_instance;
    
    GtkWidget *list_box;
    GtkWidget *btn_add;
};

GtkWidget*  fydelis_media_library_new(void);
void        fydelis_media_library_add_file(FydelisMediaLibrary *self, const gchar *filepath);

G_END_DECLS

#endif
