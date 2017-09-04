///////////////////////////////////////////////////////////////////////////////
// File generated by HDevelop for HALCON/C++ Version 13.0.1
/////////////////////////////////////////////////////////////////////////////
#include <halcon_all.h>
#include <opencv_all.h>
#include "halconObjectRecognition.h"

Mat m_matImg, m_matROIImg,m_matTmpImg,m_matDstImg;
VideoCapture capture;
void on_mouse(int event, int x, int y, int flags, void *ustc);//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  

int main(int argc, char *argv[])
{
#if defined(_WIN32)
	SetSystem("use_window_thread", "true");
#elif defined(__linux__)
	XInitThreads();
#endif

	halconObjectRecognition halconObjectRecognition;
	halconObjectRecognition.initialize();
	halconObjectRecognition.action();

	system("pause");
	return 0;
}


void on_mouse(int event, int x, int y, int flags, void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  
{
	static Point m_pointPreCoordinate = (-1, -1);//��ʼ����  
	static Point m_pointCurCoordinate = (-1, -1);//ʵʱ����  
	char m_charName[16];
	if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ��ʼ���꣬����ͼ���ϸõ㴦��Բ  
	{
		m_matImg.copyTo(m_matTmpImg);//��ԭʼͼƬ���Ƶ�img��  
		sprintf(m_charName, "(%d,%d)", x, y);
		m_pointPreCoordinate = Point(x, y);
		putText(m_matTmpImg, m_charName, m_pointPreCoordinate, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//�ڴ�������ʾ����  
		circle(m_matTmpImg, m_pointPreCoordinate, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ  
		imshow("img", m_matTmpImg);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�������  
	{
		m_matTmpImg.copyTo(m_matDstImg);//��img���Ƶ���ʱͼ��tmp�ϣ�������ʾʵʱ����  
		sprintf(m_charName, "(%d,%d)", x, y);
		m_pointCurCoordinate = Point(x, y);
		putText(m_matDstImg, m_charName, m_pointCurCoordinate, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));//ֻ��ʵʱ��ʾ����ƶ�������  
		imshow("img", m_matDstImg);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//�������ʱ������ƶ�������ͼ���ϻ�����  
	{
		m_matTmpImg.copyTo(m_matDstImg);
		sprintf(m_charName, "(%d,%d)", x, y);
		m_pointCurCoordinate = Point(x, y);
		putText(m_matTmpImg, m_charName, m_pointCurCoordinate, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		rectangle(m_matTmpImg, m_pointPreCoordinate, m_pointCurCoordinate, Scalar(0, 255, 0, 0), 1, 8, 0);//����ʱͼ����ʵʱ��ʾ����϶�ʱ�γɵľ���  
		imshow("img", m_matTmpImg);
	}
	else if (event == CV_EVENT_LBUTTONUP)//����ɿ�������ͼ���ϻ�����  
	{
		m_matImg.copyTo(m_matROIImg);
		sprintf(m_charName, "(%d,%d)", x, y);
		m_pointCurCoordinate = Point(x, y);
		//img.copyTo(tmp);
		//��ȡ���ΰ�Χ��ͼ�񣬲����浽dst��  
		int width = abs(m_pointPreCoordinate.x - m_pointCurCoordinate.x);
		int height = abs(m_pointPreCoordinate.y - m_pointCurCoordinate.y);
		if (width == 0 || height == 0&&width*height<20)
		{
			cout << "Failed to new Image" << endl;
			return;
		}
		putText(m_matROIImg, m_charName, m_pointCurCoordinate, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		circle(m_matROIImg, m_pointPreCoordinate, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		rectangle(m_matROIImg, m_pointPreCoordinate, m_pointCurCoordinate, Scalar(0, 255, 0, 0), 1, 8, 0);//���ݳ�ʼ��ͽ����㣬�����λ���img��  
		imshow("img", m_matROIImg);
		/*dst = org(Rect(min(cur_pt.x, pre_pt.x), min(cur_pt.y, pre_pt.y), width, height));
	    namedWindow("dst");
		imshow("dst", dst);
		waitKey(0);*/
	}
}

