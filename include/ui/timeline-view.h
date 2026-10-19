#ifndef FYDELIS_TIMELINE_VIEW_H
#define FYDELIS_TIMELINE_VIEW_H

#include "fydelis-editor.h"
#include "core/timeline.h"
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FYDELIS_TYPE_TIMELINE_VIEW fydelis_timeline_view_get_type()
G_DECLARE_FINAL_TYPE(FydelisTimelineView, fydelis_timeline_view, FYDELIS, TIMELINE_VIEW, GtkWidget)

/* Struct — fonte única */
struct _FydelisTimelineView {
    GtkWidget parent_instance;
    FydelisTimeline *timeline;
    fydelis_time_t scroll_offset;
    fydelis_time_t cursor_pos;
    gdouble pixels_per_second;
    gboolean dragging;
    gpointer dragged_clip;
};

FydelisTimelineView*  fydelis_timeline_view_get_instance(void);
GtkWidget*            fydelis_timeline_view_new(FydelisTimeline *tl);
void                  fydelis_timeline_view_set_timeline(FydelisTimelineView *self, FydelisTimeline *tl);

G_END_DECLS
#endif
