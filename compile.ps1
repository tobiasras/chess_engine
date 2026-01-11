Write-host $PSScriptRoot;


# compile chess engine
# Paths
$sourceDir = "$PSScriptRoot"
$buildDir  = "$PSScriptRoot\build"

$engineExe = "$buildDir\chess_engine.exe"
$pgnFile   = "$buildDir\results.pgn"
#$cuteChessCLI = "C:\Tools\cutechess-cli.exe"


# 1. Create build folder if it doesn't exist
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir
}

# 2. Run CMake configure + build
Write-Host "Configuring CMake..."
cmake -S $sourceDir -B $buildDir -G "Visual Studio 17 2022" -A x64

Write-Host "Building engine..."
cmake --build $buildDir --config Release


