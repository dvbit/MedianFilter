#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

void medianFilter(cv::Mat*, cv::Mat*, int);
bool inBounds(int, int, int, int);
int median(uchar*, int);
void insertionSort(uchar*, int);

int main() {
	cv::Mat original = cv::imread("resources\\lena.png", cv::IMREAD_GRAYSCALE);

	cv::Mat medianImage(original.rows, original.cols, original.type());
	medianFilter(&original, &medianImage, 5);

	cv::imshow("Original Image", original);
	cv::imshow("Median Image", medianImage);

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}

void medianFilter(cv::Mat* src, cv::Mat* dst, int kernelSize) {
	uchar* values = new uchar[kernelSize*kernelSize];
	for (int r = 0; r < src->rows; r++) {
		for (int c = 0; c < src->cols; c++) {
			int halfKernelSize = kernelSize / 2;
			for (int i = -halfKernelSize, index = 0; i <= halfKernelSize; i++) {
				for (int j = -halfKernelSize; j <= halfKernelSize; j++, index++) {
					if (!inBounds(r + i, c + j, src->rows, src->cols)) {
						values[index] = 0;
					}
					else {
						values[index] = src->at<uchar>(r + i, c + j);
					}
				}
			}
			dst->at<uchar>(r, c) = median(values, kernelSize*kernelSize);
		}
	}
	delete[] values;
}

bool inBounds(int r, int c, int rows, int cols) {
	return (r >= 0 && r < rows) && (c >= 0 && c < cols);
}

void printArray(uchar* values, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << static_cast<int>(values[i]) << " ";
	}
	std::cout << std::endl;
}

// Could use median of medians but this is good enough for now
int median(uchar* values, int size) {
	insertionSort(values, size);
	return values[size / 2];
}

void insertionSort(uchar* values, int size) {
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j != 0 && values[j - 1] > values[j]) {
			uchar temp = values[j];
			values[j] = values[j - 1];
			values[j - 1] = temp;
			j--;
		}
	}
}

