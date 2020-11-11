package com.example.opencvdemo;

import android.graphics.Bitmap;

public class CppImageProcess {
    public static Bitmap getBitmap(Bitmap bitmap){
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int[] pixArr = new int[width * height];
        bitmap.getPixels(pixArr, 0, width, 0, 0, width, height);

        cppImageProcess(width, height, pixArr, 60);

        Bitmap newBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        newBitmap.setPixels(pixArr, 0, width, 0, 0, width, height);

        return  newBitmap;
    }
    //定义java本地方法
    public static native void cppImageProcess(int w, int h, int[] pixArr, int ld);
}
