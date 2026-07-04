#!/usr/bin/env bash
# Simple installer wrapper for the compressor utility
set -euo pipefail

PREFIX=${PREFIX:-/usr/local}

echo "Building..."
make

echo "Installing to ${PREFIX}/bin (may require sudo)"
if [ ! -w "${PREFIX}/bin" ]; then
  echo "Directory ${PREFIX}/bin not writable; using sudo to install"
  sudo install -d "${PREFIX}/bin"
  sudo install -m 0755 compressor "${PREFIX}/bin/compressor"
else
  install -d "${PREFIX}/bin"
  install -m 0755 compressor "${PREFIX}/bin/compressor"
fi

echo "Installed compressor to ${PREFIX}/bin/compressor"
