#include "ai/whisper-bridge.h"
#include <whisper.h>
#include <glib.h>
#include <string.h>
#include <math.h>

static struct whisper_context *g_ctx = NULL;

gboolean
fydelis_whisper_is_supported(void)
{
    return TRUE;
}

gboolean
fydelis_whisper_is_loaded(void)
{
    return g_ctx != NULL;
}

gboolean
fydelis_whisper_init(const gchar *model_path)
{
    if (g_ctx) return TRUE;

    struct whisper_context_params params = whisper_context_default_params();
    g_ctx = whisper_init_from_file_with_params(model_path, params);

    if (!g_ctx) {
        g_printerr("[Fydelis/Whisper] Falha ao carregar: %s\n", model_path);
        return FALSE;
    }
    g_print("[Fydelis/Whisper] Modelo carregado com sucesso ✅\n");
    return TRUE;
}

void
fydelis_whisper_shutdown(void)
{
    if (g_ctx) {
        whisper_free(g_ctx);
        g_ctx = NULL;
    }
}

gchar*
fydelis_whisper_transcribe_srt(const float *pcm, gint n_samples, gint rate)
{
    (void)rate;
    if (!g_ctx) return NULL;

    struct whisper_full_params p = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    p.language = "pt";
    p.print_progress = false;

    if (whisper_full(g_ctx, p, pcm, n_samples) != 0)
        return NULL;

    GString *srt = g_string_new("");
    int n = whisper_full_n_segments(g_ctx);
    for (int i = 0; i < n; i++) {
        const char *txt = whisper_full_get_segment_text(g_ctx, i);
        int64_t t0 = whisper_full_get_segment_t0(g_ctx, i) * 10;
        int64_t t1 = whisper_full_get_segment_t1(g_ctx, i) * 10;

        g_string_append_printf(srt,
            "%d\n%02ld:%02ld:%02ld,%03ld --> %02ld:%02ld:%02ld,%03ld\n%s\n\n",
            i + 1,
            (long)t0 / 3600000, ((long)t0 / 60000) % 60, ((long)t0 / 1000) % 60, (long)t0 % 1000,
            (long)t1 / 3600000, ((long)t1 / 60000) % 60, ((long)t1 / 1000) % 60, (long)t1 % 1000,
            txt);
    }
    return g_string_free(srt, FALSE);
}

GArray*
fydelis_whisper_detect_silences(const float *pcm, gint n, gint rate, gint thresh_db)
{
    GArray *arr = g_array_new(FALSE, FALSE, sizeof(gint64[2]));
    float threshold = powf(10.0f, thresh_db / 20.0f) * 0.5f;
    gboolean in_silence = FALSE;
    gint64 start = 0;
    for (gint i = 0; i < n; ) {
        float rms = 0.0f;
        for (gint j = 0; j < 1024 && i + j < n; j++)
            rms += pcm[i + j] * pcm[i + j];
        rms = sqrtf(rms / 1024.0f);
        gint64 t = (gint64)i * 1000000 / rate;
        if (rms < threshold && !in_silence) {
            in_silence = TRUE;
            start = t;
        } else if (rms >= threshold && in_silence) {
            in_silence = FALSE;
            gint64 range[2] = {start, t};
            g_array_append_val(arr, range);
        }
        i += 1024;
    }
    return arr;
}
