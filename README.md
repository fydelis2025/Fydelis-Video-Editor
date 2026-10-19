# 🎬 Fydelis Video Editor

> Editor de vídeo livre, multiplataforma e com inteligência artificial — desenvolvido em C + GTK4

![Versão](https://img.shields.io/badge/versão-1.0.0--ia-purple.svg)
![Plataforma](https://img.shields.io/badge/plataforma-Linux%20%7C%20Windows-blue.svg)
![Licença](https://img.shields.io/badge/licença-MIT-green.svg)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow.svg)

---

## 📋 Sobre o Projeto

O **Fydelis Video Editor** é um editor de vídeo open source focado em simplicidade, desempenho e recursos de Inteligência Artificial nativos:

- 🧠 **Legendas automáticas** com Whisper
- 🔊 **Remoção de ruído** de áudio com RNNoise
- 🖼️ **Melhoria de imagem** com Real-ESRGAN
- 🎨 Interface moderna com tema roxo exclusivo
- 💻 Leve e rápido — roda em máquinas antigas também

---

## 🚀 Funcionalidades

| Recurso | Status |
|---|---|
| Interface gráfica GTK4 | ✅ Pronto |
| Biblioteca de mídia | ✅ Pronto |
| Linha do tempo interativa | ✅ Em desenvolvimento |
| Pré-visualização de vídeo | ✅ Em desenvolvimento |
| Exportação com FFmpeg | ⏳ Em breve |
| Legendas automáticas (Whisper) | ⏳ Em breve |
| Limpeza de áudio (RNNoise) | ⏳ Em breve |
| Upscale de imagem (Real-ESRGAN) | ⏳ Em breve |

---

## 🛠️ Como Compilar

### Pré-requisitos
- `gcc` ou `clang`
- Meson + Ninja
- GTK 4.0+
- FFmpeg (bibliotecas: `libavformat`, `libavcodec`, `libavutil`, `libswscale`)

### No Linux:
```bash
# Clonar repositório
git clone https://github.com/fydelis2025/Fydelis-Video-Editor.git
cd Fydelis-Video-Editor

# Compilar
meson setup build
ninja -C build

# Executar
./build/fydelis-editor
