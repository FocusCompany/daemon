#!/usr/bin/env bash

set -eou pipefail

if [[ "$1" = "turn_on" ]]; then
  defaults -currentHost write ~/Library/Preferences/ByHost/com.apple.notificationcenterui doNotDisturb -boolean true
  defaults -currentHost write ~/Library/Preferences/ByHost/com.apple.notificationcenterui doNotDisturbDate -date "`date -u +\"%Y-%m-%d %H:%M:%S +000\"`"
  killall NotificationCenter
  echo -n "ok"
elif [[ "$1" = "turn_off" ]]; then
  defaults -currentHost write ~/Library/Preferences/ByHost/com.apple.notificationcenterui doNotDisturb -boolean false
  killall NotificationCenter
  echo -n "ok"
elif [[ "$1" = "get_state" ]]; then
  [[ $(defaults -currentHost read ~/Library/Preferences/ByHost/com.apple.notificationcenterui doNotDisturb) -eq 0 ]] && echo -n "off" || echo -n "on"
fi
