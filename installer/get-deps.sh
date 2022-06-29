#!/bin/bash

# GTA III
mkdir build/gta3 -p
cp "fake-host.exe" "build/gta3/gta3.exe"
cp "../cleo_redux.asi" "build/gta3/cleo_redux.asi"
cd build/gta3
./gta3.exe
cd ../..

# vc
mkdir build/vc -p
cp "fake-host.exe" "build/vc/gta-vc.exe"
cp "../cleo_redux.asi" "build/vc/cleo_redux.asi"
cd build/vc
./gta-vc.exe
cd ../..

# sa
mkdir build/sa -p
cp "fake-host.exe" "build/sa/gta-sa.exe"
cp "../cleo_redux.asi" "build/sa/cleo_redux.asi"
cd build/sa
./gta-sa.exe
cd ../..

# gta_iv
mkdir build/gta_iv -p
cp "fake-host.exe" "build/gta_iv/gtaiv.exe"
cp "../cleo_redux.asi" "build/gta_iv/cleo_redux.asi"
cd build/gta_iv
./gtaiv.exe
cd ../..

# gta3_unreal
mkdir build/gta3_unreal -p
cp "fake-host64.exe" "build/gta3_unreal/libertycity.exe"
cp "../cleo_redux64.asi" "build/gta3_unreal/cleo_redux64.asi"
cd build/gta3_unreal
./libertycity.exe
cd ../..

# vc_unreal
mkdir build/vc_unreal -p
cp "fake-host64.exe" "build/vc_unreal/vicecity.exe"
cp "../cleo_redux64.asi" "build/vc_unreal/cleo_redux64.asi"
cd build/vc_unreal
./vicecity.exe
cd ../..

# sa_unreal
mkdir build/sa_unreal -p
cp "fake-host64.exe" "build/sa_unreal/sanandreas.exe"
cp "../cleo_redux64.asi" "build/sa_unreal/cleo_redux64.asi"
cd build/sa_unreal
./sanandreas.exe
cd ../..

# unknown_x86
mkdir build/unknown_x86 -p
cp "fake-host.exe" "build/unknown_x86/unknown.exe"
cp "../cleo_redux.asi" "build/unknown_x86/cleo_redux.asi"
cd build/unknown_x86
./unknown.exe
cd ../..

# unknown_x64
mkdir build/unknown_x64 -p
cp "fake-host64.exe" "build/unknown_x64/unknown.exe"
cp "../cleo_redux64.asi" "build/unknown_x64/cleo_redux64.asi"
cd build/unknown_x64
./unknown.exe
cd ../..

