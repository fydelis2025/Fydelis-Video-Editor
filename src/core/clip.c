#include "core/clip.h"
#include <glib.h>

/* ⚠️  NÃO coloque a struct _FydelisClip aqui — ela já está no .h! */

static fydelis_id_t next_id = 1;

G_DEFINE_TYPE(FydelisClip, fydelis_clip, G_TYPE_OBJECT)

static void
fydelis_clip_finalize(GObject *obj)
{
    FydelisClip *self = FYDELIS_CLIP(obj);

    g_free(self->path);
    g_free(self->title);

    G_OBJECT_CLASS(fydelis_clip_parent_class)->finalize(obj);
}

static void
fydelis_clip_class_init(FydelisClipClass *klass)
{
    GObjectClass *gobj = G_OBJECT_CLASS(klass);
    gobj->finalize = fydelis_clip_finalize;
}

static void
fydelis_clip_init(FydelisClip *self)
{
    self->id = next_id++;
    self->speed = 1.0;
    self->volume = 1.0;
    self->muted = FALSE;
    self->title = NULL;
    self->start = 0;
    self->offset = 0;
    self->duration = 0;
}

FydelisClip*
fydelis_clip_new(const gchar *path, FydelisMediaType type)
{
    g_return_val_if_fail(path != NULL, NULL);

    FydelisClip *self = g_object_new(FYDELIS_TYPE_CLIP, NULL);
    self->path = g_strdup(path);
    self->type = type;

    return self;
}

void
fydelis_clip_set_range(FydelisClip *self, fydelis_time_t start,
                        fydelis_time_t offset, fydelis_time_t duration)
{
    g_return_if_fail(self != NULL);

    self->start = start;
    self->offset = offset;
    self->duration = duration;
}

void
fydelis_clip_set_speed(FydelisClip *self, gdouble fator)
{
    g_return_if_fail(self != NULL);

    self->speed = CLAMP(fator, 0.25, 4.0);
}

void
fydelis_clip_set_volume(FydelisClip *self, gdouble vol)
{
    g_return_if_fail(self != NULL);

    self->volume = CLAMP(vol, 0.0, 2.0);
}

FydelisMediaType
fydelis_clip_get_media_type(FydelisClip *self)
{
    g_return_val_if_fail(self != NULL, FYDELIS_MEDIA_UNKNOWN);
    return self->type;
}
