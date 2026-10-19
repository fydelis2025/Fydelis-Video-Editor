#!/bin/bash
set -e

# Cores do Fydelis
COR_PRINCIPAL="#7C3AED"
COR_ESCURO="#0F0A1E"

echo "🎨 Gerando ícones SVG do Fydelis..."

# Criar pasta se não existir
mkdir -p assets/icons
cd assets/icons

# Função auxiliar
criar_icone() {
  nome="$1"
  conteudo="$2"
  echo "$conteudo" > "$nome.svg"
  echo "✅ $nome.svg"
}

# 📄 Novo Documento
criar_icone "document-new" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8l-6-6zm-1 7V3.5L19.5 9H13z'/>
</svg>"

# 📁 Abrir
criar_icone "document-open" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M20 6h-8l-2-2H4a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h16a2 2 0 0 0 2-2V8a2 2 0 0 0-2-2zm0 12H4V8h16v10z'/>
</svg>"

# 💾 Salvar
criar_icone "document-save" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M17 3H5a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2V7l-4-4zm-5 16a3 3 0 1 1 0-6 3 3 0 0 1 0 6zm4-10H6V5h10v4z'/>
</svg>"

# ▶️ Play
criar_icone "media-playback-start" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M8 5v14l11-7z'/>
</svg>"

# ⏹️ Stop
criar_icone "media-playback-stop" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M6 6h12v12H6z'/>
</svg>"

# ⏮️ Recuar
criar_icone "media-skip-backward" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M6 6h2v12H6V6zm3.5 6l8.5 6V6l-8.5 6z'/>
</svg>"

# ⏭️ Avançar
criar_icone "media-skip-forward" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M16 6h2v12h-2V6zM6 18l8.5-6L6 6v12z'/>
</svg>"

# ✂️ Cortar/Dividir
criar_icone "edit-cut" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M6 3l4 4-4 4 1.5 1.5L10 9l4 4-4 4-1.5-1.5L6 17l4 4 1.5-1.5L12 17l4 4 1.5-1.5L14 17l-4-4 4-4 1.5-1.5L14 7l-4 4-1.5-1.5L6 3zm10 10l4.5 4.5-1.5 1.5L14 14.5l2-1.5zm0-6l2 1.5 4.5-4.5-1.5-1.5L16 7z'/>
</svg>"

# 🗑️ Apagar
criar_icone "edit-delete" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M6 19a2 2 0 0 0 2 2h8a2 2 0 0 0 2-2V7H6v12zM19 4h-3.5l-1-1h-5l-1 1H5v2h14V4z'/>
</svg>"

# 🔍 Zoom-mais
criar_icone "zoom-in" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M15.5 14h-.79l-.28-.27A6.47 6.47 0 0 0 16 9.5 6.5 6.5 0 1 0 9.5 16c1.61 0 3.09-.59 4.23-1.57l.27.28v.79l5 4.99L20.49 19l-4.99-5zm-6 0C7.01 14 5 11.99 5 9.5S7.01 5 9.5 5 14 7.01 14 9.5 11.99 14 9.5 14zm1-7H9v2H7v1h2v2h1v-2h2V9h-2V7z'/>
</svg>"

# 🔍 Zoom-menos
criar_icone "zoom-out" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M15.5 14h-.79l-.28-.27A6.47 6.47 0 0 0 16 9.5 6.5 6.5 0 1 0 9.5 16c1.61 0 3.09-.59 4.23-1.57l.27.28v.79l5 4.99L20.49 19l-4.99-5zm-6 0C7.01 14 5 11.99 5 9.5S7.01 5 9.5 5 14 7.01 14 9.5 11.99 14 9.5 14zm-2-2h4V10H7v2z'/>
</svg>"

# 🔍 Ajustar Tudo
criar_icone "zoom-fit-best" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M17 4h-3V2h3c1.1 0 2 .9 2 2v3h-2V4zm0 16h-3v2h3c1.1 0 2-.9 2-2v-3h-2v3zM7 4H4c-1.1 0-2 .9-2 2v3h2V4h3zM4 20h3v2H4c-1.1 0-2-.9-2-2v-3h2v3zM18 8H6v8h12V8zm-2 6H8v-4h8v4z'/>
</svg>"

# 🧠 Cérebro / IA
criar_icone "brain" "<?xml version='1.0' encoding='UTF-8'?>
<svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24'>
  <path fill='$COR_PRINCIPAL' d='M12 2a4 4 0 0 0-4 4v1H7a3.5 3.5 0 0 0-3.5 3.5c0 .63.17 1.21.46 1.72A3.49 3.49 0 0 0 3 15.5c0 1.93 1.57 3.5 3.5 3.5H9v1a4 4 0 0 0 4 4 4 4 0 0 0 4-4v-1h2.5c1.93 0 3.5-1.57 3.5-3.5 0-1.58-1.05-2.9-2.5-3.33.29-.51.46-1.09.46-1.72A3.5 3.5 0 0 0 17 7h-1V6a4 4 0 0 0-4-4zm-1 7h2v3h-2V9zm-2 0v3H7V9h2zm6 0h2v3h-2V9zm-6 5h2v3H9v-3zm4 0h2v3h-2v-3z'/>
</svg>"

cd ..
echo ""
echo "🎉 Todos os ícones criados em assets/icons/"
ls -1 assets/icons/*.svg
