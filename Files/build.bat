@echo off
setlocal enabledelayedexpansion

:: --- CONFIGURATION ---
set COMPILER=g++
set TARGET=spaceinvaders.exe
set FLAGS=-Wall -Wextra -O2
set INCLUDES=-I. -Iimgui -ISDL_Image -I"C:\Path\To\SDL3\include"
set LINKS=-L"C:\Path\To\SDL3\lib" -lSDL3 -lSDL3_image

:: --- SOURCES ---
:: On liste les fichiers manuellement pour garder le contrôle
set SRCS=main.cpp Game.cpp Renderer.cpp UI.cpp Utils.cpp ^
imgui\imgui.cpp imgui\imgui_draw.cpp imgui\imgui_tables.cpp ^
imgui\imgui_widgets.cpp imgui\imgui_demo.cpp ^
imgui\imgui_impl_sdl3.cpp imgui\imgui_impl_sdlrenderer3.cpp

echo ------------------------------------------
echo [BUILD] Compilation de %TARGET%...
echo ------------------------------------------

%COMPILER% %FLAGS% %INCLUDES% %SRCS% -o %TARGET% %LINKS%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Compilation REUSSIE !
    echo 🚀 Lancement du jeu...
    echo ------------------------------------------
    %TARGET%
) else (
    echo.
    echo ❌ ERREUR lors de la compilation.
    pause
)
