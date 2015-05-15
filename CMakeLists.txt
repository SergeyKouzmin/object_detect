project(object_detect)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

include_directories("/usr/local/include")

set(opencv_lib_dir /usr/local/lib)
set(boost_lib_dir /usr/local/lib)

add_library(opencv_highgui SHARED IMPORTED)
set_property(TARGET opencv_highgui PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_highgui.so)

add_library(opencv_objdetect SHARED IMPORTED)
set_property(TARGET opencv_objdetect PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_objdetect.so)

add_library(opencv_imgproc SHARED IMPORTED)
set_property(TARGET opencv_imgproc PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_imgproc.so)

add_library(opencv_features2d SHARED IMPORTED)
set_property(TARGET opencv_features2d PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_features2d.so)

add_library(opencv_legacy SHARED IMPORTED)
set_property(TARGET opencv_legacy PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_legacy.so)

add_library(opencv_nonfree SHARED IMPORTED)
set_property(TARGET opencv_nonfree PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_nonfree.so)

add_library(opencv_core SHARED IMPORTED)
set_property(TARGET opencv_core PROPERTY IMPORTED_LOCATION ${opencv_lib_dir}/libopencv_core.so)

add_library(boost_regex SHARED IMPORTED)
set_property(TARGET boost_regex PROPERTY IMPORTED_LOCATION ${boost_lib_dir}/libboost_regex.so)

add_library(boost_filesystem SHARED IMPORTED)
set_property(TARGET boost_filesystem PROPERTY IMPORTED_LOCATION ${boost_lib_dir}/libboost_filesystem.so)

add_library(boost_system SHARED IMPORTED)
set_property(TARGET boost_system PROPERTY IMPORTED_LOCATION ${boost_lib_dir}/libboost_system.so)


add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} opencv_objdetect opencv_imgproc opencv_core opencv_highgui opencv_legacy opencv_nonfree opencv_features2d boost_regex boost_filesystem boost_system)
