#include "core/renderer.h"
#include "core/timeline.h"

G_DEFINE_TYPE(FydelisRenderer, fydelis_renderer, G_TYPE_OBJECT)

FydelisRenderer*
fydelis_renderer_new(FydelisTimeline *tl)
{
    FydelisRenderer *self = g_object_new(FYDELIS_TYPE_RENDERER, NULL);
    self->timeline = tl;
    if (tl) g_object_ref(tl);
    return self;
}

void
fydelis_renderer_free(FydelisRenderer *self)
{
    g_object_unref(self);
}

GdkTexture*
fydelis_renderer_get_frame(FydelisRenderer *self, fydelis_time_t time)
{
    (void)self; (void)time;
    return NULL;
}

void
fydelis_renderer_set_resolution(FydelisRenderer *self, gint w, gint h)
{
    if (!self) return;
    (void)w; (void)h;
}

void
fydelis_renderer_play(FydelisRenderer *self)
{
    if (!self) return;
    self->playing = TRUE;
}

void
fydelis_renderer_pause(FydelisRenderer *self)
{
    if (!self) return;
    self->playing = FALSE;
}

gboolean
fydelis_renderer_is_playing(FydelisRenderer *self)
{
    return self ? self->playing : FALSE;
}

static void
fydelis_renderer_class_init(FydelisRendererClass *klass)
{
    (void)klass;
}

static void
fydelis_renderer_init(FydelisRenderer *self)
{
    (void)self;
}
