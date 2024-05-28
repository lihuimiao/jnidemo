//
// Created by lee on 2024/5/27.
//
#include <android/log.h>
#define LOG_TAG "LEE-> JNI->"
#define ANDROID_PLATFORM

#ifdef ANDROID_PLATFORM
#define logd(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define logi(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define logw(...) ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define loge(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))

#else
   #define LOGD(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
   #define LOGI(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
   #define LOGW(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
   #define LOGE(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
#endif

//#ifndef STUDYJNI_1_MYLOG_H
//#define STUDYJNI_1_MYLOG_H
//
//
//#endif //STUDYJNI_1_MYLOG_H
