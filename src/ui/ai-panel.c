#include "ui/ai-panel.h"
#include "ai/whisper-bridge.h"
#include <gtk/gtk.h>

/* ⚠️  APAGUE a struct _FydelisAiPanel daqui — JÁ ESTÁ no .h! */

G_DEFINE_TYPE(FydelisAiPanel, fydelis_ai_panel, GTK_TYPE_BOX)

/* === Funções auxiliares (sem lambda, C puro) === */

static gboolean
whisper_init_done(gpointer user_data)
{
    FydelisAiPanel *self = user_data;
    if (fydelis_whisper_is_loaded()) {
        gtk_label_set_text(self->status, "✅ Whisper pronto!");
    } else {
        gtk_label_set_text(self->status, "❌ Falha ao carregar modelo");
    }
    return G_SOURCE_REMOVE;
}

static gboolean
whisper_ready_msg(gpointer user_data)
{
    FydelisAiPanel *self = user_data;
    gtk_label_set_text(self->status, "✅ Pronto para transcrever! Selecione um clipe.");
    return G_SOURCE_REMOVE;
}

static gpointer
whisper_thread_func(gpointer user_data)
{
    FydelisAiPanel *self = user_data;

    if (!fydelis_whisper_is_loaded()) {
        gboolean ok = fydelis_whisper_init("./models/ggml-small.bin");
        (void)ok;
        g_idle_add(whisper_init_done, self);
    } else {
        g_idle_add(whisper_ready_msg, self);
    }

    return NULL;
}

/* === Callback do botão === */
static void
on_transcribe_clicked(GtkWidget *btn, gpointer user_data)
{
    FydelisAiPanel *self = user_data;
    (void)btn;

    gtk_label_set_text(self->status, "🔄 Processando transcrição...");

    /* ✅ g_thread_new: nome, função, dados — tudo em C puro */
    g_thread_new("ai-whisper", whisper_thread_func, self);
}

/* === Ciclo de vida do widget === */
static void
fydelis_ai_panel_class_init(FydelisAiPanelClass *klass)
{
    GtkWidgetClass *wc = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(wc, "/com/fydelis/Editor/ui/ai-panel.ui");
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, btn_transcribe);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, btn_denoise);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, btn_track);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, btn_upscale);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, bg_remove);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, btn_tts);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, status);
    gtk_widget_class_bind_template_child(wc, FydelisAiPanel, progress);
}

static void
fydelis_ai_panel_init(FydelisAiPanel *self)
{
    gtk_widget_init_template(GTK_WIDGET(self));

    g_signal_connect(self->btn_transcribe, "clicked",
                     G_CALLBACK(on_transcribe_clicked), self);
    /* Conectar os outros botões aqui depois */
}

/* === Funções públicas === */
GtkWidget*
fydelis_ai_panel_new(void)
{
    return g_object_new(FYDELIS_TYPE_AI_PANEL, NULL);
}

void
fydelis_ai_panel_set_status(FydelisAiPanel *self, const gchar *texto)
{
    g_return_if_fail(self != NULL);
    g_return_if_fail(texto != NULL);
    gtk_label_set_text(self->status, texto);
}

void
fydelis_ai_panel_set_progress(FydelisAiPanel *self, gdouble fracao)
{
    g_return_if_fail(self != NULL);
    gtk_progress_bar_set_fraction(self->progress, fracao);
}

void
fydelis_ai_panel_reset(FydelisAiPanel *self)
{
    g_return_if_fail(self != NULL);
    gtk_label_set_text(self->status, "Pronto");
    gtk_progress_bar_set_fraction(self->progress, 0.0);
}
