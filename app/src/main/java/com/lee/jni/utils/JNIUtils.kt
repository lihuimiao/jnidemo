package com.lee.jni.utils

import com.lee.jni.Person

class JNIUtils {
    
    external fun calculate(a : Int, b : Int):Int
    external fun createPerson(name : String, age : Int):Person
    external fun testInvokeJava();
    fun showMessageFromJNI(msg :String) {
        println("LEE-> msg : ${msg}")
    }
    
}