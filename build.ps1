
param (
    [switch]$clean,    
    [switch]$rebuild,
    [switch]$compile,
    [switch]$help,
    [switch]$test,
    [switch]$doc
)

# Function to display help
function Show-Help {
    Write-Host "Usage: .\build.ps1 [options]"
    Write-Host ""
    Write-Host "Options:"
    Write-Host "  -clean      Clean the build directory."
    Write-Host "  -rebuild    Rebuild the build directory."
    Write-Host "  -compile    Compile the project."
    Write-Host "  -test       Compile and run the tests."
    Write-Host "  -doc        Generate Doxygen documentaion."
    Write-Host "  -help       Show this help message."
    Write-Host ""
    Write-Host "If no options are provided, the script will perform the default actions: clean, rebuild, and compile."
}

# Function to clean the build directory
function Clean {
    Write-Host "Cleaning build directory..."
    meson compile --clean -C builddir
}

# Function to rebuild the build directory
function Rebuild {
    Write-Host "Rebuilding build directory..."
    if (Test-Path -Path builddir) {
        Remove-Item -Recurse -Force builddir
    }
    meson setup builddir
}

# Function to compile the project
function Compile {
    Write-Host "Compiling the project..."
    meson compile -C builddir
}

# Function to run the tests
function Test {
    Write-Host "Running the tests..."
    ./builddir/runtests.exe
}

# Function generate Doxygen documentation
function Write-Doxygen {
    Write-Host "Generating Doxygen documentation..."
    doxygen Doxyfile
}

# Execute actions based on flags
if ($help) {
    Show-Help
    exit
}

if ($clean) {
    Clean
}

if ($rebuild) {
    Rebuild
}

if ($compile) {
    Compile
}

if ($test) {
    Test
}

if ($doc) {
    Write-Doxygen
    exit
}


# Default action if no flags are provided
if (-not ($clean -or $rebuild -or $compile -or $test -or $doc)) {
    Write-Host "No flags provided. Performing default actions: clean, rebuild, and compile."
    Clean
    Rebuild
    Compile
}