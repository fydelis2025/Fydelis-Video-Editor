#include "ui/main-window.h"
#include "fydelis-editor.h"
#include "ui/media-library.h"
#include "ui/timeline-view.h"

G_DEFINE_TYPE(FydelisMainWindow, fydelis_main_window, GTK_TYPE_APPLICATION_WINDOW)

// ==============================================
// DIÁLOGO DE IMPORTAÇÃO — API CORRETA GTK 4
// ==============================================
static void
on_file_dialog_response(GtkFileChooserNative *dialog, gint response, gpointer user_data)
{
    FydelisMainWindow *win = user_data;
    
    if (response == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        GListModel *files = gtk_file_chooser_get_files(chooser);
        
        guint n = g_list_model_get_n_items(files);
        for (guint i = 0; i < n; i++) {
            GFile *f = g_list_model_get_item(files, i);
            g_autofree gchar *path = g_file_get_path(f);
            g_autofree gchar *nome = g_path_get_basename(path);
            g_print("[Importar] ✅ %s\n", nome);
            g_object_unref(f);
        }
        
        fydelis_main_window_update_status(win, "Arquivos importados com sucesso");
    }
    
    g_object_unref(dialog);
}

static void
on_importar_clicked(GtkWidget *btn, gpointer user_data)
{
    FydelisMainWindow *win = user_data;
    GtkWindow *janela = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(btn)));

    GtkFileChooserNative *dialog = gtk_file_chooser_native_new(
        "Importar Mídia",
        janela,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Adicionar",
        "Cancelar"
    );
    
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);
    
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Vídeo e Áudio");
    gtk_file_filter_add_mime_type(filter, "video/*");
    gtk_file_filter_add_mime_type(filter, "audio/*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // ✅ Conecta o sinal "response" ANTES de mostrar
    g_signal_connect(dialog, "response", G_CALLBACK(on_file_dialog_response), win);
    
    // ✅ Apenas 1 argumento — funciona no seu GTK 4
    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
}

// ==============================================
// DEMAIS CALLBACKS
// ==============================================
static void
on_exportar_clicked(GtkWidget *btn, gpointer user_data)
{
    FydelisMainWindow *win = user_data;
    g_print("[Exportar] Clicado ✅\n");
    fydelis_main_window_update_status(win, "Preparando exportação...");
}

static void
on_play_clicked(GtkWidget *btn, gpointer user_data)
{
    FydelisMainWindow *win = user_data;
    g_print("[Reproduzir] Clicado ✅\n");
    fydelis_main_window_update_status(win, "Reproduzindo...");
}

static void
on_toggle_ai_panel(GtkWidget *btn, gpointer user_data)
{
    FydelisMainWindow *win = user_data;
    g_print("[IA] Painel de IA ✅\n");
}

// ==============================================
// CICLO DE VIDA DA JANELA
// ==============================================
static void
fydelis_main_window_dispose(GObject *object)
{
    FydelisMainWindow *win = FYDELIS_MAIN_WINDOW(object);
    g_clear_object(&win->timeline);
    g_clear_pointer(&win->project_path, g_free);
    G_OBJECT_CLASS(fydelis_main_window_parent_class)->dispose(object);
}

static void
fydelis_main_window_class_init(FydelisMainWindowClass *klass)
{
    GObjectClass *obj_class = G_OBJECT_CLASS(klass);
    obj_class->dispose = fydelis_main_window_dispose;
}

static void
fydelis_main_window_init(FydelisMainWindow *win)
{
    win->timeline = g_object_new(FYDELIS_TYPE_TIMELINE, NULL);
    win->project_modified = FALSE;
    win->project_path = NULL;
}

FydelisMainWindow*
fydelis_main_window_new(GtkApplication *app)
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    g_print("[DEBUG] Carregando interface...\n");
    gtk_builder_add_from_resource(builder, "/com/fydelis/Editor/assets/ui/main-window.ui", &error);

    if (error) {
        g_print("[ERRO] %s\n", error->message);
        g_error_free(error);
        g_object_unref(builder);
        return NULL;
    }
    g_print("[DEBUG] Arquivo .ui carregado ✅\n");

    GObject *win_obj = gtk_builder_get_object(builder, "janela_principal");
    if (!win_obj) {
        g_print("[ERRO] Janela 'janela_principal' não encontrada ❌\n");
        g_object_unref(builder);
        return NULL;
    }

    FydelisMainWindow *win = FYDELIS_MAIN_WINDOW(win_obj);

    // Conectar botões
    GObject *btn;
    btn = gtk_builder_get_object(builder, "btn_importar");
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_importar_clicked), win);
    else g_print("[AVISO] btn_importar não encontrado\n");

    btn = gtk_builder_get_object(builder, "btn_exportar");
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_exportar_clicked), win);
    else g_print("[AVISO] btn_exportar não encontrado\n");

    btn = gtk_builder_get_object(builder, "btn_play");
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_play_clicked), win);
    else g_print("[AVISO] btn_play não encontrado\n");

    btn = gtk_builder_get_object(builder, "btn_ai");
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_toggle_ai_panel), win);
    else g_print("[AVISO] btn_ai não encontrado\n");

    win->status_bar = GTK_WIDGET(gtk_builder_get_object(builder, "status_bar"));
    win->project_modified = FALSE;
    win->project_path = NULL;
    win->timeline = g_object_new(FYDELIS_TYPE_TIMELINE, NULL);

    gtk_window_set_application(GTK_WINDOW(win), app);
    g_object_unref(builder);
    
    fydelis_main_window_update_status(win, "Pronto • Fydelis Video Editor v" FYDELIS_VERSION);
    return win;
}

void
fydelis_main_window_update_status(FydelisMainWindow *win, const gchar *mensagem)
{
    if (win->status_bar && GTK_IS_LABEL(win->status_bar))
        gtk_label_set_text(GTK_LABEL(win->status_bar), mensagem);
}
