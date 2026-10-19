#!/bin/bash
set -e
mkdir -p models
cd models

echo "📦 Baixando modelos para o Fydelis..."

# Whisper (ggml formato compatível com whisper.cpp)
echo "Baixando Whisper Base..."
wget -c https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-base.bin

echo "Baixando Whisper Small..."
wget -c https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-small.bin

# RNNoise
echo "Baixando RNNoise..."
wget -c https://raw.githubusercontent.com/xiph/rnnoise/master/models/rnnoise-model.bin

# YOLOv8n (formato ONNX)
echo "Baixando YOLOv8n..."
wget -c https://github.com/ultralytics/assets/releases/download/v8.3.0/yolov8n.onnx

# Real-ESRGAN x4
echo "Baixando Real-ESRGAN x4..."
wget -c https://github.com/xinntao/Real-ESRGAN/releases/download/v0.1.0/RealESRGAN_x4.onnx \
     -O realesrgan-x4.onnx

echo "✅ Todos os modelos baixados em models/"
ls -lh