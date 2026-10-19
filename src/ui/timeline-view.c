#include "ui/timeline-view.h"
#include "core/clip.h"
#include <gtk/gtk.h>
#include <graphene.h>  // ✅ Tipo correto: graphene_point_t
#include <math.h>

/* ⚠️  APAGUE a struct _FydelisTimelineView daqui — JÁ ESTÁ no .h! */

G_DEFINE_TYPE(FydelisTimelineView, fydelis_timeline_view, GTK_TYPE_WIDGET)

static void
draw_time_ruler(FydelisTimelineView *self, GtkSnapshot *snap, int width)
{
    gchar buf[32];
    for (fydelis_time_t t = self->scroll_offset;
         t < self->scroll_offset + (fydelis_time_t)width * 1000000 / self->pixels_per_second;
         t += 500000000) {

        gdouble x = (t - self->scroll_offset) * self->pixels_per_second / 1000000.0;

        snprintf(buf, sizeof buf, "%.1fs", t / 1000000.0);
        PangoLayout *lay = gtk_widget_create_pango_layout(GTK_WIDGET(self), buf);

        /* ✅ Tipo correto em C — não existe GraphenePoint, é graphene_point_t */
        graphene_point_t ponto;
        ponto.x = x + 4;
        ponto.y = 6;

        gtk_snapshot_save(snap);
        gtk_snapshot_translate(snap, &ponto);
        gtk_snapshot_append_layout(snap, lay, &(GdkRGBA){1, 1, 1, 0.7});
        gtk_snapshot_restore(snap);

        /* ✅ GRAPHENE_RECT_INIT funciona normalmente */
        gtk_snapshot_append_color(snap, &(GdkRGBA){0.486, 0.227, 0.929, 0.5},
            &GRAPHENE_RECT_INIT(x, 30, 1, 1000));

        g_object_unref(lay);  // ✅ Libera memória do layout
    }
}

static void
fydelis_timeline_view_snapshot(GtkWidget *w, GtkSnapshot *snap)
{
    FydelisTimelineView *self = FYDELIS_TIMELINE_VIEW(w);
    int width = gtk_widget_get_width(w);
    int height = gtk_widget_get_height(w);

    /* Fundo principal */
    gtk_snapshot_append_color(snap, &(GdkRGBA){0.059, 0.043, 0.173, 1.0},
                               &GRAPHENE_RECT_INIT(0, 0, width, height));

    /* Régua de tempo */
    gtk_snapshot_append_color(snap, &(GdkRGBA){0.102, 0.067, 0.200, 1.0},
                               &GRAPHENE_RECT_INIT(0, 0, width, 30));

    draw_time_ruler(self, snap, width);

    /* Linha do cursor */
    gdouble cx = (self->cursor_pos - self->scroll_offset) * self->pixels_per_second / 1000000.0;
    gtk_snapshot_append_color(snap, &(GdkRGBA){1.0, 0.8, 0.2, 1.0},
        &GRAPHENE_RECT_INIT(cx, 0, 2, height));
}

static void
fydelis_timeline_view_class_init(FydelisTimelineViewClass *klass)
{
    GtkWidgetClass *wc = GTK_WIDGET_CLASS(klass);
    wc->snapshot = fydelis_timeline_view_snapshot;
}

static void
fydelis_timeline_view_init(FydelisTimelineView *self)
{
    self->pixels_per_second = 100.0;
    self->scroll_offset = 0;
    self->cursor_pos = 0;
    self->timeline = NULL;
    self->dragging = FALSE;
    self->dragged_clip = NULL;

    gtk_widget_set_hexpand(GTK_WIDGET(self), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(self), TRUE);
}

GtkWidget*
fydelis_timeline_view_new(FydelisTimeline *tl)
{
    FydelisTimelineView *self = g_object_new(FYDELIS_TYPE_TIMELINE_VIEW, NULL);
    fydelis_timeline_view_set_timeline(self, tl);
    return GTK_WIDGET(self);
}

void
fydelis_timeline_view_set_timeline(FydelisTimelineView *self, FydelisTimeline *tl)
{
    g_return_if_fail(self != NULL);

    if (self->timeline)
        g_object_unref(self->timeline);

    self->timeline = tl;

    if (tl)
        g_object_ref(tl);

    gtk_widget_queue_draw(GTK_WIDGET(self));
}
