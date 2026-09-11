set -euo pipefail
 
SDL_VERSION="3.4.12"
INSTALL_DEPS=0
FORCE=0
 
while [ $# -gt 0 ]; do
    case "$1" in
        --version)      SDL_VERSION="$2"; shift 2 ;;
        --install-deps) INSTALL_DEPS=1; shift ;;
        --force)        FORCE=1; shift ;;
        *) echo "Unknown argument: $1" >&2; exit 1 ;;
    esac
done
 
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
THIRDPARTY_SDL="$REPO_ROOT/ThirdParty/SDL"
DEST_INCLUDE="$THIRDPARTY_SDL/include"
DEST_LIB="$THIRDPARTY_SDL/lib/linux-x64"
STAMP_FILE="$THIRDPARTY_SDL/.sdl3-linux-version"
 
WORK_DIR="$(mktemp -d)"
trap 'rm -rf "$WORK_DIR"' EXIT
 
if [ "$FORCE" -eq 0 ] && [ -f "$STAMP_FILE" ] && [ "$(cat "$STAMP_FILE")" = "$SDL_VERSION" ] \
   && [ -f "$DEST_LIB/libSDL3.so" ]; then
    echo "SDL3 $SDL_VERSION already vendored at $THIRDPARTY_SDL (use --force to rebuild)."
    exit 0
fi
 
if [ "$INSTALL_DEPS" -eq 1 ]; then
    if command -v apt-get >/dev/null 2>&1; then
        echo "==> Installing SDL3 Linux build dependencies (apt, Debian/Ubuntu) ..."
        sudo apt-get update
        sudo apt-get install -y \
            build-essential git make pkg-config cmake ninja-build \
            clang gdb \
            libasound2-dev libpulse-dev libaudio-dev libfribidi-dev \
            libjack-dev libsndio-dev libx11-dev libxext-dev libxrandr-dev \
            libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
            libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev \
            libgles2-mesa-dev libegl1-mesa-dev libdbus-1-dev \
            libibus-1.0-dev libudev-dev libthai-dev libusb-1.0-0-dev \
            libwayland-dev libdecor-0-dev liburing-dev
    elif command -v dnf >/dev/null 2>&1; then
        echo "==> Installing SDL3 Linux build dependencies (dnf, Fedora/RHEL) ..."
        sudo dnf install -y \
            gcc gcc-c++ git-core make cmake ninja-build pkgconf-pkg-config \
            clang gdb \
            alsa-lib-devel fribidi-devel pulseaudio-libs-devel pipewire-devel \
            libX11-devel libXext-devel libXrandr-devel libXcursor-devel \
            libXfixes-devel libXi-devel libXScrnSaver-devel libXtst-devel \
            dbus-devel ibus-devel systemd-devel mesa-libGL-devel \
            libxkbcommon-devel mesa-libGLES-devel mesa-libEGL-devel \
            vulkan-devel wayland-devel wayland-protocols-devel \
            libdrm-devel mesa-libgbm-devel libusb1-devel
    else
        echo "warning: --install-deps only automates apt-get (Debian/Ubuntu)" >&2
        echo "         and dnf (Fedora/RHEL). Install the equivalent -dev" >&2
        echo "         packages for your distro yourself:" >&2
        echo "         https://wiki.libsdl.org/SDL3/README-linux" >&2
    fi
fi
 
for tool in curl tar cmake; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "error: '$tool' is required but not found on PATH." >&2
        exit 1
    fi
done
 
TARBALL_URL="https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL3-${SDL_VERSION}.tar.gz"
TARBALL_PATH="$WORK_DIR/SDL3-${SDL_VERSION}.tar.gz"
 
echo "==> Downloading SDL3 ${SDL_VERSION} source ..."
curl -fL --progress-bar -o "$TARBALL_PATH" "$TARBALL_URL"
 
echo "==> Extracting ..."
tar -xzf "$TARBALL_PATH" -C "$WORK_DIR"
SRC_DIR="$WORK_DIR/SDL3-${SDL_VERSION}"
 
echo "==> Configuring (CMake) ..."
BUILD_DIR="$WORK_DIR/build"
STAGE_DIR="$WORK_DIR/stage"
cmake -S "$SRC_DIR" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="$STAGE_DIR" \
    -DSDL_SHARED=ON \
    -DSDL_STATIC=OFF \
    -DSDL_TEST_LIBRARY=OFF \
    -DSDL_TESTS=OFF \
    -DSDL_DISABLE_INSTALL_DOCS=ON
 
echo "==> Building ..."
cmake --build "$BUILD_DIR" --parallel "$(nproc)"
 
echo "==> Installing to staging dir ..."
cmake --install "$BUILD_DIR"
 
echo "==> Vendoring headers and shared library into $THIRDPARTY_SDL ..."
mkdir -p "$DEST_INCLUDE" "$DEST_LIB"
cp -r "$STAGE_DIR"/include/SDL3 "$DEST_INCLUDE/"
cp -Pv "$STAGE_DIR"/lib*/libSDL3.so* "$DEST_LIB/"
 
echo "$SDL_VERSION" > "$STAMP_FILE"
 
echo "Done. SDL3 ${SDL_VERSION} headers -> $DEST_INCLUDE/SDL3, lib -> $DEST_LIB"