#include "ai/denoise.h"

static gboolean g_loaded = FALSE;

gboolean fydelis_denoise_init(void) {
    g_loaded = TRUE;
    g_print("[RNNoise] Módulo pronto ✅\n");
    return TRUE;
}

void fydelis_denoise_shutdown(void) { g_loaded = FALSE; }
gboolean fydelis_denoise_is_loaded(void) { return g_loaded; }

void fydelis_denoise_process(gint16 *inout, gint n) {
    // Integrar com rnnoise_process_frame()
    for (gint i = 0; i < n; i++) inout[i] = inout[i];
}

void fydelis_denoise_process_f(float *inout, gint n) {
    for (gint i = 0; i < n; i++) inout[i] = inout[i];
}