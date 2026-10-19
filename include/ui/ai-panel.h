#ifndef FYDELIS_AI_PANEL_H
#define FYDELIS_AI_PANEL_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FYDELIS_TYPE_AI_PANEL fydelis_ai_panel_get_type()
G_DECLARE_FINAL_TYPE(FydelisAiPanel, fydelis_ai_panel, FYDELIS, AI_PANEL, GtkBox)

struct _FydelisAiPanel {
    GtkBox parent_instance;

    GtkButton *btn_transcribe;
    GtkButton *btn_denoise;
    GtkButton *btn_track;
    GtkButton *btn_upscale;
    GtkButton *bg_remove;
    GtkButton *btn_tts;

    GtkLabel  *status;
    GtkProgressBar *progress;
};

GtkWidget*  fydelis_ai_panel_new(void);
void        fydelis_ai_panel_set_status(FydelisAiPanel*, const gchar *texto);
void        fydelis_ai_panel_set_progress(FydelisAiPanel*, gdouble fracao);
void        fydelis_ai_panel_reset(FydelisAiPanel*);

G_END_DECLS

#endif /* FYDELIS_AI_PANEL_H */