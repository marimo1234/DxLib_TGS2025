#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    unsigned int Cr;

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    Cr = GetColor(0, 0, 255);
    int red, blue, green;

    for (int x = 0; x < 640; x += 20) {
        for (int y = 0; y < 480; y += 20) {
            red = GetRand(255);
            blue = GetRand(255);
            green = GetRand(0);
            DrawBoxAA(x, y, x + 18, y + 18, GetColor(red, green, blue), TRUE);

        }
    }


    WaitKey();

    DxLib_End();

    return 0;
}