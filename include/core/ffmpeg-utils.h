#ifndef FYDELIS_FFMPEG_UTILS_H
#define FYDELIS_FFMPEG_UTILS_H

#include <glib.h>
#include <libavutil/rational.h>
#include "../fydelis-editor.h"

G_BEGIN_DECLS

gboolean  fydelis_ffmpeg_check_encoder(const gchar *encoder_name);
void      fydelis_ffmpeg_set_log_handler(void);
gint64    fydelis_ffmpeg_time_to_ts(fydelis_time_t time_us, AVRational tb);
fydelis_time_t fydelis_ffmpeg_ts_to_time(gint64 ts, AVRational tb);

G_END_DECLS

#endif /* FYDELIS_FFMPEG_UTILS_H */
