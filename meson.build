project('fydelis-video-editor', 'c', 'cpp',
  version: '1.0.0-ia',
  license: 'GPL-3.0',
  default_options: [
    'c_std=c17',
    'cpp_std=c++17',
    'warning_level=3',
    'buildtype=release',
    'c_args=-D_GNU_SOURCE=1 -D_POSIX_C_SOURCE=200809L',
    'cpp_args=-D_GNU_SOURCE=1 -D_POSIX_C_SOURCE=200809L'
  ]
)

gnome = import('gnome')
cc = meson.get_compiler('c')

gtk4_dep = dependency('gtk4', version: '>=4.12')
avformat_dep = dependency('libavformat')
avcodec_dep = dependency('libavcodec')
avutil_dep = dependency('libavutil')
swscale_dep = dependency('libswscale')
swresample_dep = dependency('libswresample')
m_dep = cc.find_library('m', required: true)

inc_root = include_directories('include')
inc_core = include_directories('include/core')
inc_ui = include_directories('include/ui')
inc_ai = include_directories('include/ai')
inc_whisper = include_directories('third_party/whisper')

src = files(
  'src/main.c',
  'src/core/timeline.c',
  'src/core/clip.c',
  'src/core/exporter.c',
  'src/core/renderer.c',
  'src/core/ffmpeg-utils.c',
  'src/ui/main-window.c',
  'src/ui/timeline-view.c',
  'src/ui/ai-panel.c',
  'src/ui/media-library.c',
  'src/ai/whisper-bridge.c'
)

# Arquivos do Whisper
src += files(
  'third_party/whisper/whisper.cpp',
  'third_party/whisper/ggml.c',
  'third_party/whisper/ggml-alloc.c',
  'third_party/whisper/ggml-backend.c',
  'third_party/whisper/ggml-quants.c'
)

res = gnome.compile_resources(
    'fydelis-resources',
    'resources.gresource.xml',
    source_dir: '.',
    c_name: 'fydelis_res',  
    export: true
)

executable('fydelis-editor',
  src,
  res,
  include_directories: [
    inc_root,
    inc_core,
    inc_ui,
    inc_ai,
    inc_whisper
  ],
  dependencies: [
    gtk4_dep,
    avformat_dep,
    avcodec_dep,
    avutil_dep,
    swscale_dep,
    swresample_dep,
    m_dep
  ],
  link_args: '-ldl',
  install: true
)
