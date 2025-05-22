#!/bin/bash

START=${1:-10}
END=${2:-30}
MAX_JOBS=$(nproc)
BUILDDIR="/home/tahea/edu/Geant4_proj2/simplegeo/build"
EXE="${BUILDDIR}/main.exe"
OUT_LIST="${BUILDDIR}/results/output.list"

: > "$OUT_LIST"
JOBS=0

for NLAYERS in $(seq $START $END); do
    if (( JOBS >= MAX_JOBS )); then
        wait -n
        ((JOBS--))
    fi
    (
        cd /home/tahea/edu/Geant4_proj2/simplegeo/build || exit 1
        "$EXE" "$NLAYERS"
        echo "${BUILDDIR}/results/rm_vs_layers_${NLAYERS}.txt" >> "$OUT_LIST"
    ) &
    ((JOBS++))
done

wait
./process
echo "Готово. Все результаты в build/results/, список файлов в $OUT_LIST"
