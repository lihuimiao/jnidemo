#include <jni.h>
#include <string>
#include "myLog.h"

extern "C" JNIEXPORT jstring JNICALL Java_com_lee_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ 我是你大爷............";
    logi("我是 使用了 cmake jni");
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_lee_jni_utils_JNIUtils_calculate(JNIEnv *env, jobject thiz, jint a, jint b) {
    jint sum = a + b;
    return sum;
}
