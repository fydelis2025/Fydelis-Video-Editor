#ifndef FYDELIS_TTS_H
#define FYDELIS_TTS_H

#include "../fydelis-editor.h"

G_BEGIN_DECLS

gboolean  fydelis_tts_init(const gchar *model_path, const gchar *voice_path);
void      fydelis_tts_shutdown(void);
gboolean  fydelis_tts_is_loaded(void);

/* Texto → áudio WAV em memória */
GBytes*   fydelis_tts_speak(const gchar *texto, gfloat velocidade);

G_END_DECLS

#endif /* FYDELIS_TTS_H */