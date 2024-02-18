$buildDir = ".\build"
$executablePath = Join-Path -Path $buildDir -ChildPath "Techhi.exe"

if (-not (Test-Path $buildDir)) {
    New-Item -Path $buildDir -ItemType Directory
}

cmake -G "MinGW Makefiles" -S . -B $buildDir
mingw32-make -C $buildDir

if (Test-Path $executablePath -PathType Leaf) {
    Start-Process -FilePath $executablePath
} else {
    Write-Host "Executable not found: $executablePath"
}