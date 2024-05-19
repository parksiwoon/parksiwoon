#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// RGBA 픽셀 구조체 정의
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} PixelRGBA;

// 비트 축소 함수 정의
uint8_t reduce_channel_bits(uint8_t value, int original_bits, int new_bits) {
    // 기존 비트 수에 따라 비트 마스크 생성
    uint8_t max_val = (1 << original_bits) - 1;  // 기존 비트 마스크
    uint8_t new_max_val = (1 << new_bits) - 1;   // 축소된 비트 마스크

    // 비트를 축소하고 확장하여 결과 비트 복원
    uint16_t reduced = (uint16_t)value * new_max_val / max_val;
    uint16_t expanded = (uint16_t)reduced * max_val / new_max_val;
    return (uint8_t)expanded;
}

// 이미지 크기
#define IMAGE_WIDTH  100
#define IMAGE_HEIGHT 100

int main() {
    // RGBA 이미지 데이터
    PixelRGBA rgba_image[IMAGE_WIDTH][IMAGE_HEIGHT] = { 0 };

    // PNG 파일 경로
    const char* image_path = "C:\\Users\\parks\\Downloads\\2024S_MA_image_rgba.png";

    // 이미지 파일 읽기 및 RGBA 이미지로 변환 (이 부분은 파일 읽기 및 RGBA로 변환하는 코드로 대체되어야 합니다)

    // 비트 축소 및 이미지 변환
    for (int x = 0; x < IMAGE_WIDTH; x++) {
        for (int y = 0; y < IMAGE_HEIGHT; y++) {
            // 이미지 픽셀 RGBA 값 읽기
            uint8_t r = rgba_image[x][y].r;
            uint8_t g = rgba_image[x][y].g;
            uint8_t b = rgba_image[x][y].b;
            uint8_t a = rgba_image[x][y].a;

            // R, G, B 채널을 축소 및 확장
            uint8_t r_reduced = reduce_channel_bits(r, 8, 3);  // 3비트로 축소
            uint8_t g_reduced = reduce_channel_bits(g, 8, 3);  // 3비트로 축소
            uint8_t b_reduced = reduce_channel_bits(b, 8, 2);  // 2비트로 축소

            // 새로운 RGB 값을 계산
            uint8_t rgb_reduced = (r_reduced << 5) | (g_reduced << 2) | b_reduced;  // 각 비트를 적절한 위치로 이동

            // 이미지에 새로운 값 할당
            rgba_image[x][y].r = r_reduced;
            rgba_image[x][y].g = g_reduced;
            rgba_image[x][y].b = b_reduced;
        }
    }

    // 변환된 이미지 저장
    FILE* output_file;
    if (fopen_s(&output_file, "converted_image.bin", "wb") != 0) {
        printf("Error: Could not open output file.\n");
        return 1;
    }


    // 이미지 데이터를 파일에 쓰기
    for (int x = 0; x < IMAGE_WIDTH; x++) {
        for (int y = 0; y < IMAGE_HEIGHT; y++) {
            fwrite(&rgba_image[x][y], sizeof(PixelRGBA), 1, output_file);
        }
    }

    // 파일 닫기
    fclose(output_file);

    // 변환된 이미지 출력
    // 여기에 이미지를 출력하는 코드 추가
    // 예를 들어, 픽셀 값을 화면에 출력하는 방법은 다음과 같습니다.
    for (int y = 0; y < IMAGE_HEIGHT; y++) {
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            printf("(%d, %d, %d, %d) ", rgba_image[x][y].r, rgba_image[x][y].g, rgba_image[x][y].b, rgba_image[x][y].a);
        }
        printf("\n");
    }

    return 0;
}
