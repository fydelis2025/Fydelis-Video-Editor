QT       += core gui widgets

TARGET = FydelisVideoEditor
TEMPLATE = app

VERSION = 1.0.0-ia
DEFINES += FYDELIS_VERSION=\\\"$$VERSION\\\"

CONFIG += c++17 warn_on release

INCLUDEPATH += $$PWD/include

# ⚡ AQUI ESTÁ A CORREÇÃO: .c em vez de .cpp
SOURCES += \
    $$PWD/src/main.c \
    $$PWD/src/core/timeline.c \
    $$PWD/src/core/clip.c \
    $$PWD/src/core/exporter.c \
    $$PWD/src/core/renderer.c \
    $$PWD/src/core/ffmpeg-utils.c \
    $$PWD/src/ui/main-window.c \
    $$PWD/src/ui/timeline-view.c \
    $$PWD/src/ui/ai-panel.c \
    $$PWD/src/ui/media-library.c \
    $$PWD/src/ui/export-dialog.c \
    $$PWD/src/ai/whisper-bridge.c \
    $$PWD/src/ai/denoise.c

HEADERS += \
    $$PWD/include/fydelis-editor.h \
    $$PWD/include/core/timeline.h \
    $$PWD/include/core/clip.h \
    $$PWD/include/core/exporter.h \
    $$PWD/include/core/renderer.h \
    $$PWD/include/core/ffmpeg-utils.h \
    $$PWD/include/ui/main-window.h \
    $$PWD/include/ui/timeline-view.h \
    $$PWD/include/ui/ai-panel.h \
    $$PWD/include/ui/media-library.h \
    $$PWD/include/ui/export-dialog.h \
    $$PWD/include/ai/whisper-bridge.h \
    $$PWD/include/ai/denoise.h

DEFINES += MODELS_DIR=\\\"$$PWD/models\\\"

DESTDIR = $$PWD/bin
