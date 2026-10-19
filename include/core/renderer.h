#ifndef FYDELIS_RENDERER_H
#define FYDELIS_RENDERER_H

#include "../fydelis-editor.h"
#include "timeline.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

#define FYDELIS_TYPE_RENDERER fydelis_renderer_get_type()
G_DECLARE_FINAL_TYPE(FydelisRenderer, fydelis_renderer, FYDELIS, RENDERER, GObject)

struct _FydelisRenderer {
    GObject parent_instance;
    FydelisTimeline *timeline;
    gboolean playing;
    fydelis_time_t current_time;
};

FydelisRenderer*  fydelis_renderer_new(FydelisTimeline*);
void              fydelis_renderer_free(FydelisRenderer*);

/* Pré-visualização */
GdkTexture*       fydelis_renderer_get_frame(FydelisRenderer*, fydelis_time_t);
void              fydelis_renderer_set_resolution(FydelisRenderer*, gint w, gint h);

/* Controle de reprodução */
void              fydelis_renderer_play(FydelisRenderer*);
void              fydelis_renderer_pause(FydelisRenderer*);
gboolean          fydelis_renderer_is_playing(FydelisRenderer*);

G_END_DECLS
#endif /* FYDELIS_RENDERER_H */
