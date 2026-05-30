#!/bin/bash
POS_FILE="$1"
sed -i -e '1s/Ref/Designator/' -e '1s/Pos/Mid /g' -e '1s/Rot/Rotation/' -e '1s/Side/Layer/' "$POS_FILE"
