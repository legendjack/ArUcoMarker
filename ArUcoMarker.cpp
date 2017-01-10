#include "ArUcoMarker.h"

ArUcoMarker::ArUcoMarker() {
	ArUcoMarker::name = DICT_6X6_250;
	ArUcoMarker::dictionary = getPredefinedDictionary(DICT_6X6_250);
	ArUcoMarker::num = 0;
	ArUcoMarker::corners.clear();
	ArUcoMarker::ids.clear();
	ArUcoMarker::rvecs.clear();
	ArUcoMarker::tvecs.clear();
}

ArUcoMarker::ArUcoMarker(PREDEFINED_DICTIONARY_NAME name_) {
	ArUcoMarker::name = name_;
	ArUcoMarker::dictionary = getPredefinedDictionary(name_);
	ArUcoMarker::num = 0;
	ArUcoMarker::corners.clear();
	ArUcoMarker::ids.clear();
	ArUcoMarker::rvecs.clear();
	ArUcoMarker::tvecs.clear();
}

ArUcoMarker::~ArUcoMarker() {
	
}

bool ArUcoMarker::detect(Mat img) {
	detectMarkers(img, dictionary, corners, ids);
	ArUcoMarker::num = static_cast<int>(ids.size());
	if (num > 0)
		return true;
	else
		return false;
}

void ArUcoMarker::estimatePose(float markerLength, Mat cameraMatrix, Mat distCoeffs) {
	if (num > 0)
	{
		estimatePoseSingleMarkers(corners, markerLength, cameraMatrix, distCoeffs, rvecs, tvecs);
	}
	else
	{
		//cout << "No markers!" << endl;
	}
}

void ArUcoMarker::drawMarkers(Mat img, Mat cameraMatrix, Mat distCoeffs, bool showAxis) {
	if (ArUcoMarker::num > 0 && ArUcoMarker::rvecs.size() > 0)
	{
		drawDetectedMarkers(img, ArUcoMarker::corners, ArUcoMarker::ids);
		if (showAxis)
			for (int i = 0; i < num; i++)
				drawAxis(img, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], float(0.03));
	}
	else
	{
		//cout << "No markers!" << endl;
	}
}

int ArUcoMarker::getMarkersNum() {
	return ArUcoMarker::num;
}

void ArUcoMarker::getMarkersCorners(vector<vector<Point2f> >& corners_) {
	corners_ = ArUcoMarker::corners;
}

void ArUcoMarker::getMarkersIds(vector<int>& ids_) {
	ids_ = ArUcoMarker::ids;
}

void ArUcoMarker::getMarKersRvecsAndTvecs(vector<Vec3d>& rvecs_, vector<Vec3d>& tvecs_) {
	rvecs_ = ArUcoMarker::rvecs;
	tvecs_ = ArUcoMarker::tvecs;
}
