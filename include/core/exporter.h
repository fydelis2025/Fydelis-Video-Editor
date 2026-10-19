#ifndef FYDELIS_EXPORTER_H
#define FYDELIS_EXPORTER_H

#include "../fydelis-editor.h"  /* Já traz FydelisStatus e FydelisExportConfig */
#include "core/timeline.h"

G_BEGIN_DECLS

#define FYDELIS_TYPE_EXPORTER fydelis_exporter_get_type()
G_DECLARE_FINAL_TYPE(FydelisExporter, fydelis_exporter, FYDELIS, EXPORTER, GObject)

/* Callback de progresso */
typedef void (*FydelisExportProgress)(gdouble percent, gpointer user_data);

/* Funções públicas */
FydelisExporter*   fydelis_exporter_new(FydelisTimeline *timeline);
FydelisStatus      fydelis_exporter_start(FydelisExporter *self,
                                           const FydelisExportConfig *cfg,
                                           FydelisExportProgress cb,
                                           gpointer cbdata);
void               fydelis_exporter_cancel(FydelisExporter *self);
gboolean           fydelis_exporter_is_running(FydelisExporter *self);

G_END_DECLS
#endif
