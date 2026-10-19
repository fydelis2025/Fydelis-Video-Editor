#ifndef FYDELIS_WHISPER_BRIDGE_H
#define FYDELIS_WHISPER_BRIDGE_H

#include <glib.h>

G_BEGIN_DECLS

gboolean  fydelis_whisper_is_supported(void);
gboolean  fydelis_whisper_is_loaded(void);
gboolean  fydelis_whisper_init(const gchar *model_path);
void      fydelis_whisper_shutdown(void);
gchar*    fydelis_whisper_transcribe_srt(const float *pcm, gint n_samples, gint rate);
GArray*   fydelis_whisper_detect_silences(const float *pcm, gint n, gint rate, gint thresh_db);

G_END_DECLS

#endif
