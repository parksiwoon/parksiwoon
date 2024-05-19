#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

// 채널별 비트 축소 함수
int reduce_channel_bits(int value, int original_bits, int new_bits) {
    // 기존 비트 수에 따라 비트 마스크 생성
    int max_val = (1 << original_bits) - 1;  // 기존 비트 마스크
    int new_max_val = (1 << new_bits) - 1;    // 축소된 비트 마스크

    // 비트를 축소하고 확장하여 결과 비트 복원
    int reduced = (value * new_max_val) / max_val;
    int expanded = (reduced * max_val) / new_max_val;
    return expanded;
}

int main(int argc, char** argv) {
    // RGBA 이미지 로드
    Mat image = imread("C:\\Users\\parks\\Downloads\\2024S_MA_image_rgba.png", IMREAD_UNCHANGED);
    if (image.empty()) {
        printf("이미지를 읽을 수 없습니다.\n");
        return -1;
    }

    // 새로운 이미지를 저장할 배열 생성
    Mat reduced_image(image.rows, image.cols, CV_8UC3);

    // 비트 축소
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            Vec4b pixel = image.at<Vec4b>(y, x);
            int r = pixel[0];
            int g = pixel[1];
            int b = pixel[2];
            // R, G, B 채널을 축소 및 확장
            int r_reduced = reduce_channel_bits(r, 8, 3);  // 3비트로 축소
            int g_reduced = reduce_channel_bits(g, 8, 3);  // 3비트로 축소
            int b_reduced = reduce_channel_bits(b, 8, 2);  // 2비트로 축소

            reduced_image.at<Vec3b>(y, x) = Vec3b(r_reduced, g_reduced, b_reduced);
        }
    }

    // 결과 이미지 저장
    imwrite("C:\\Users\\parks\\Downloads\\2024S_MA_image_rgba_8bit.png", reduced_image);

    printf("이미지 변환이 완료되었습니다.\n");

    return 0;
}
