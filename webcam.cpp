#include "image2ascii.h"


int main()
{
	cv::Mat frame;

	cv::VideoCapture cap(0);


	if (!cap.isOpened())
	{
		std::cout << "ERROR::OPENCV Unable to Open Webcam" << std::endl;
		return -1;
	}

	std::vector<std::string> lines;
	while (true)
	{
		//if (frame.empty())
		//{
		//	std::cout << "ERROR::OPENCV Unable to Capture frame" << std::endl;
		//	break;
		//}
		cap >> frame;
		cv::imshow("Webcam", frame);

		lines = image2ascii(frame);



		if (cv::waitKey(1) == 27)
		{
			break;
		}
	}

	cap.release();
	cv::destroyAllWindows();	

	return 0;
}