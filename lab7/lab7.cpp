//
// Created by Cukier on 12/7/2022.
//

#include "lab7.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    using namespace cv;
    VideoCapture vc(0);
    if (!vc.isOpened() ) return 1;
    cv::Mat frame;
    cv::Mat myFrame;
    cv::namedWindow("Window", WINDOW_AUTOSIZE); // Create a window for display.
    int i = 0;
    while (waitKey(10) != 27) {
        vc >> frame;
        std::cout << "frame info: " << frame.rows << " " << frame.cols << std::endl;
        cv::flip(frame, myFrame, 1);
        cv::imshow("Frame", myFrame);

    }
    return 0;
}
