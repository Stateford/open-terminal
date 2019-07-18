#!/usr/bin/env bash

set -e
set +x

TERMINAL_I3=i3-sensible-terminal

function is_empty {
    if [ -z "$1" ]; then
        eval "$TERMINAL_I3"
    fi
}

ACTIVE_WINDOW=$(xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2)

is_empty "$ACTIVE_WINDOW"

WINDOW_NAME=$(xprop -id "${ACTIVE_WINDOW}" _NET_WM_NAME | sed 's/.*: //' | sed 's/"//')

is_empty "$WINDOW_NAME"

OPEN_TERMINAL="$TERMINAL_I3 -cd $WINDOW_NAME"
eval "$OPEN_TERMINAL"
