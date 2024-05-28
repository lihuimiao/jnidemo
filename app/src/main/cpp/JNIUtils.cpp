//
// Created by lee on 2024/5/28.
//
#include <jni.h>
#include <string>
#include <codecvt> // 注意：在C++17中，std::codecvt已被标记为废弃，并可能在C++20中移除
#include <locale>
#include "myLog.h"

using namespace std;

extern "C"
JNIEXPORT jobject JNICALL
Java_com_lee_jni_utils_JNIUtils_createPerson(JNIEnv *env, jobject thiz, jstring name, jint age) {
    jclass clazz = env->FindClass("com/lee/jni/Person");
    if (clazz == nullptr) {
        return nullptr;
    }
    /** 获取有参构造器*/
    jmethodID mid = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;I)V");
    if (mid == nullptr) {
        return nullptr;
    }
//    jfieldID fidName = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
//    jfieldID fidAge = env->GetFieldID(clazz, "age", "I");
//    if (fidAge == nullptr || fidName == nullptr) {
//        return nullptr;
//    }

/// 注意：我们需要获取jstring的UTF-8表示并将其转换为jstring（如果需要）
    const char *nativeName = env->GetStringUTFChars(name, 0);
    if (nativeName == NULL) {
        // 处理获取字符串的错误
        return nullptr;
    }


    env->ReleaseStringUTFChars(name, nativeName);



    /** 操作name 需要进行转换,jstring 默认是 jvm的 utf-16编码 需要转换为 utf-8 或者 utf-16
     * 所以需要 GetStringUTFChars->utf8 或者 GetStringChars->utf16 后才能进行操作
     * */
    //name = name + "你好";///编译错误
    /** utf8:*/
    const char *utfChars = env->GetStringUTFChars(name, nullptr);
    if (utfChars == nullptr) {
        return nullptr;
    }
    ///创建一个新的C++字符串，包含原始内容和"你好"
    string _name(utfChars);
    _name += "你好";
    /// 释放之前从jstring获取的UTF-8字符串
    env->ReleaseStringUTFChars(name, utfChars);
    /// 将新的C++字符串转换为jstring
    jstring jname = env->NewStringUTF(_name.c_str());

    /** todo utf16: 还没有完成,特别的麻烦,所以开发中 尽量使用 GetStringUTFChars 来把jstring转为 utf8 string,操作后string再转为 jstring*/
//    const jchar *utf16Chars = env->GetStringChars(name, nullptr);
//    if (utf16Chars == nullptr) {
//        return nullptr;
//    }
//    /// 计算UTF-16字符串的长度（不包括结尾的null字符）
//    jsize utf16Length = env->GetStringLength(name);
//    // 创建一个std::basic_string<char16_t>来存储UTF-16字符串
//    std::basic_string<char16_t> wstr(reinterpret_cast<const char16_t*>(utf16Chars), utf16Length);
//
//    // 假设你有了一个UTF-16编码的"你好"字符串（这里只是示意）
//    // 注意：在实际应用中，你需要确保这是正确的UTF-16编码
//    std::basic_string<char16_t> hello = u"你好"; // C++11及以上版本支持u""前缀的char16_t字面量
//    // 添加"你好"到wstr
//    wstr += hello;
//    // 释放JNI获取的字符串
//    env->ReleaseStringChars(name, reinterpret_cast<const jchar*>(utf16Chars));

    /** todo 'jint' is not a valid JVM type.如果是jint ,NewObject会提示错误 不知道为何??*/
    //jint _age = age + 10;
    int _age = age + 10;

    /** 编译错误, 不能直接使用 string类型的 _name这个变量作为 参数
     * Cannot pass object of non-trivial type 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char>>')
     * through variadic method; call will abort at runtime
     * 'std::string' is not a valid JVM type. */
//    jobject objPerson = env->NewObject(clazz, mid, _name, _age);
    jobject objPerson = env->NewObject(clazz, mid, jname, _age);
    if (objPerson == nullptr) {
        return nullptr;
    }
    return objPerson;
}










extern "C"
JNIEXPORT void JNICALL
Java_com_lee_jni_utils_JNIUtils_testInvokeJava(JNIEnv *env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    if (cls == nullptr) {
        return;
    }
    jmethodID mid = env->GetMethodID(cls, "showMessageFromJNI", "(Ljava/lang/String;)V");
    jstring s = env->NewStringUTF("我是来自JNI的消息.....");
    if (s == nullptr) {
        return;
    }
    env->CallVoidMethod(thiz, mid, s);
}