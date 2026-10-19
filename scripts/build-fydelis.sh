#!/bin/bash
set -e

# ==========================================
# Fydelis Video Editor — Script de Build
# ==========================================

echo "=========================================="
echo "  Fydelis Video Editor — Build Script"
echo "=========================================="
echo ""

# Detectar distro
if command -v apt &> /dev/null; then
    PKG_MANAGER="apt"
elif command -v pacman &> /dev/null; then
    PKG_MANAGER="pacman"
else
    echo "❌ Distro não suportada automaticamente. Instale as dependências manualmente."
    exit 1
fi

# ==========================================
# PASSO 1 — Instalar dependências do sistema
# ==========================================
echo "[1/6] Instalando dependências do sistema..."

if [ "$PKG_MANAGER" = "apt" ]; then
    sudo apt update
    sudo apt install -y --no-install-recommends \
        build-essential git meson pkg-config \
        libgtk-4-dev \
        libavformat-dev libavcodec-dev libavutil-dev \
        libswscale-dev libswresample-dev \
        libglib2.0-dev libgirepository1.0-dev \
        wget
elif [ "$PKG_MANAGER" = "pacman" ]; then
    sudo pacman -S --noconfirm --needed \
        base-devel git meson pkgconfig \
        gtk4 ffmpeg glib2 wget
fi

echo "✅ Dependências do sistema instaladas"
echo ""

# ==========================================
# PASSO 2 — Criar pastas necessárias
# ==========================================
echo "[2/6] Criando estrutura de pastas..."
mkdir -p assets/icons models lib build scripts
echo "✅ Pastas prontas"
echo ""

# ==========================================
# PASSO 3 — Baixar modelos de IA
# ==========================================
echo "[3/6] Baixando modelos de IA (~670 MB)..."
cd models

# Whisper — ggml-small.bin (recomendado para PT-BR)
if [ ! -f "ggml-small.bin" ]; then
    echo "→ Whisper Small..."
    wget -q --show-progress "https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-small.bin"
else
    echo "✓ ggml-small.bin já existe, pulando"
fi

# RNNoise
if [ ! -f "rnnoise-model.bin" ]; then
    echo "→ RNNoise..."
    wget -q --show-progress "https://raw.githubusercontent.com/xiph/rnnoise/master/models/rnnoise-model.bin"
else
    echo "✓ rnnoise-model.bin já existe, pulando"
fi

cd ..
echo "✅ Modelos prontos em models/"
echo ""

# ==========================================
# PASSO 4 — Compilar e instalar Whisper.cpp
# ==========================================
echo "[4/6] Compilando Whisper.cpp..."
cd lib

if [ ! -d "whisper" ]; then
    git clone --depth 1 "https://github.com/ggerganov/whisper.cpp.git"
fi

cd whisper
make -j$(nproc)
sudo make install
cd ../../

echo "✅ Whisper.cpp instalado no sistema"
echo ""

# ==========================================
# PASSO 5 — Configurar build do Fydelis
# ==========================================
echo "[5/6] Configurando Fydelis..."
rm -rf build
meson setup build --prefix=/usr --buildtype=release

echo "✅ Configuração concluída"
echo ""

# ==========================================
# PASSO 6 — Compilar
# ==========================================
echo "[6/6] Compilando Fydelis Video Editor..."
ninja -C build -j$(nproc)

echo ""
echo "=========================================="
echo "  ✅ BUILD CONCLUÍDO COM SUCESSO!"
echo "=========================================="
echo ""
echo "Para rodar:"
echo "  ./build/fydelis-editor"
echo ""
echo "Para instalar no sistema:"
echo "  sudo ninja -C build install"
echo ""