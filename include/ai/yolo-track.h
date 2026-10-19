#ifndef FYDELIS_YOLO_TRACK_H
#define FYDELIS_YOLO_TRACK_H

#include "../fydelis-editor.h"

G_BEGIN_DECLS

typedef struct {
    gfloat x, y;          /* Centro normalizado */
    gfloat w, h;          /* Dimensões normalizadas */
    gfloat confidence;
    gint class_id;
    gchar class_name[64];
} FydelisDetection;

gboolean  fydelis_yolo_init(const gchar *model_path);
void      fydelis_yolo_shutdown(void);
gboolean  fydelis_yolo_is_loaded(void);

/* Detecta objetos em quadro RGBA */
GArray*   fydelis_yolo_detect_frame(const guint8 *rgba_data, gint w, gint h);

/* Rastreia objeto de referência ao longo de sequência */
gboolean  fydelis_yolo_track_object(const gchar *video_path,
                                      const FydelisDetection *ref,
                                      GArray **out_positions);

G_END_DECLS

#endif /* FYDELIS_YOLO_TRACK_H */