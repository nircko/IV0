#!/bin/bash

# Configuration
APP_NAME="ImageViewer"
EXECUTABLE_NAME="image_viewer"
SOURCE_DIR="$(pwd)"  # The current directory containing source code
BUILD_DIR="${SOURCE_DIR}/build"
SRC_DIR="${SOURCE_DIR}/src"
APP_DIR="${SOURCE_DIR}/${APP_NAME}.app"
MACOS_DIR="${APP_DIR}/Contents/MacOS"
RESOURCES_DIR="${APP_DIR}/Contents/Resources"
INFO_PLIST="${APP_DIR}/Contents/Info.plist"

# Ensure build directory exists
if [ ! -d "${BUILD_DIR}" ]; then
    mkdir -p "${BUILD_DIR}"
fi

# Step 1: Run CMake to generate build files
echo "Running CMake..."
cd "${BUILD_DIR}"
cmake ..

# Step 2: Compile the code
echo "Compiling the project..."
make

# Step 3: Create the .app bundle structure
echo "Creating .app bundle..."
mkdir -p "${MACOS_DIR}" "${RESOURCES_DIR}"

# Step 4: Move the compiled executable into the .app bundle
if [ -f "${BUILD_DIR}/${EXECUTABLE_NAME}" ]; then
    echo "Moving executable to .app bundle..."
    cp "${BUILD_DIR}/${EXECUTABLE_NAME}" "${MACOS_DIR}/"
    chmod +x "${MACOS_DIR}/${EXECUTABLE_NAME}"  # Ensure the executable is executable
else
    echo "Error: Executable not found!"
    exit 1
fi
# Step 5: Create the Info.plist file
echo "Creating Info.plist..."
cat <<EOL > "${INFO_PLIST}"
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleName</key>
    <string>${APP_NAME}</string>
    <key>CFBundleExecutable</key>
    <string>${EXECUTABLE_NAME}</string>
    <key>CFBundleIdentifier</key>
    <string>com.example.${APP_NAME}</string>
    <key>CFBundleVersion</key>
    <string>1.0</string>
    <key>CFBundleIconFile</key>
    <string>ivleeg.icns</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
</dict>
</plist>
EOL

# Step 6: Optionally copy an icon file (if you have an .icns file)
if [ -f "${SRC_DIR}/misc/ivleeg.icns" ]; then
    echo "Adding icon to .app bundle..."
    cp "${SRC_DIR}/misc/ivleeg.icns" "${RESOURCES_DIR}/"
fi

# Done
echo "Build and packaging completed! You can find the app in ${APP_DIR}"


