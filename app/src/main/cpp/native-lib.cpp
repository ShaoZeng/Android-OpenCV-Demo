#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C" JNIEXPORT void JNICALL
Java_com_example_opencvdemo_CppImageProcess_cppImageProcess(
        JNIEnv *env,
        jobject jobj, jint jw, jint jh, jintArray jPixArr, jint jld){

    jint *cPixArr = env->GetIntArrayElements(jPixArr, JNI_FALSE);
    if(cPixArr==NULL){
        return;
    }
    Mat mat_img_src(jh, jw, CV_8UC4, (unsigned char*)cPixArr);

    Mat mat_img_dst;
    cvtColor(mat_img_src, mat_img_dst, CV_RGBA2RGB, 3);

    Mat mat_img_clone = mat_img_dst.clone();
    for(int i=0; i<jh; i++){
        for(int j=0; j<jw; j++){
            mat_img_clone.at<Vec3b>(i,j)[0] = saturate_cast<uchar>(mat_img_dst.at<Vec3b>(i,j)[0]+jld);
            mat_img_clone.at<Vec3b>(i,j)[1] = saturate_cast<uchar>(mat_img_dst.at<Vec3b>(i,j)[1]+jld);
            mat_img_clone.at<Vec3b>(i,j)[2] = saturate_cast<uchar>(mat_img_dst.at<Vec3b>(i,j)[2]+jld);

        }
    }
    cvtColor(mat_img_clone, mat_img_src, CV_RGB2RGBA, 4);

    env->ReleaseIntArrayElements(jPixArr, cPixArr, 0);
}
