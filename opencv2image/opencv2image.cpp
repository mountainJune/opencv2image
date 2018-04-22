// opencv2image.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
void firstWay(Mat I);
void secondWay(Mat I);
void thirdWay(Mat I);
Mat thirdHuidu(Mat I);
void firstErzhi(Mat I);
int main()
{

	// ����ͼ��
	const string filename = "input.jpg";
	Mat srcImg = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (srcImg.empty())
		return -1;
	// ������ʾ����
	namedWindow("Result", WINDOW_NORMAL);
	//��ʾͼ��
	imshow("Result", srcImg);
	waitKey(0);
	//������ɫ�ռ��
	firstWay(srcImg);
	imshow("Result", srcImg);
	waitKey(0);
	//ͼ��ҶȻ�
	Mat dstImg(srcImg.size(), CV_8UC1);
	dstImg = thirdHuidu(srcImg);
	imshow("Result", dstImg);
	// ����ͼ��
	imwrite("�ҶȻ�output.jpg", dstImg);
	waitKey(0);
	//ͼ���ֵ��
	firstErzhi(dstImg);
	imwrite("��ֵ��output.jpg", dstImg);
	imshow("Result", dstImg);
	waitKey(0);
	// ������ʾ����
	waitKey(0);
	destroyWindow("Result");

	//����ɫЧ��ͼ
/*
Mat thirdImg(100,100,CV_64F);
float t = 0;
for (int i = 0; i < thirdImg.rows; i++)
{
for (int j = 0; j < thirdImg.cols; j++)
{
thirdImg.at<float>(i,j) = t;
}
t++;
}
imwrite("����output.jpg", thirdImg);
*/
	



	//���ظ�ִ����������Ԫ�ط��ʷ���100�飩A / B / C
	/*
	double t;
	t = (double)getTickCount();
	for (int i = 0; i < 100; i++)
	{
	secondWay(srcImg);//a

	}
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= 100;
	cout << "a��ʱ��" << t << endl;

	t = (double)getTickCount();
	for (int i = 0; i < 100; i++)
	{
	secondWay(srcImg);//b

	}
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= 100;
	cout << "b��ʱ��" << t << endl;

	t = (double)getTickCount();
	for (int i = 0; i < 100; i++)
	{
	thirdWay(srcImg);//c

	}
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= 100;
	cout << "c��ʱ��" << t << endl;

	

	*/
	return 0;

}

//������ɫ�ռ��3�ַ���
void firstWay(Mat I)
{
	int divideWith = 60;
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));
	//���ͼ��ĳ��λ�õ�rgbֵ
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols * channels;
	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
}
void secondWay(Mat I)
{
	int divideWith = 60;
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			*it = table[*it];
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}
}
void thirdWay(Mat I)
{
	int divideWith = 60;
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
	}
	}
}
//ͼ��ҶȻ�
Mat thirdHuidu(Mat I) {
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		
		/*for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;*/
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{//ͼ��ҶȻ�  ���ÿ�����ص��R��G,B����������ƽ��ֵ��
				//Ȼ�����ƽ��ֵ�����������ص���������
				uchar t = (_I(i, j)[0] + _I(i, j)[1] + _I(i, j)[2]) / 3;
				_I(i, j)[0] = t;
				_I(i, j)[1] = t;
				_I(i, j)[2] = t;
			}
		I = _I;
	}
	}

	return I;
}
//ͼ���ֵ��
void firstErzhi(Mat I) {
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols * channels;
	uchar* p = I.data;
	for (unsigned int i = 0; i < nRows*nCols; ++i)
	{
		if (*p > 127)
			*p = 255;
		else
			*p = 0;
		*p++;
	}
}

