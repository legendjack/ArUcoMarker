#pragma once
#ifndef __ARUCOMARKER_H__
#define __ARUCOMARKER_H__

#include <opencv.hpp>
#include <aruco.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

/* @brief 表示二维码的类，默认构造函数使用的Dictionary为DICT_6X6_250
 *		使用ArUcoMarker::detect(Mat img)方法对图像中的二维码进行检测
 *		提供了一系列的get方法来获取检测结果
 */
class ArUcoMarker {
private:
	PREDEFINED_DICTIONARY_NAME name;
	Ptr<Dictionary> dictionary;

	int num;							// 图像中二维码的个数
	vector<vector<Point2f> > corners;	// 每个二维码的四个角点组成的vector
	vector<int> ids;					// 每个二维码在Dictionary中的id组成的vector
	vector<Vec3d> rvecs, tvecs;			// 每个二维码的旋转向量和平移向量

public:

	/* @brief 默认构造函数，默认的Dictionary是DICT_6X6_250
	 */
	ArUcoMarker();
	ArUcoMarker(PREDEFINED_DICTIONARY_NAME name_);
	~ArUcoMarker();

	/* @brief 检测图中的二维码，得到每个二维码的四个角点corners和对应的编号ids。
	 *		如果图像中存在二维码，则返回true，否则返回false。
	 *		也可以通过getMarkersNum()获得二维码的数目来判断是否存在二维码
	 * @param img 待检测的图像
	 */
	bool detect(Mat img);

	/* @brief 估计每个二维码的姿态，得到每个二维码的旋转向量和平移向量rvecs, tvecs
	 * @param markerLength 二维码实际的边长，单位为米
	 */
	void estimatePose(float markerLength, Mat cameraMatrix, Mat distCoeffs);

	/* @brief 绘制每个二维码的位置，需要先执行estimatePose()方法
	 * @param showAxis，是否在二维码上绘制轴线
	 */
	void drawMarkers(Mat img, Mat cameraMatrix, Mat distCoeffs, bool showAxis = false);

	// 获得图像中二维码的个数
	int getMarkersNum();

	// 获得每个二维码的四个角点组成的vector
	void getMarkersCorners(vector<vector<Point2f> >& corners_);

	// 获得每个二维码在Dictionary中的id组成的vector
	void getMarkersIds(vector<int>& ids_);

	// 获得每个二维码的旋转向量和平移向量
	void getMarKersRvecsAndTvecs(vector<Vec3d>& rvecs_, vector<Vec3d>& tvecs_);
};

#endif