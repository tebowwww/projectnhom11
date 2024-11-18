#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Function to perform morphological opening
Mat performOpening(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage;
    int morphologyType;

    if (morphologyElement == 0)
        morphologyType = MORPH_RECT;

    else if (morphologyElement == 1)
        morphologyType = MORPH_CROSS;

    else if (morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(morphologyType, Size(2 * morphologySize + 1, 2 * morphologySize + 1), Point(morphologySize, morphologySize));
    erode(inputImage, tempImage, element);
    dilate(tempImage, outputImage, element);
    return outputImage;
}

// Function to perform morphological closing
Mat performClosing(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage;
    int morphologyType;

    if (morphologyElement == 0)
        morphologyType = MORPH_RECT;

    else if (morphologyElement == 1)
        morphologyType = MORPH_CROSS;

    else if (morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(morphologyType, Size(2 * morphologySize + 1, 2 * morphologySize + 1), Point(morphologySize, morphologySize));
    dilate(inputImage, tempImage, element);
    erode(tempImage, outputImage, element);
    return outputImage;
}

// Function to perform morphological gradient
Mat performMorphologicalGradient(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage, tempImage1, tempImage2;
    int morphologyType;

    if (morphologyElement == 0)
        morphologyType = MORPH_RECT;

    else if (morphologyElement == 1)
        morphologyType = MORPH_CROSS;

    else if (morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(morphologyType, Size(2 * morphologySize + 1, 2 * morphologySize + 1), Point(morphologySize, morphologySize));
    dilate(inputImage, tempImage1, element);
    erode(inputImage, tempImage2, element);
    return tempImage1 - tempImage2;
}

// Function to perform top hat operation
Mat performTopHat(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage;
    int morphologyType;

    if (morphologyElement == 0)
        morphologyType = MORPH_RECT;

    else if (morphologyElement == 1)
        morphologyType = MORPH_CROSS;

    else if (morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(morphologyType, Size(2 * morphologySize + 1, 2 * morphologySize + 1), Point(morphologySize, morphologySize));
    outputImage = inputImage - performOpening(inputImage, morphologyElement, morphologySize);
    return outputImage;
}

// Function to perform black hat operation
Mat performBlackHat(Mat inputImage, int morphologyElement, int morphologySize)
{
    Mat outputImage;
    int morphologyType;

    if (morphologyElement == 0)
        morphologyType = MORPH_RECT;

    else if (morphologyElement == 1)
        morphologyType = MORPH_CROSS;

    else if (morphologyElement == 2)
        morphologyType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(morphologyType, Size(2 * morphologySize + 1, 2 * morphologySize + 1), Point(morphologySize, morphologySize));
    outputImage = performClosing(inputImage, morphologyElement, morphologySize) - inputImage;
    return outputImage;
}

int main()
{
    Mat inputImage, openingOutputImage, closingOutputImage, gradientOutputImage, tophatOutputImage, blackhatOutputImage;

    // Read the input image directly from the specified path
    string imagePath = "E:\\projectnhom\\lena.jpg"; // Replace with your image path
    inputImage = imread(imagePath);

    if (!inputImage.data)
    {
        cout << "Invalid input image. Exiting!" << endl;
        return -1;
    }

    int morphologySize = 5; // Adjust the morphology size as needed
    int morphologyElement = 0;

    // Create windows to display the input and output images
    namedWindow("Input image", WINDOW_AUTOSIZE);
    namedWindow("Output image after opening", WINDOW_AUTOSIZE);
    namedWindow("Output image after closing", WINDOW_AUTOSIZE);
    namedWindow("Output image after morphological gradient", WINDOW_AUTOSIZE);
    namedWindow("Output image after top hat", WINDOW_AUTOSIZE);
    namedWindow("Output image after black hat", WINDOW_AUTOSIZE);

    // Apply morphological operations
    openingOutputImage = performOpening(inputImage, morphologyElement, morphologySize);
    closingOutputImage = performClosing(inputImage, morphologyElement, morphologySize);
    gradientOutputImage = performMorphologicalGradient(inputImage, morphologyElement, morphologySize);
    tophatOutputImage = performTopHat(inputImage, morphologyElement, morphologySize);
    blackhatOutputImage = performBlackHat(inputImage, morphologyElement, morphologySize);

    // Display the output images
    imshow("Input image", inputImage);
    imshow("Output image after opening", openingOutputImage);
    imshow("Output image after closing", closingOutputImage);
    imshow("Output image after morphological gradient", gradientOutputImage);
    imshow("Output image after top hat", tophatOutputImage);
    imshow("Output image after black hat", blackhatOutputImage);

    waitKey(0);
    return 0;
}
