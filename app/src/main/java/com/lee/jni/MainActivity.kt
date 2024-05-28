package com.lee.jni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.lee.jni.databinding.ActivityMainBinding
import com.lee.jni.utils.JNIUtils

class MainActivity : AppCompatActivity() {
    
    private lateinit var binding : ActivityMainBinding
    
    override fun onCreate(savedInstanceState : Bundle?) {
        super.onCreate(savedInstanceState)
        
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        
        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()
        binding.testJni.setOnClickListener {
            testJNI()
            JNI_创建Person对象()
            JNIUtils().testInvokeJava()
        }
        initPerson()
    }
    private fun JNI_创建Person对象() {
        val p = JNIUtils().createPerson("小丽",30)
        println("LEE-> p.name : ${p.name},p.age:${p.age}")
    }
    /** 测试git000000案例三等奖发拉升阶段111111阿斯蒂芬 切换到main分支*/
    
    private fun testJNI() {
        /** 调用jni方法并返回求和结果*/
        val sum = JNIUtils().calculate(100, 200)
        println("LEE-> sum :$sum")
        binding.sampleText.text = sum.toString()
    }
    
    fun initPerson() {
        val p = Person("lee",100)
        p.apply {
            name = "修改过的名称"
            age = 120
        }
        println("LEE-> p : ${p.name}")
        
    }
    
    /**
     * A native method that is implemented by the 'jni' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI() : String
    
    companion object {
        // Used to load the 'jni' library on application startup.
        init {
            System.loadLibrary("jni")
        }
    }
}