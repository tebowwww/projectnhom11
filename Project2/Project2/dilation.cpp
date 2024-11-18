#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Function to perform dilation
Mat performDilation(Mat inputImage, int dilationElement, int dilationSize)
{
    Mat outputImage;
    int dilationType;

    if (dilationElement == 0)
        dilationType = MORPH_RECT;
    else if (dilationElement == 1)
        dilationType = MORPH_CROSS;
    else if (dilationElement == 2)
        dilationType = MORPH_ELLIPSE;

    // Create the structuring element for dilation
    Mat element = getStructuringElement(dilationType, Size(2 * dilationSize + 1, 2 * dilationSize + 1), Point(dilationSize, dilationSize));

    // Dilate the image using the structuring element
    dilate(inputImage, outputImage, element);

    // Return the output image
    return outputImage;
}

// Main function
int main()
{
    Mat inputImage, outputImage;

    // Set the path to the image file
    string imagePath = "E:\\projectnhom\\lena.jpg";

    // Read the input image
    inputImage = imread(imagePath);

    // Set the dilation size (you can change this value)
    int dilationSize = 5;

    // Check the validity of the input image
    if (!inputImage.data)
    {
        cout << "Invalid input image. Exiting!" << endl;
        return -1;
    }

    int dilationElement = 0;

    // Create windows to display the input and output images
    namedWindow("Input image", WINDOW_AUTOSIZE);
    namedWindow("Output image after dilation", WINDOW_AUTOSIZE);

    // Dilate the image
    outputImage = performDilation(inputImage, dilationElement, dilationSize);

    // Display the input and output images
    imshow("Input image", inputImage);
    imshow("Output image after dilation", outputImage);

    // Wait until the user hits a key on the keyboard
    waitKey(0);

    return 0;
}