#include "core/timeline.h"
#include "core/clip.h"
#include <glib.h>

/* ✅ NÃO repita a struct aqui — ela já está no .h!
   Mantemos apenas G_DEFINE_TYPE e as implementações */

G_DEFINE_TYPE(FydelisTimeline, fydelis_timeline, G_TYPE_OBJECT)

static void
fydelis_timeline_finalize(GObject *obj)
{
    FydelisTimeline *self = FYDELIS_TIMELINE(obj);

    g_ptr_array_unref(self->video_tracks);
    g_ptr_array_unref(self->audio_tracks);
    g_ptr_array_unref(self->subtitle_tracks);

    G_OBJECT_CLASS(fydelis_timeline_parent_class)->finalize(obj);
}

static void
fydelis_timeline_class_init(FydelisTimelineClass *klass)
{
    GObjectClass *gobj = G_OBJECT_CLASS(klass);
    gobj->finalize = fydelis_timeline_finalize;
}

static void
fydelis_timeline_init(FydelisTimeline *self)
{
    self->video_tracks = g_ptr_array_new_with_free_func(g_object_unref);
    self->audio_tracks = g_ptr_array_new_with_free_func(g_object_unref);
    self->subtitle_tracks = g_ptr_array_new_with_free_func(g_object_unref);
    self->duration = 0;
    self->sample_rate = 48000;
}

FydelisTimeline*
fydelis_timeline_new(void)
{
    return g_object_new(FYDELIS_TYPE_TIMELINE, NULL);
}

FydelisTrack*
fydelis_timeline_add_video_track(FydelisTimeline *self, gint pos)
{
    g_return_val_if_fail(self != NULL, NULL);

    /* Criação real da faixa — você precisa do tipo FydelisTrack */
    FydelisTrack *track = g_new0(FydelisTrack, 1);

    if (pos < 0 || pos >= (gint)self->video_tracks->len)
        g_ptr_array_add(self->video_tracks, track);
    else
        g_ptr_array_insert(self->video_tracks, pos, track);

    return track;
}

FydelisClip*
fydelis_timeline_add_clip(FydelisTimeline *self, FydelisTrack *track,
                          const gchar *path, fydelis_time_t start,
                          fydelis_time_t offset, fydelis_time_t duration)
{
    g_return_val_if_fail(self != NULL, NULL);
    g_return_val_if_fail(path != NULL, NULL);

    (void)track; /* Será usado para inserir na faixa específica */

    FydelisClip *clip = fydelis_clip_new(path, FYDELIS_MEDIA_VIDEO);
    if (!clip) return NULL;

    fydelis_clip_set_range(clip, start, offset, duration);

    if (start + duration > self->duration)
        self->duration = start + duration;

    return clip;
}

fydelis_time_t
fydelis_timeline_get_duration(FydelisTimeline *self)
{
    g_return_val_if_fail(self != NULL, 0);
    return self->duration;
}
