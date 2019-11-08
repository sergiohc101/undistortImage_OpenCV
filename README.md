# undistortImage_OpenCV
Program that takes and input image and, given and XML Camera Calibration Parameters file, applies undistortion to the input image, saves the undistorted image and displays both.

Using OpenCV 'undistort()'.

Program compilation:
g++ undistort_img.cpp -o undistortImg `pkg-config --cflags --libs opencv`

Program execution [image name as parameter]:
./undistortImg  setCalibV/setA01.jpg

NOTE: The XML Calibration Parameters file must be in the same directory as the executable.
