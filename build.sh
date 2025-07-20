#!/bin/bash

DEPENDENCIES=(gcc nasm make)

SHELL_NAME=$(basename "$SHELL")
if [[ "$SHELL_NAME" == "zsh" ]]; then
    CONFIG_FILE="$HOME/.zshrc"
elif [[ "$SHELL_NAME" == "bash" ]]; then
    CONFIG_FILE="$HOME/.bashrc"
elif [[ "$SHELL_NAME" == "fish" ]]; then
    CONFIG_FILE="$HOME/.config/fish/config.fish"
else
    echo "Unsupported shell: $SHELL_NAME"
    exit 1
fi

BLC_DIR="$(cd "$(dirname "$0")/application" && pwd)"
BLC_PATH="$BLC_DIR/blc"

if command -v apt &>/dev/null; then
    INSTALL_CMD="sudo apt install -y"
    UPDATE_CMD="sudo apt update"
elif command -v brew &>/dev/null; then
    INSTALL_CMD="brew install"
    UPDATE_CMD="brew update"
elif command -v dnf &>/dev/null; then
    INSTALL_CMD="sudo dnf install -y"
    UPDATE_CMD="sudo dnf check-update"
elif command -v pacman &>/dev/null; then
    INSTALL_CMD="sudo pacman -S --noconfirm"
    UPDATE_CMD="sudo pacman -Sy"
else
    echo "❌ No supported package manager found (apt, brew, dnf, pacman)"
    exit 1
fi

echo "🔍 Checking dependencies..."
for dep in "${DEPENDENCIES[@]}"; do
    if ! command -v "$dep" &>/dev/null; then
        echo "⚠️  $dep not found. Installing..."
        $UPDATE_CMD
        $INSTALL_CMD "$dep" || {
            echo "❌ Failed to install $dep"
            exit 1
        }
    else
        echo "✅ $dep is installed."
    fi
done

if [[ ! -x "$BLC_PATH" ]]; then
    echo "⚙️  Building 'blc'..."
    make 
    if [[ -f "blc" ]]; then
        mv -f blc "$BLC_PATH"
        chmod +x "$BLC_PATH"
        echo "✅ 'blc' moved to $BLC_PATH"
    else
        echo "❌ Build failed: 'blc' not found after make"
        exit 1
    fi
fi

EXPORT_LINE="export PATH=\"\$PATH:$BLC_DIR\""
if [[ "$SHELL_NAME" == "fish" ]]; then
    EXPORT_LINE="set -gx PATH \"$BLC_DIR\" \$PATH"
    if ! grep -q "set -gx PATH.*\"$BLC_DIR\"" "$CONFIG_FILE"; then
        echo "$EXPORT_LINE" >> "$CONFIG_FILE"
        echo "✅ Added blc to PATH in $CONFIG_FILE (Fish shell)"
    else
        echo "ℹ️  blc path already in $CONFIG_FILE (Fish shell)"
    fi
else
    if ! grep -Fxq "$EXPORT_LINE" "$CONFIG_FILE"; then
        echo "$EXPORT_LINE" >> "$CONFIG_FILE"
        echo "✅ Added blc to PATH in $CONFIG_FILE"
    else
        echo "ℹ️  blc path already in $CONFIG_FILE"
    fi
fi

cat << EOF

██████╗ ██╗  ██╗ █████╗ ██╗   ██╗ ██╗       █████╗ ███╗  ██╗ ██████╗ 
██╔══██╗██║  ██║██╔══██╗██║   ██║ ██║      ██╔══██╗████╗ ██║██╔════╝ 
██████╔╝███████║███████║██║   ██║ ██║      ███████║██╔██╗██║██║  ███╗
██╔══██╗██╔══██║██╔══██║╚██╗ ██╔╝ ██║      ██╔══██║██║╚████║██║   ██║
██████╔╝██║  ██║██║  ██║ ╚████╔╝  ███████╗ ██║  ██║██║ ╚████║╚██████╔╝
╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝  ╚═══╝   ╚══════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝                                   

                        Welcome to BhauLang! 


✅  Compiler Installed
✅  PATH Updated
ℹ️   Please run: source $CONFIG_FILE

EOF