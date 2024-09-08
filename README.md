# ImageViewer (Objective-C)

This macOS application allows users to open an image and display it in a window. The app shows the current cursor position and pixel color values (RGB) in a bottom bar when hovering over the image.

## Features

- **Open Image Dialog**: Users can select an image using an open file dialog.
- **Image Display**: The selected image is displayed in the main window.
- **Pixel Information**: The bottom bar shows the current mouse position and the RGB color values of the pixel under the cursor.

## Code Explanation

### `openImage:`

- **Purpose**: Opens a file dialog box for selecting an image. When an image is selected, it is displayed in the `NSImageView`.
- **Details**: 
  - The file dialog is created using `NSOpenPanel`.
  - The selected image is loaded into an `NSImageView`.
  - The bitmap representation (`NSBitmapImageRep`) of the image is extracted for pixel-level access.

### `mouseMoved:`

- **Purpose**: Tracks the mouse movement over the `NSImageView` and retrieves the pixel location and color data.
- **Details**: 
  - The method converts the mouse location to the image coordinates.
  - The RGB values of the pixel under the cursor are extracted from the bitmap.
  - The bottom bar is updated with the pixel's coordinates and RGB values.

### `viewDidAppear`

- **Purpose**: Enables mouse tracking for the window.
- **Details**: 
  - This method ensures that the app captures mouse movement events so the pixel data can be updated as the cursor moves over the image.

## Requirements

- macOS
- Xcode

## How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/nircko/IV0.git
   cd ImageViewer
