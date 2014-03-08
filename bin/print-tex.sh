#/bin/bash

pushd article

rm -rfv ../target/Main*
pdflatex --output-directory=../target/ Main.tex
pdflatex --output-directory=../target/ Main.tex

popd

# Run script twice, because .toc file is created
# and considered as Table of Contents
