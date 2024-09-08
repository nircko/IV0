#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function to load the image with error handling
Mat loadImage(const string& imagePath) {
    Mat img = imread(imagePath, IMREAD_UNCHANGED);
    if (img.empty()) {
        cerr << "Error: Cannot load image from path: " << imagePath << endl;
    }
    return img;
}
