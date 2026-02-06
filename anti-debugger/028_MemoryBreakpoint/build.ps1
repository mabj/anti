# Build script for Visual Studio projects

# Function to capture environment variables from batch file
function Invoke-BatchFile {
    param([string]$Path, [string]$Arguments)
    $tempFile = [IO.Path]::GetTempFileName()
    cmd.exe /c "`"$Path`" $Arguments && set > `"$tempFile`""
    Get-Content $tempFile | ForEach-Object {
        if ($_ -match "^(.*?)=(.*)$") {
            Set-Content env:"$($matches[1])" $matches[2]
        }
    }
    Remove-Item $tempFile
}

# Parameters
$architecture = $args[0]

# Visual Studio VC compiler path
$vcVarsPath = "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat"

# Set environment variables
if ($architecture -eq "amd64") {
    Invoke-BatchFile -Path $vcVarsPath -Arguments "amd64"
    $outputDir = "build/amd64"
    $exeName = "bin/sample_MemoryBreakpoint_amd64.exe"
    $cflags = "/W4 /std:c11 /MT /D_CRT_SECURE_NO_WARNINGS /EHa /D_AMD64_ /fp:fast /Os /GL /Gy"
    $ldflags = "/link /LTCG:OFF /MACHINE:X64 kernel32.lib user32.lib legacy_stdio_definitions.lib"
}
elseif ($architecture -eq "x86") {
    Invoke-BatchFile -Path $vcVarsPath -Arguments "x86"
    $outputDir = "build/x86"
    $exeName = "bin/sample_MemoryBreakpoint_x86.exe"
    $cflags = "/W4 /std:c11 /MT /D_CRT_SECURE_NO_WARNINGS /EHa /D_X86_ /arch:SSE2 /Os /GL /Gy"
    $ldflags = "/link /LTCG:OFF /MACHINE:X86 kernel32.lib user32.lib legacy_stdio_definitions.lib"
}
else {
    Write-Host "Invalid architecture. Use 'amd64' or 'x86'"
    exit 1
}

# Create directories
New-Item -ItemType Directory -Force -Path $outputDir | Out-Null
New-Item -ItemType Directory -Force -Path bin | Out-Null

# Compile and link
$arguments = @("/nologo", "/c", "src/main.c") + ($cflags -split ' ') + @("/Fo$outputDir/main.obj")
& cl.exe $arguments

$linkArguments = @("/nologo", "/Fe$exeName", "$outputDir/main.obj") + ($ldflags -split ' ')
& cl.exe $linkArguments

Write-Host "Built $architecture executable: $exeName"
