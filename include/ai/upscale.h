#ifndef FYDELIS_UPSCALE_H
#define FYDELIS_UPSCALE_H

#include "../fydelis-editor.h"

G_BEGIN_DECLS

gboolean  fydelis_upscale_init(const gchar *model_path, gint scale_factor);
void      fydelis_upscale_shutdown(void);
gboolean  fydelis_upscale_is_loaded(void);

/* Aumenta resolução de imagem RGBA */
gboolean  fydelis_upscale_process_image(const guint8 *src, gint sw, gint sh,
                                         guint8 **out_dst, gint *out_dw, gint *out_dh);

G_END_DECLS

#endif /* FYDELIS_UPSCALE_H */