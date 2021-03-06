# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE -pie -DLUA_DL_DLOPEN -DLUA_USE_C89 -DLUA_COMPAT_5_1 -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wl,--exclude-libs,ALL")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS D__DEBUG__")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu99 -Wno-pmf-conversions -fno-rtti -fno-exceptions -Dtypeof=decltype")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -flto=3 -fvisibility=hidden")
SET(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -Wl,--exclude-libs,ALL")

SET(CMAKE_ANDROID_STL_TYPE c++_static)


include_directories(src/main/jni/lua)
include_directories(src/main/jni/android)

add_library( # Sets the name of the library.
             lua

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             src/main/jni/lua/lapi.c
             src/main/jni/lua/lauxlib.c
             src/main/jni/lua/lbaselib.c
             src/main/jni/lua/lbitlib.c
             src/main/jni/lua/lcode.c
             src/main/jni/lua/lcorolib.c
             src/main/jni/lua/lctype.c
             src/main/jni/lua/ldblib.c
             src/main/jni/lua/ldebug.c
             src/main/jni/lua/ldo.c
             src/main/jni/lua/ldump.c
             src/main/jni/lua/lfunc.c
             src/main/jni/lua/lgc.c
             src/main/jni/lua/linit.c
             src/main/jni/lua/liolib.c
             src/main/jni/lua/llex.c
             src/main/jni/lua/lmathlib.c
             src/main/jni/lua/lmem.c
             src/main/jni/lua/loadlib.c
             src/main/jni/lua/lobject.c
             src/main/jni/lua/lopcodes.c
             src/main/jni/lua/loslib.c
             src/main/jni/lua/lparser.c
             src/main/jni/lua/lstate.c
             src/main/jni/lua/lstring.c
             src/main/jni/lua/lstrlib.c
             src/main/jni/lua/ltable.c
             src/main/jni/lua/ltablib.c
             src/main/jni/lua/ltm.c
             src/main/jni/lua/lundump.c
             src/main/jni/lua/lutf8lib.c
             src/main/jni/lua/lvm.c
             src/main/jni/lua/lzio.c
        src/main/jni/android/ldroidlib.c
        src/main/jni/android/ldoinput.c
        src/main/jni/android/lshellcmd.c
        )

add_library( # Sets the name of the library.
             luajava

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/jni/luajava/luajava.c )



# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#add_definitions(-DLUA_DL_DLOPEN)
#add_definitions(-DLUA_USE_C89)
#add_definitions(-DLUA_COMPAT_5_1)
#add_definitions(-DLUA_COMPAT_5_2)
#add_definitions(-DLUA_USE_LINUX)


#find_library( # Sets the name of the path variable.
#              log-lib
#
#              # Specifies the name of the NDK library that
#              # you want CMake to locate.
#              log)

#if(${log-lib} STREQUAL "NOTFOUND")
#    set(log-lib log)
#endif()
target_link_libraries( # Specifies the target library.
                       luajava

                       # Links the target library to the log library
                       # included in the NDK.
                       lua
                       log
                      )