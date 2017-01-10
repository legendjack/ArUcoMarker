#include <iostream>
#include <opencv.hpp>
#include "ArUcoMarker.h"

using namespace cv;
using namespace std;

const Mat cameraMatrix = (Mat_<double>(3, 3) << 5.415783594209042e+02, 0, 3.206666177978510e+02,
	0, 5.404611401994315e+02, 2.422876948687574e+02, 0, 0, 1);
const Mat distCoeffs = (Mat_<double>(1, 5) << -0.352052735773963, 0.104787681524661,
	-0.001162907806854, -7.652280170769810e-05, 0.0);

int main()
{
	ArUcoMarker marker;

	Mat frame;
	VideoCapture cap(1);

	while (cap.isOpened())
	{
		cap >> frame;
		if (!frame.data)
		{
			break;
		}

		marker.detect(frame);

		if (marker.getMarkersNum() > 0)
		{
			marker.estimatePose(0.05, cameraMatrix, distCoeffs);
			marker.drawMarkers(frame, cameraMatrix, distCoeffs, true);
		}

		imshow("frame", frame);
		int key = waitKey(10);
		if (key == 27)
			break;
	}

	return 0;
}