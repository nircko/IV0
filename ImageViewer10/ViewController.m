#import "ViewController.h"

@implementation ViewController {
    NSBitmapImageRep *bitmap; // Bitmap representation of the image for pixel-level access
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Set the background color for the bottom bar
    self.bottomBar.wantsLayer = YES;
    self.bottomBar.layer.backgroundColor = [[NSColor whiteColor] CGColor];
    self.pixelInfoLabel.stringValue = @"Select an image to start"; // Initial message
    self.pixelInfoLabel.textColor = [NSColor blackColor];
}

// Action triggered when the user clicks 'Open Image'
- (IBAction)openImage:(id)sender {
    // Open file dialog for selecting an image
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    openPanel.canChooseFiles = YES;
    openPanel.allowedFileTypes = @[@"png", @"jpg", @"jpeg", @"tiff", @"bmp"];
    
    // If user selects a file and clicks OK
    if ([openPanel runModal] == NSModalResponseOK) {
        NSURL *imageURL = [openPanel URL];
        
        // Load the selected image and set it in the NSImageView
        NSImage *image = [[NSImage alloc] initWithContentsOfURL:imageURL];
        [self.imageView setImage:image];
        
        // Get bitmap representation of the image
        bitmap = (NSBitmapImageRep *)[[image representations] firstObject];
        
        // Clear the bottom bar info
        self.pixelInfoLabel.stringValue = @"Move cursor over the image to view pixel data";
    }
}

// Tracks mouse movements over the image view to get pixel data
- (void)mouseMoved:(NSEvent *)event {
    // Get the location of the mouse in the window
    NSPoint locationInWindow = [event locationInWindow];
    NSPoint locationInImageView = [self.imageView convertPoint:locationInWindow fromView:nil];
    
    int x = (int)locationInImageView.x;
    int y = (int)locationInImageView.y;
    
    // Check if the coordinates are within the image bounds
    if (bitmap && x >= 0 && x < [bitmap pixelsWide] && y >= 0 && y < [bitmap pixelsHigh]) {
        NSColor *color = [bitmap colorAtX:x y:[bitmap pixelsHigh] - y - 1];
        
        int r = (int)(color.redComponent * 255);
        int g = (int)(color.greenComponent * 255);
        int b = (int)(color.blueComponent * 255);
        
        // Update the pixel info label with the cursor's pixel location and RGB values
        self.pixelInfoLabel.stringValue = [NSString stringWithFormat:@"X: %d, Y: %d | R: %d, G: %d, B: %d", x, y, r, g, b];
        self.pixelInfoLabel.textColor = [NSColor blackColor];
    } else {
        // Out of bounds
        self.pixelInfoLabel.stringValue = @"Out of bounds";
    }
}

// Enable mouse tracking when the view appears
- (void)viewDidAppear {
    [super viewDidAppear];
    [self.view.window setAcceptsMouseMovedEvents:YES];
}

@end
