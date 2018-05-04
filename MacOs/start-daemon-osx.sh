#!/bin/sh

K3D_BUNDLE="`echo "$0" | sed -e 's/\/Contents\/MacOS\/Focus//'`"

export "DYLD_LIBRARY_PATH=$K3D_BUNDLE/Contents/Resources/lib"

#export
exec "$K3D_BUNDLE/Contents/Resources/bin/focus-daemon"
