#ifndef FYDELIS_MAIN_WINDOW_H
#define FYDELIS_MAIN_WINDOW_H

#include "fydelis-editor.h"
#include "core/timeline.h"
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FYDELIS_TYPE_MAIN_WINDOW fydelis_main_window_get_type()
G_DECLARE_FINAL_TYPE(FydelisMainWindow, fydelis_main_window, FYDELIS, MAIN_WINDOW, GtkApplicationWindow)

struct _FydelisMainWindow {
    GtkApplicationWindow parent_instance;
    
    /* Widgets */
    GtkWidget *header_bar;
    GtkWidget *paned_main;
    GtkWidget *media_library;
    GtkWidget *preview_area;
    GtkWidget *timeline_view;
    GtkWidget *ai_panel;
    GtkWidget *status_bar;
    
    /* Estado */
    FydelisTimeline *timeline;
    gboolean project_modified;
    gchar *project_path;
};

FydelisMainWindow*  fydelis_main_window_new(GtkApplication *app);
void                fydelis_main_window_update_status(FydelisMainWindow *win, const gchar *mensagem);

G_END_DECLS

#endif
