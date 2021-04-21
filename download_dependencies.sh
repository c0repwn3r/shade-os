#!/bin/bash
echo Downloading crosscompilation tools.
wget https://coresdev.ml/cdn/gcc-crosscompiler.zip
echo Extracting.
unzip gcc-crosscompiler.zip
echo Ready to build. Ensure grub is installed before proceeding.
