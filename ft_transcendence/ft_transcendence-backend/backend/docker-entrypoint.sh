#!/bin/sh
set -e

mkdir -p /app/uploads/avatars

if [ ! -f /app/uploads/avatars/default-avatar.png ]; then
    echo "Copying default avatar to uploads volume..."
    cp /app/default-assets/default-avatar.png /app/uploads/avatars/default-avatar.png
fi

chown -R node:node /app/uploads

exec gosu node "$@"
