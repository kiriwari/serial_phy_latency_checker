#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ftd2xx.h"
#include <unistd.h>
#include <sys/time.h>

#define INPUT_PIN  4  // 入力を検知するGPIOピンの番号
#define OUTPUT_PIN  0  // 出力するGPIOピンの番号

int main() {
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD bytesWritten;

    // デバイスをオープン
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("failed open device\n");
        return 1;
    }
    FT_SetBaudRate(ftHandle, FT_BAUD_921600);
    // MODEリセット
    FT_SetBitMode(ftHandle, 0xFF, FT_BITMODE_RESET);
    // BIT BANG MODEセット
    FT_SetBitMode(ftHandle, 0xFF, FT_BITMODE_ASYNC_BITBANG);
    // IOピンPULL UP
    FT_Write(ftHandle, "\xFF", 1, &bytesWritten);

    printf("start\n");
    // INPUT_PIN用マスク
    unsigned char inputMask = (0b1 << INPUT_PIN);
    unsigned char outputMask = (0b1 << INPUT_PIN);

    struct timeval startTime;
    struct timeval endTime;
    gettimeofday(&startTime, NULL);

    // 入力ピンがLowになるまで待機
    while (1) {
        char inputData;
        // すべてのピン状態読み込み
        FT_GetBitMode(ftHandle, &inputData);
        if ((inputData & inputMask) == inputMask) { // 指定した入力ピンに電圧を検知したか確認
        //if ((inputData & inputMask) == 0) { // 指定した入力ピンが電圧を検知しなくなったか確認
            gettimeofday(&endTime, NULL); // 終了時刻を記録
            break;
        }
    }


    // 測定結果を計算して表示
    double elapsedTime = (endTime.tv_sec - startTime.tv_sec) + ((endTime.tv_usec - startTime.tv_usec) / 1e6);
    printf("latency: %.6f milli second\n", elapsedTime*1e3);

    // デバイスをクローズ
    FT_Close(ftHandle);

    return 0;
}