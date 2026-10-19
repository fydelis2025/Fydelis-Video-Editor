#ifndef FYDELIS_DENOISE_H
#define FYDELIS_DENOISE_H

#include "../fydelis-editor.h"

G_BEGIN_DECLS

gboolean  fydelis_denoise_init(void);
void      fydelis_denoise_shutdown(void);
gboolean  fydelis_denoise_is_loaded(void);

/* Processa bloco de áudio mono 16-bit 48kHz */
void      fydelis_denoise_process(gint16 *inout, gint n_frames);

/* Versão float */
void      fydelis_denoise_process_f(float *inout, gint n_frames);

G_END_DECLS

#endif /* FYDELIS_DENOISE_H */