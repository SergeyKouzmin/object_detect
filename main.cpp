#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include "MatchTemplate.h"

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


    std::ofstream positiveDatFile;
    positiveDatFile.open("/home/sergey/Programs/projects/object_detect/object_detect/box_positives.dat");

    std::ofstream positives_data;
    positives_data.open("/home/sergey/Programs/projects/object_detect/object_detect/positives_data.dat");

    for (int j = 0; j < 9; j++) {
        std::stringstream fileName;
        //fileName << "/home/sergey/Programs/projects/object_detect/object_detect/images/" << j << ".jpg";
        fileName << "/home/sergey/Programs/projects/object_detect/object_detect/box_images/" << j << ".jpg";

        cv::Mat image = cv::imread(fileName.str());
        cv::Mat image_gray;

        cv:cvtColor( image, image_gray, CV_BGR2GRAY );
        cv::threshold(image_gray, image_gray, 115, 255, CV_THRESH_BINARY);

        std::stringstream grayImageFileName;
        grayImageFileName << "/home/sergey/Programs/projects/object_detect/object_detect/images_gray/" << j << ".jpg";
        cv::imwrite(grayImageFileName.str(), image_gray);

        cv::Canny( image_gray, canny_output, 30, 60, 3 );
        /// Find contours
        cv::findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );


        std::vector<std::vector<cv::Point> > contours_poly(contours.size());

        /*for( int i = 0; i < contours.size(); i++ ) {
        cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
        boundRect[i] = cv::boundingRect( cv::Mat(contours_poly[i]) );
        }*/

        int count = 0;
        std::stringstream rects;
        for( int i = 0; i< contours.size(); i++ ) {
            cv::Scalar color = cv::Scalar( 255, 0, 0);
            cv::Rect boundRect = cv::boundingRect( cv::Mat(contours[i]) );
            //cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
            //cv::rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
            if (boundRect.area() > 4000) {
                rects  << boundRect.x << " " << boundRect.y << " " << boundRect.width << " " << boundRect.height << " ";
                count++;
                cv::Mat objectRect = image(boundRect);
                std::stringstream saveObject;
                saveObject << "/home/sergey/Programs/projects/object_detect/object_detect/results/" << j << i << ".jpg";
                cv::imwrite(saveObject.str(), objectRect);
                positives_data << saveObject.str() << " 1 0 0 " << boundRect.width << " "<< boundRect.height << std::endl;
                cv::rectangle(image, boundRect, color);
            }
        }

        positiveDatFile << "/home/sergey/Programs/projects/object_detect/object_detect/" << j << ".jpg " << count << " " << rects.str() << std::endl;


        std::stringstream saveFrame;
        saveFrame << "/home/sergey/Programs/projects/object_detect/object_detect/data/" << j << ".jpg";

        cv::imwrite(saveFrame.str(), image);
    }

    MatchTemplate();

    return 0;

}

