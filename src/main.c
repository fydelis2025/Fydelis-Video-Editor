#include <gtk/gtk.h>
#include "fydelis-editor.h"
#include "ui/main-window.h"
#include <dirent.h>

extern GResource *fydelis_res_get_resource(void);

static void
apply_fydelis_theme(void)
{
    GtkCssProvider *css = gtk_css_provider_new();
    
    // ✅ Caminho correto com assets/
    gtk_css_provider_load_from_resource(css, "/com/fydelis/Editor/assets/css/style.css");
    g_print("[DEBUG] Tema Fydelis carregado ✅\n");
    
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    g_object_unref(css);
}

static void
register_icons(void)
{
    GtkIconTheme *theme = gtk_icon_theme_get_for_display(gdk_display_get_default());
    
    // ✅ Caminho EXATO — sem "assets/icons" no prefixo!
    gtk_icon_theme_add_resource_path(theme, "/com/fydelis/Editor/assets/icons");
    
    // 🧪 Teste: veja se o ícone é encontrado
    gboolean tem_icone = gtk_icon_theme_has_icon(theme, "document-new");
    g_print("[DEBUG] Ícone document-new: %s\n", tem_icone ? "✅ Encontrado" : "❌ NÃO encontrado");
}

// ✅ Verificação da pasta de modelos
void
verificar_pasta_models(void)
{
    DIR *dir = opendir(MODELS_DIR);
    if (dir) {
        g_print("[Fydelis] ✅ Pasta de modelos encontrada: %s\n", MODELS_DIR);
        closedir(dir);
    } else {
        g_print("[Fydelis] ⚠️ Pasta de modelos NÃO encontrada!\n");
        g_print("         Crie a pasta: %s\n", MODELS_DIR);
        g_print("         E baixe os modelos conforme o guia.\n");
    }
}

static void
on_activate(GtkApplication *app, gpointer user_data)
{
    (void)user_data;
    
    // 1. Verificar modelos ANTES de tudo
    verificar_pasta_models();
    
    // 2. Registrar recursos embutidos
    g_resources_register(fydelis_res_get_resource());
    g_print("[DEBUG] Recursos registrados ✅\n");
    
    // 3. Registrar pasta de ícones
    register_icons();
    
    // 4. Aplicar tema
    apply_fydelis_theme();
    
    // 5. Abrir janela
    FydelisMainWindow *win = fydelis_main_window_new(app);
    gtk_window_present(GTK_WINDOW(win));
}

int
main(int argc, char **argv)
{
    g_print("[Fydelis] Iniciando %s v%s...\n", FYDELIS_NAME, FYDELIS_VERSION);
    
    GtkApplication *app = gtk_application_new("com.fydelis.Editor", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
