#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

double scaleFactor = 1.0;

// Mouse callback function to show pixel value and coordinates
void onMouse(int event, int x, int y, int, void* userdata) {
    Mat* img = reinterpret_cast<Mat*>(userdata);

    // If the mouse moves, display pixel coordinates and values
    if (event == EVENT_MOUSEMOVE) {
        // Create a new image with extra space at the bottom for the text
        Mat displayImg(Size(img->cols, img->rows + 50), img->type());

        // Copy the original image into the new image (at the top)
        img->copyTo(displayImg(Rect(0, 0, img->cols, img->rows)));

        // Get pixel value at the current (x, y) position
        Vec3b pixel = img->at<Vec3b>(y, x);

        // Prepare the text for pixel location and value
        string text = "X: " + to_string(x) + " Y: " + to_string(y) +
                      " | B: " + to_string((int)pixel[0]) +
                      " G: " + to_string((int)pixel[1]) +
                      " R: " + to_string((int)pixel[2]);

        // Set font parameters
        int fontFace = FONT_HERSHEY_SIMPLEX;
        double fontScale = 1.5;  // Larger font size for readability
        int thickness = 2;
        int baseline = 0;

        // Calculate the size of the text
        Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        baseline += thickness;

        // Set the position for the text (at the bottom of the image)
        Point textOrg(10, img->rows + textSize.height + 10);

        // Draw a white rectangle background for the text at the bottom
        rectangle(displayImg, Point(0, img->rows), Point(displayImg.cols, displayImg.rows), Scalar(255, 255, 255), FILLED);

        // Draw the text in blue color
        putText(displayImg, text, textOrg, fontFace, fontScale, Scalar(255, 0, 0), thickness);

        // Display the modified image with text
        imshow("Image Viewer", displayImg);
    }
}
