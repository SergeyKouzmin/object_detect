#include <iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main() {
    cv::VideoCapture camera(CV_CAP_ANY);

    if (!camera.isOpened()) {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    cv::namedWindow("CameraVideo",CV_WINDOW_AUTOSIZE);

    while (1) {
        cv::Mat frame;

        if (!camera.read(frame)) {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        cv::imshow("CameraVideo", frame);

        if (cv::waitKey(30) == 27) {
                cout << "esc key is pressed by user" << endl;
                break;
        }
    }

    return 0;

}

