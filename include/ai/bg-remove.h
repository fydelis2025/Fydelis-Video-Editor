#ifndef FYDELIS_BG_REMOVE_H
#define FYDELIS_BG_REMOVE_H

#include "../fydelis-editor.h"

G_BEGIN_DECLS

gboolean  fydelis_bgremove_init(const gchar *model_path);
void      fydelis_bgremove_shutdown(void);
gboolean  fydelis_bgremove_is_loaded(void);

/* Gera máscara de transparência (canal alpha) */
gboolean  fydelis_bgremove_process(const guint8 *rgba_src, gint w, gint h,
                                    guint8 *alpha_out);

G_END_DECLS

#endif /* FYDELIS_BG_REMOVE_H */