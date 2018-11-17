#!/usr/bin/env bash

set -eou pipefail

if [[ "$1" = "turn_on" ]]; then
  gsettings set org.gnome.desktop.notifications show-banners false
  echo -n "ok"
elif [[ "$1" = "turn_off" ]]; then
  gsettings set org.gnome.desktop.notifications show-banners true
  echo -n "ok"
elif [[ "$1" = "get_state" ]]; then
  [[ "$(gsettings get org.gnome.desktop.notifications show-banners)" = "true" ]] && echo -n "off" || echo -n "on"
fi
