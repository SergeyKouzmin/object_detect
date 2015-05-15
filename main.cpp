#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

int main() {
    cv::VideoCapture camera(CV_CAP_ANY);

    if (!camera.isOpened()) {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    cv::namedWindow("CameraVideo",CV_WINDOW_AUTOSIZE);

   /* int i = 0;
    while (i < 100) {
        cv::Mat frame;

        if (!camera.read(frame)) {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        cv::imshow("CameraVideo", frame);
        std::stringstream fileName;
        fileName << "/home/sergey/Programs/projects/object_detect/object_detect/images/" << i << ".jpg";
        cv::imwrite(fileName.str(), frame);

        i++;
    }*/

    /*cv::Mat image = cv::imread("/home/sergey/Programs/projects/object_detect/object_detect/images/24.jpg");
    cv::Mat image_gray;
    cv:cvtColor( image, image_gray, CV_BGR2GRAY );
    cv::threshold(image_gray, image_gray, 115, 255, CV_THRESH_BINARY);*/

    cv::Mat canny_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Rect> boundRect( contours.size() );

    for (int i = 24; i < 100; i++) {
        std::stringstream fileName;
        fileName << "/home/sergey/Programs/projects/object_detect/object_detect/images/" << i << ".jpg";

        cv::Mat image = cv::imread(fileName.str());
        cv::Mat image_gray;

        cv:cvtColor( image, image_gray, CV_BGR2GRAY );
        cv::threshold(image_gray, image_gray, 115, 255, CV_THRESH_BINARY);

        cv::Canny( image_gray, canny_output, 30, 60, 3 );
        /// Find contours
        cv::findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );


        std::vector<std::vector<cv::Point> > contours_poly(contours.size());

        /*for( int i = 0; i < contours.size(); i++ ) {
        cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = cv::boundingRect( cv::Mat(contours_poly[i]) );
        }*/

        cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ ) {
            cv::Scalar color = cv::Scalar( 255, 0, 0);
            cv::Rect boundRect = cv::boundingRect( cv::Mat(contours[i]) );
            //cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
            //cv::rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
            if (boundRect.area() > 4000) {
                cv::rectangle(drawing, boundRect, color);
            }
        }

        std::stringstream saveFrame;
        saveFrame << "/home/sergey/Programs/projects/object_detect/object_detect/image_gray/" << i << ".jpg";

        cv::imwrite(saveFrame.str(), drawing);
    }

    return 0;

}

