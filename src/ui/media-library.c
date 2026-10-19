#include "ui/media-library.h"
#include <gtk/gtk.h>

G_DEFINE_TYPE(FydelisMediaLibrary, fydelis_media_library, GTK_TYPE_BOX)

// ==============================================
// RESPOSTA DO DIÁLOGO — API CORRETA GTK 4
// ==============================================
static void
on_dialog_response(GtkFileChooserNative *dialog, gint response, gpointer user_data)
{
    FydelisMediaLibrary *self = user_data;
    
    if (response == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        GListModel *files = gtk_file_chooser_get_files(chooser);
        
        guint n = g_list_model_get_n_items(files);
        for (guint i = 0; i < n; i++) {
            GFile *f = g_list_model_get_item(files, i);
            g_autofree gchar *path = g_file_get_path(f);
            fydelis_media_library_add_file(self, path);
            g_object_unref(f);
        }
    }
    
    g_object_unref(dialog);
}

static void
on_add_file_clicked(GtkWidget *btn, gpointer user_data)
{
    FydelisMediaLibrary *self = user_data;
    GtkWindow *janela = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(self)));

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

    // ✅ Conecta o sinal ANTES de exibir
    g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), self);
    
    // ✅ Apenas 1 argumento — funciona no seu GTK 4
    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
}

// ==============================================
// INICIALIZAÇÃO
// ==============================================
static void
fydelis_media_library_class_init(FydelisMediaLibraryClass *klass)
{
}

static void
fydelis_media_library_init(FydelisMediaLibrary *self)
{
    gtk_orientable_set_orientation(GTK_ORIENTABLE(self), GTK_ORIENTATION_VERTICAL);
    gtk_box_set_spacing(GTK_BOX(self), 8);
    gtk_widget_set_margin_top(GTK_WIDGET(self), 12);
    gtk_widget_set_margin_bottom(GTK_WIDGET(self), 12);
    gtk_widget_set_margin_start(GTK_WIDGET(self), 12);
    gtk_widget_set_margin_end(GTK_WIDGET(self), 12);
    
    // Título
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>📁 Biblioteca de Mídia</b>");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(self), label);
    
    // Botão Adicionar
    self->btn_add = gtk_button_new_with_label("+ Adicionar Arquivos");
    gtk_widget_set_margin_top(self->btn_add, 8);
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(on_add_file_clicked), self);
    gtk_box_append(GTK_BOX(self), self->btn_add);
    
    // Lista
    self->list_box = gtk_list_box_new();
    gtk_widget_set_vexpand(self->list_box, TRUE);
    gtk_widget_set_margin_top(self->list_box, 12);
    gtk_box_append(GTK_BOX(self), self->list_box);
}

GtkWidget*
fydelis_media_library_new(void)
{
    return g_object_new(FYDELIS_TYPE_MEDIA_LIBRARY, NULL);
}

void
fydelis_media_library_add_file(FydelisMediaLibrary *self, const gchar *filepath)
{
    g_autofree gchar *basename = g_path_get_basename(filepath);
    
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    
    GtkWidget *name_label = gtk_label_new(basename);
    gtk_widget_set_halign(name_label, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(box), name_label);
    
    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), box);
    gtk_list_box_append(GTK_LIST_BOX(self->list_box), row);
    
    g_print("[Biblioteca] Adicionado: %s\n", basename);
}
