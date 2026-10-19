#include <core/ffmpeg-utils.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/mathematics.h>
#include <libavutil/log.h>
#include <stdio.h>

gboolean
fydelis_ffmpeg_check_encoder(const gchar *encoder_name)
{
    const AVCodec *codec = avcodec_find_encoder_by_name(encoder_name);
    if (!codec) {
        g_printerr("[Fydelis/FFmpeg] Encoder não encontrado: %s\n", encoder_name);
        return FALSE;
    }
    g_print("[Fydelis/FFmpeg] Encoder disponível: %s\n", encoder_name);
    return TRUE;
}

void
fydelis_ffmpeg_set_log_handler(void)
{
    av_log_set_level(AV_LOG_WARNING);
    g_print("[Fydelis/FFmpeg] Log nível: AV_LOG_WARNING\n");
}

gint64
fydelis_ffmpeg_time_to_ts(fydelis_time_t time_us, AVRational tb)
{
    return av_rescale_q(time_us, (AVRational){1, 1000000}, tb);
}

fydelis_time_t
fydelis_ffmpeg_ts_to_time(gint64 ts, AVRational tb)
{
    return av_rescale_q(ts, tb, (AVRational){1000000, 1});
}
