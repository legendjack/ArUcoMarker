#pragma once
#ifndef __ARUCOMARKER_H__
#define __ARUCOMARKER_H__

#include <opencv.hpp>
#include <aruco.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

/* @brief ��ʾ��ά����࣬Ĭ�Ϲ��캯��ʹ�õ�DictionaryΪDICT_6X6_250
 *		ʹ��ArUcoMarker::detect(Mat img)������ͼ���еĶ�ά����м��
 *		�ṩ��һϵ�е�get��������ȡ�����
 */
class ArUcoMarker {
private:
	PREDEFINED_DICTIONARY_NAME name;
	Ptr<Dictionary> dictionary;

	int num;							// ͼ���ж�ά��ĸ���
	vector<vector<Point2f> > corners;	// ÿ����ά����ĸ��ǵ���ɵ�vector
	vector<int> ids;					// ÿ����ά����Dictionary�е�id��ɵ�vector
	vector<Vec3d> rvecs, tvecs;			// ÿ����ά�����ת������ƽ������

public:

	/* @brief Ĭ�Ϲ��캯����Ĭ�ϵ�Dictionary��DICT_6X6_250
	 */
	ArUcoMarker();
	ArUcoMarker(PREDEFINED_DICTIONARY_NAME name_);
	~ArUcoMarker();

	/* @brief ���ͼ�еĶ�ά�룬�õ�ÿ����ά����ĸ��ǵ�corners�Ͷ�Ӧ�ı��ids��
	 *		���ͼ���д��ڶ�ά�룬�򷵻�true�����򷵻�false��
	 *		Ҳ����ͨ��getMarkersNum()��ö�ά�����Ŀ���ж��Ƿ���ڶ�ά��
	 * @param img ������ͼ��
	 */
	bool detect(Mat img);

	/* @brief ����ÿ����ά�����̬���õ�ÿ����ά�����ת������ƽ������rvecs, tvecs
	 * @param markerLength ��ά��ʵ�ʵı߳�����λΪ��
	 */
	void estimatePose(float markerLength, Mat cameraMatrix, Mat distCoeffs);

	/* @brief ����ÿ����ά���λ�ã���Ҫ��ִ��estimatePose()����
	 * @param showAxis���Ƿ��ڶ�ά���ϻ�������
	 */
	void drawMarkers(Mat img, Mat cameraMatrix, Mat distCoeffs, bool showAxis = false);

	// ���ͼ���ж�ά��ĸ���
	int getMarkersNum();

	// ���ÿ����ά����ĸ��ǵ���ɵ�vector
	void getMarkersCorners(vector<vector<Point2f> >& corners_);

	// ���ÿ����ά����Dictionary�е�id��ɵ�vector
	void getMarkersIds(vector<int>& ids_);

	// ���ÿ����ά�����ת������ƽ������
	void getMarKersRvecsAndTvecs(vector<Vec3d>& rvecs_, vector<Vec3d>& tvecs_);
};

#endif