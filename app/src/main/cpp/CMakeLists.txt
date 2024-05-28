# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.


# 指定需要的 CMake 最低版本为 3.22.1
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).


# 指定项目名称为 "jni"
project("jni")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.

# 添加一个名为 "jni" 的共享库，并将 "native-lib.cpp" 源文件添加到库中
# 这里使用 SHARED 标志表示这是一个共享库（动态链接库）
#创建一个静态或者动态库，并提供其关联的源文件路径，开发者可以定义多个库，CMake会自动去构建它们。Gradle可以自动将它们打包进APK中。
#第一个参数——native-lib：是库的名称
#第二个参数——SHARED：是库的类别，是动态的还是静态的
#第三个参数——src/main/cpp/native-lib.cpp：是库的源文件的路径

add_library(${CMAKE_PROJECT_NAME}
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        JNIUtils.cpp
        native-lib.cpp)

# 查找名为 "log" 的库，并将其路径保存在变量 log-lib 中
# 这是为了在后面的步骤中将这个库链接到目标库
#find_library：找到一个预编译的库，并作为一个变量保存起来。由于CMake在搜索库路径的时候会包含系统库，
#并且CMake会检查它自己之前编译的库的名字，所以开发者需要保证开发者自行添加的库的名字的独特性。

#第一个参数——log-lib：设置路径变量的名称
#第一个参数—— log：指定NDK库的名子，这样CMake就可以找到这个库
find_library(
        log-lib
        log
)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.

# 将目标库 "myscorelib" 与 log-lib 变量中的库链接起来。
# 这意味着在编译和链接过程中，将使用 "log" 库提供的功能和符号
#target_link_libraries：指定CMake链接到目标库。开发者可以链接多个库，比如开发者可以在此定义库的构建脚本，并且预编译第三方库或者系统库。
#第一个参数——native-lib：指定的目标库
#第一个参数——${log-lib}：将目标库链接到NDK中的日志库
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        log)