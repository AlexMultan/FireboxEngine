@echo off
REM ============================================================
REM  Downloads and installs the latest Vulkan SDK (Windows x64)
REM  Requires: curl (built into Windows 10/11)
REM ============================================================

setlocal enabledelayedexpansion

set "INSTALL_DIR=%~dp0..\ThirdParty\VulkanSDK"
set "TEMP_DIR=%TEMP%\VulkanSDKFetch"
set "INSTALLER=%TEMP_DIR%\VulkanSDK-Installer.exe"
set "VERSION_URL=https://vulkan.lunarg.com/sdk/latest/windows.txt"
set "LATEST_DOWNLOAD_URL=https://sdk.lunarg.com/sdk/download/latest/windows/vulkan_sdk.exe"

echo ============================================================
echo  Vulkan SDK Downloader / Installer
echo  Target: %INSTALL_DIR%
echo ============================================================

if not exist "%TEMP_DIR%" mkdir "%TEMP_DIR%"
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"

echo Checking latest Vulkan SDK version...
set "VULKAN_VERSION="
for /f "usebackq delims=" %%v in (`curl -s --ssl-no-revoke "%VERSION_URL%"`) do set "VULKAN_VERSION=%%v"

if defined VULKAN_VERSION (
    echo Latest Vulkan SDK version: %VULKAN_VERSION%
) else (
    echo Could not determine version string, continuing with "latest" alias anyway.
)

echo.
echo Downloading Vulkan SDK installer...
echo   %LATEST_DOWNLOAD_URL%
curl -L --fail --ssl-no-revoke --output "%INSTALLER%" "%LATEST_DOWNLOAD_URL%"

if not exist "%INSTALLER%" (
    echo.
    echo ERROR: Download failed. Retrying once with plain HTTP fallback flags...
    curl -L --fail -k --ssl-no-revoke --output "%INSTALLER%" "%LATEST_DOWNLOAD_URL%"
)

if not exist "%INSTALLER%" (
    echo.
    echo ERROR: Download failed. Check your internet connection and try again.
    PAUSE
)

REM --- Silent, unattended install with components ---
REM     com.lunarg.vulkan.glm   - GLM math headers
REM     com.lunarg.vulkan.volk  - Volk meta-loader
REM     com.lunarg.vulkan.vma   - Vulkan Memory Allocator
REM     com.lunarg.vulkan.debug - Debuggable shader API libraries
echo.
echo Installing Vulkan SDK to %INSTALL_DIR% ...
"%INSTALLER%" --root "%INSTALL_DIR%" --accept-licenses --default-answer --confirm-command install ^
    com.lunarg.vulkan.glm ^
    com.lunarg.vulkan.volk ^
    com.lunarg.vulkan.vma ^
    com.lunarg.vulkan.debug

if errorlevel 1 (
    echo.
    echo ERROR: Installation failed with exit code %errorlevel%.
    PAUSE
)

echo.
echo Cleaning up temporary files...
del /q "%INSTALLER%" >nul 2>&1

echo.
echo ============================================================
echo  Done. Vulkan SDK installed to:
echo    %INSTALL_DIR%
echo.
echo  Note: This script installs into a project-local folder
echo  rather than the default C:\VulkanSDK, so it will NOT set
echo  the system VULKAN_SDK / PATH environment variables. Point
echo  your build system (CMake, project files, etc.) at:
echo    %INSTALL_DIR%\Include
echo    %INSTALL_DIR%\Lib
echo    %INSTALL_DIR%\Bin
echo  manually, or run the installer without --root if you want
echo  the standard system-wide setup instead.
echo ============================================================

endlocal