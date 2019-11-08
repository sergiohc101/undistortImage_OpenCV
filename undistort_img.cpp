// Program that takes and input image and 
// given and XML Camera Calibratrion Parameters file
// applies undistortion to the original image and displays both.
// OpenCV 3.4
// 06/Nov/2019
// Sergio Herrera

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the image file from arguments
    if(! image.data ){                             // Check for invalid input
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    //Read XML File
    string inputCalibFile = "calibParams_Set2AB.xml";  // XML Calibration file must be in same directory

    Mat cameraMatrix, distCoeff;
    FileStorage fs(inputCalibFile, FileStorage::READ);
    if (!fs.isOpened()){
        cout << "Could not open the calibration file: \"" << inputCalibFile << "\"" << endl;
            return -1;
    }
    fs["cameraMatrix"] >> cameraMatrix;
    fs["dist_coeffs"] >> distCoeff;
    fs.release(); 

    //cameraMatrix.at<double>(0,2) = 640/2;
    //cameraMatrix.at<double>(1,2) = 480/2;

    cout << "K = "<< endl << " "  << cameraMatrix << endl << endl;
    cout << "DistParams = "<< endl << " "  << distCoeff << endl << endl;


    Mat undistortedImg = image.clone();
    bitwise_not(image, undistortedImg); //INVERT IMG

    //Undistort image
    undistort( image, undistortedImg, cameraMatrix, distCoeff);

    string NAME = argv[1];
        //cout << "Name: " <<NAME <<" -- L: " << NAME.length() <<endl;
    NAME = NAME.substr(0,NAME.length()-4) + "_C.jpg";
        //cout << "Name: " <<NAME <<" -- L: " << NAME.length() <<endl;
    
    //Save undistorted image
    imwrite(NAME, undistortedImg );   // Read the image file from arguments

    /////////////////////Display both images
    // 640x480 images
    cv::Mat mat_1 = image;
    cv::Mat mat_2 = undistortedImg;

    // Create 1280x480 mat for window
    //cv::Mat Win = Mat(cv::Size(1280, 480), CV_8UC3);
    cv::Mat Win = Mat::zeros(1280, 1500, CV_8UC3);

    // Copy small images into big mat
    mat_1.copyTo(Win(Rect(  0, 0, 640, 480)));
    mat_2.copyTo(Win(Rect(640, 0, 640, 480)));

    // Display big mat
    cv::imshow("Undistorted Image", Win);

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
