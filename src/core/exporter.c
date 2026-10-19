#include "core/exporter.h"
#include "core/ffmpeg-utils.h"
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <glib.h>
#include <stdio.h>

struct _FydelisExporter {
    GObject parent_instance;
    FydelisTimeline *timeline;
    GThread *worker;
    gboolean running;
    gboolean cancel_requested;
};

G_DEFINE_TYPE(FydelisExporter, fydelis_exporter, G_TYPE_OBJECT)

static void*
export_worker(gpointer user_data)
{
    FydelisExporter *self = user_data;
    self->running = TRUE;
    g_print("[Fydelis/Exporter] Iniciando exportação...\n");

    /* TODO: Montar grafo de filtros FFmpeg a partir da timeline */
    /* ffmpeg-utils.c vai conter as funções de abertura de arquivo,
       configuração de codecs e escrita de pacotes */

    /* Simulação de progresso — será substituída pela leitura real dos frames */
    for (int i = 0; i <= 100 && !self->cancel_requested; i += 5) {
        g_usleep(100000); /* 0.1s por passo — remover na versão real */
        g_print("[Fydelis/Exporter] Progresso: %d%%\n", i);
    }

    if (self->cancel_requested)
        g_print("[Fydelis/Exporter] Exportação cancelada pelo usuário.\n");
    else
        g_print("[Fydelis/Exporter] ✅ Exportação concluída com sucesso!\n");

    self->running = FALSE;
    return NULL;
}

FydelisExporter*
fydelis_exporter_new(FydelisTimeline *tl)
{
    g_return_val_if_fail(tl != NULL, NULL);

    FydelisExporter *self = g_object_new(FYDELIS_TYPE_EXPORTER, NULL);
    self->timeline = tl;
    g_object_ref(tl);

    return self;
}

FydelisStatus
fydelis_exporter_start(FydelisExporter *self, const FydelisExportConfig *cfg,
                       FydelisExportProgress cb, gpointer cbdata)
{
    g_return_val_if_fail(self != NULL, FYDELIS_ERR_GENERIC);
    g_return_val_if_fail(cfg != NULL, FYDELIS_ERR_GENERIC);

    if (self->running)
        return FYDELIS_ERR_GENERIC;

    self->cancel_requested = FALSE;
    self->worker = g_thread_new("fydelis-export-worker", export_worker, self);

    /* Avisar ao compilador que esses parâmetros serão usados em breve */
    (void)cb;
    (void)cbdata;

    return FYDELIS_OK;
}

void
fydelis_exporter_cancel(FydelisExporter *self)
{
    g_return_if_fail(self != NULL);

    if (!self->running)
        return;

    self->cancel_requested = TRUE;

    if (self->worker) {
        g_thread_join(self->worker);
        g_clear_pointer(&self->worker, g_thread_unref);
    }
}

gboolean
fydelis_exporter_is_running(FydelisExporter *self)
{
    g_return_val_if_fail(self != NULL, FALSE);
    return self->running;
}

static void
fydelis_exporter_finalize(GObject *obj)
{
    FydelisExporter *self = FYDELIS_EXPORTER(obj);

    if (self->running)
        fydelis_exporter_cancel(self);

    g_clear_object(&self->timeline);

    G_OBJECT_CLASS(fydelis_exporter_parent_class)->finalize(obj);
}

static void
fydelis_exporter_class_init(FydelisExporterClass *klass)
{
    GObjectClass *gobj = G_OBJECT_CLASS(klass);
    gobj->finalize = fydelis_exporter_finalize;
}

static void
fydelis_exporter_init(FydelisExporter *self)
{
    self->running = FALSE;
    self->cancel_requested = FALSE;
    self->worker = NULL;
    self->timeline = NULL;
}
