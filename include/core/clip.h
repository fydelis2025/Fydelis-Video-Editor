#ifndef FYDELIS_CLIP_H
#define FYDELIS_CLIP_H

#include "fydelis-editor.h"
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/* Tipo de mídia */
typedef enum {
    FYDELIS_MEDIA_UNKNOWN = 0,
    FYDELIS_MEDIA_VIDEO,
    FYDELIS_MEDIA_AUDIO,
    FYDELIS_MEDIA_IMAGE
} FydelisMediaType;

#define FYDELIS_TYPE_CLIP fydelis_clip_get_type()
G_DECLARE_FINAL_TYPE(FydelisClip, fydelis_clip, FYDELIS, CLIP, GObject)

/* A struct SÓ existe aqui — fonte única */
struct _FydelisClip {
    GObject parent_instance;

    gchar          *path;
    FydelisMediaType type;
    fydelis_id_t    id;

    fydelis_time_t  start;     /* Posição na linha do tempo */
    fydelis_time_t  offset;    /* Início dentro do arquivo de mídia */
    fydelis_time_t  duration;  /* Duração na linha do tempo */

    gdouble         speed;
    gdouble         volume;
    gboolean        muted;
    gchar          *title;
};

/* Funções públicas */
FydelisClip*        fydelis_clip_new(const gchar *path, FydelisMediaType type);
void                fydelis_clip_set_range(FydelisClip *self, fydelis_time_t start,
                                             fydelis_time_t offset, fydelis_time_t duration);
void                fydelis_clip_set_speed(FydelisClip *self, gdouble fator);
void                fydelis_clip_set_volume(FydelisClip *self, gdouble vol);
FydelisMediaType    fydelis_clip_get_media_type(FydelisClip *self);

G_END_DECLS
#endif
