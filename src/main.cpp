#include <opencv2/opencv.hpp>
#include <iostream>
#include "mouse_events.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: ./image_viewer <image_file>" << endl;
        return -1;
    }

    // Load the image
    Mat img = imread(argv[1], IMREAD_UNCHANGED);
    if (img.empty()) {
        cout << "Error: Could not open or find the image." << endl;
        return -1;
    }

    // Create a window
    namedWindow("Image Viewer", WINDOW_NORMAL);

    // Set the mouse callback for pixel value display
    setMouseCallback("Image Viewer", onMouse, &img);

    // Display the image (initially without any pixel values)
    imshow("Image Viewer", img);

    // Wait for a key press indefinitely
    waitKey(0);

    return 0;
}
