#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// Variables for mouse callback
Point pt1(-1, -1), pt2(-1, -1);
bool first_click = false;
bool second_click = false;

// Function to display the distance between two points
void displayDistance(Mat &img, Point p1, Point p2) {
    double distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    string distText = "Distance: " + to_string(distance) + " px";
    putText(img, distText, Point(10, img.rows - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    line(img, p1, p2, Scalar(0, 255, 0), 2);
}

// Mouse callback function to show pixel value and coordinates
void onMouse(int event, int x, int y, int, void* userdata) {
    Mat* img = reinterpret_cast<Mat*>(userdata);
    
    // Show pixel value and coordinates when moving mouse
    if (event == EVENT_MOUSEMOVE) {
        Vec3b pixel = img->at<Vec3b>(y, x);
        Mat displayImg = img->clone();

        string text = "X: " + to_string(x) + ", Y: " + to_string(y) +
                      " | B: " + to_string((int)pixel[0]) + 
                      " G: " + to_string((int)pixel[1]) +
                      " R: " + to_string((int)pixel[2]);
        putText(displayImg, text, Point(10, img->rows - 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);

        // If two clicks for the ruler have been made, display the distance
        if (first_click && second_click) {
            displayDistance(displayImg, pt1, pt2);
        }

        imshow("Image Viewer", displayImg);
    }

    // Handle mouse clicks for distance measurement
    if (event == EVENT_LBUTTONDOWN) {
        if (!first_click) {
            pt1 = Point(x, y);
            first_click = true;
            second_click = false;
        } else if (!second_click) {
            pt2 = Point(x, y);
            second_click = true;
        }
    }
}

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

    // Check if the image is grayscale or RGB
    if (img.channels() == 1) {
        cvtColor(img, img, COLOR_GRAY2BGR);  // Convert to 3-channel for consistent display
    }

    // Create a window and set mouse callback
    namedWindow("Image Viewer", WINDOW_AUTOSIZE);
    setMouseCallback("Image Viewer", onMouse, &img);

    // Show the image
    imshow("Image Viewer", img);

    // Wait until user presses a key
    waitKey(0);
    return 0;
}

