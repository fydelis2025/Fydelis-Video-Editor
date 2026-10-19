#ifndef FYDELIS_EDITOR_H
#define FYDELIS_EDITOR_H

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>      /* ← Adicionei */
#include <gdk/gdk.h>      /* ← Adicionei */

/* Versão e identidade */
#define FYDELIS_NAME        "Fydelis Video Editor"
#define FYDELIS_VERSION     "1.0.0-ia"
#define FYDELIS_THEME_COLOR "#7C3AED"
#define FYDELIS_DARK_BG     "#0F0A1E"
#define MODELS_DIR "models"

/* Caminho relativo dentro da pasta de cache do usuário */
#define FYDELIS_CACHE_SUBDIR   "fydelis-editor"

/* Tipos básicos usados em todo o projeto */
typedef gint64 fydelis_time_t;   /* Tempo em microssegundos */
typedef guint32 fydelis_id_t;    /* Identificador único */

/* Estrutura de resolução */
typedef struct {
    gint width;
    gint height;
    gint fps_num;
    gint fps_den;
} FydelisResolution;

/* Estrutura de configuração de exportação */
typedef struct {
    FydelisResolution res;
    gint bitrate;          /* Em kbps */
    const gchar *codec_video;
    const gchar *codec_audio;
    gchar *output_path;
    gboolean use_gpu;
} FydelisExportConfig;

/* Códigos de retorno */
typedef enum {
    FYDELIS_OK = 0,
    FYDELIS_ERR_GENERIC = -1,
    FYDELIS_ERR_IO = -2,
    FYDELIS_ERR_FORMAT = -3,
    FYDELIS_ERR_CODEC = -4,
    FYDELIS_ERR_AIAVAIL = -10,  /* Módulo de IA não disponível */
    FYDELIS_ERR_AIMODEL = -11   /* Modelo de IA não carregado */
} FydelisStatus;

/* Inicialização global */
void fydelis_init(void);
void fydelis_cleanup(void);

/* Utilitários */
gchar* fydelis_get_cache_path(const gchar *subpath);
void fydelis_set_status_message(const gchar *msg);

#endif /* FYDELIS_EDITOR_H */
