#ifndef FYDELIS_TIMELINE_H
#define FYDELIS_TIMELINE_H

#include "fydelis-editor.h"
#include "core/clip.h"
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define FYDELIS_TYPE_TIMELINE fydelis_timeline_get_type()
G_DECLARE_FINAL_TYPE(FydelisTimeline, fydelis_timeline, FYDELIS, TIMELINE, GObject)

/* Tipo de faixa */
typedef struct {
    gchar *nome;
    gboolean bloqueada;
    /* clipes serão armazenados aqui */
} FydelisTrack;

struct _FydelisTimeline {
    GObject parent_instance;
    GPtrArray *video_tracks;
    GPtrArray *audio_tracks;
    GPtrArray *subtitle_tracks;
    fydelis_time_t duration;
    gint sample_rate;
};

/* Funções públicas */
FydelisTimeline*   fydelis_timeline_new(void);
FydelisTrack*     fydelis_timeline_add_video_track(FydelisTimeline *self, gint pos);
FydelisClip*      fydelis_timeline_add_clip(FydelisTimeline *self,
                                               FydelisTrack *track,
                                               const gchar *caminho,
                                               fydelis_time_t inicio,
                                               fydelis_time_t deslocamento,
                                               fydelis_time_t duracao);
fydelis_time_t    fydelis_timeline_get_duration(FydelisTimeline *self);

G_END_DECLS
#endif
