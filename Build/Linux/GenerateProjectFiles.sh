set -euo pipefail

PREMAKE_VERSION="${PREMAKE_VERSION:-5.0.0-beta8}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

ACTION="${1:-gmake}"
VENDOR_PREMAKE_DIR="$REPO_ROOT/vendor/bin/premake"
VENDORED_PREMAKE="$VENDOR_PREMAKE_DIR/premake5"

resolve_premake_bin() {
    if [ -n "${PREMAKE_BIN:-}" ]; then
        echo "$PREMAKE_BIN"
        return
    fi
    if [ -x "$VENDORED_PREMAKE" ]; then
        echo "$VENDORED_PREMAKE"
        return
    fi
    if command -v premake5 >/dev/null 2>&1; then
        echo "premake5"
        return
    fi
    echo ""
}

PREMAKE_BIN="$(resolve_premake_bin)"

if [ -z "$PREMAKE_BIN" ]; then
    echo "premake5 not found on PATH or vendored at $VENDORED_PREMAKE; downloading v$PREMAKE_VERSION ..."
    TMP_DIR="$(mktemp -d)"
    trap 'rm -rf "$TMP_DIR"' EXIT
    TARBALL_URL="https://github.com/premake/premake-core/releases/download/v${PREMAKE_VERSION}/premake-${PREMAKE_VERSION}-linux.tar.gz"
    curl -fL --progress-bar -o "$TMP_DIR/premake5.tar.gz" "$TARBALL_URL"
    tar -xzf "$TMP_DIR/premake5.tar.gz" -C "$TMP_DIR"
    mkdir -p "$VENDOR_PREMAKE_DIR"
    install -m 0755 "$TMP_DIR/premake5" "$VENDORED_PREMAKE"
    PREMAKE_BIN="$VENDORED_PREMAKE"
    echo "Vendored premake5 v$PREMAKE_VERSION at $VENDORED_PREMAKE"
fi

echo "Searching for workspace premake5.lua files under $REPO_ROOT ..."

mapfile -t SCRIPTS < <(grep -l -R --include="premake5.lua" -E "^\s*workspace\s*\"" "$REPO_ROOT")

if [ ${#SCRIPTS[@]} -eq 0 ]; then
    echo "No workspace premake5.lua files found." >&2
    exit 1
fi

for script in "${SCRIPTS[@]}"; do
    dir="$(dirname "$script")"
    echo "==> Generating ($ACTION) for $script"
    (cd "$dir" && "$PREMAKE_BIN" "$ACTION")
done

echo "Done."
