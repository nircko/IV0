#import <Cocoa/Cocoa.h> // Import the Cocoa framework

@interface ViewController : NSViewController

// Outlets for UI components
@property (weak) IBOutlet NSImageView *imageView;    // For displaying the image
@property (weak) IBOutlet NSView *bottomBar;         // The bottom bar view
@property (weak) IBOutlet NSTextField *pixelInfoLabel; // Label to display pixel data

// Action for opening the image dialog
- (IBAction)openImage:(id)sender;

@end
