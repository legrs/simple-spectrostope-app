#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <camera/NdkCameraMetadata.h>
#include <camera/NdkCameraMetadataTags.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraCaptureSession.h>
#include <media/NdkImage.h>
#include <media/NdkImageReader.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <jni.h>
#include <jni.h>
#include <fstream>
#include <opencv2/opencv.hpp>

#define LOG_TAG "CameraNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define WIDTH 640
#define HEIGHT 640

using namespace cv;
using namespace std;

extern "C"{
JNIEXPORT jstring JNICALL
Java_com_example_ssa_CapActivity_processRawImg(
        JNIEnv* env,
        jobject tmp,
        jobject buff,
        jint width,
        jint height,
        jint rowStride,
        jstring jfilepath){
    
    std::stringstream ss;
    if(jfilepath == nullptr){
        ss << "ぬるぽ" << endl;
        return env->NewStringUTF(ss.str().c_str());
    }
    ss << "log from c++" << std::endl;
    uint8_t* dataPtr = (uint8_t*)env->GetDirectBufferAddress(buff);
    Mat rawMat(height, width, CV_16UC1, (void*)dataPtr, rowStride);

    //Mat testMat = Mat.zeros(100,100,CV_8UC1);

    //imwrite()
    //
    // save csv
    const char* filepath = env->GetStringUTFChars(jfilepath, nullptr);
    std::fstream csvFile(filepath, std::ios::out);
    if(csvFile.is_open()){
        csvFile << "aaa\n";
        csvFile.close();
    }else{
        ss << "file is not opened" << std::endl;
    }
    env->ReleaseStringUTFChars(jfilepath, filepath);

    return env->NewStringUTF(ss.str().c_str());

}
}


