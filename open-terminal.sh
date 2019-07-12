#!/bin/bash
ACTIVE_WINDOW=$(xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2)

WINDOW_NAME=$(xprop -id "${ACTIVE_WINDOW}" _NET_WM_NAME | sed 's/.*: //' | sed 's/"//')

i3-sensible-terminal -cd "${WINDOW_NAME}"
