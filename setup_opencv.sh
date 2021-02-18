#!/bin/bash

working_directory=$PWD

sudo apt install \
  checkinstall \
  libssl-dev

### CMake
cmake_version="3.19.1"
cmake_folder="cmake-$cmake_version"
cmake_archive="$cmake_folder.tar.gz"
wget https://github.com/Kitware/CMake/releases/download/v$cmake_version/$cmake_archive
tar xfv $cmake_archive
cd $cmake_folder
./bootstrap 
make -j 18
sudo checkinstall

### Ceres
sudo apt-get install libgoogle-glog-dev libgflags-dev -y
sudo apt-get install libatlas-base-dev -y
sudo apt-get install libeigen3-dev -y
sudo apt-get install libsuitesparse-dev -y

cd $working_directory
ceres_version=ceres-solver-2.0.0
ceres_archive=$ceres_version.tar.gz
wget http://ceres-solver.org/$ceres_archive
tar xfv $ceres_archive
cd $ceres_version

mkdir build && cd build
cmake ..
cmake --build . -j 18
sudo checkinstall

### OpenCV
sudo apt install liblz-dev libtiff5 libtiff5-dev libtiff-tools libwebp6
sudo apt-get install vlc ubuntu-restricted-extras

sudo apt install liblz-dev -y
sudo apt-get install python3-dev python3-numpy python3-pip -y
sudo apt-get install libavcodec-dev libavformat-dev libavutil-dev libswscale-dev -y
sudo apt-get install libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev -y
sudo apt-get install libpng-dev -y
sudo apt-get install libjpeg-dev -y
sudo apt-get install libopenexr-dev -y
sudo apt-get install libtiff-dev -y
sudo apt-get install libwebp-dev -y
sudo apt-get install qt5-default -y

sudo apt install libavcodec-dev libavformat-dev libswscale-dev libavresample-dev -y
sudo apt install libxvidcore-dev x264 libx264-dev libfaac-dev libmp3lame-dev libtheora-dev  -y
sudo apt install libfaac-dev libmp3lame-dev libvorbis-dev -y
sudo apt-get install libgtk-3-dev -y
sudo -H pip3 install -U pip numpy

sudo apt-get install libtbb-dev -y
sudo apt-get install libprotobuf-dev protobuf-compiler -y
sudo apt-get install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen -y
sudo apt-get install libdc1394-22 libdc1394-22-dev libxine2-dev libv4l-dev v4l-utils -y
cd /usr/include/linux
sudo ln -s -f ../libv4l1-videodev.h videodev.h

cd $working_directory

sudo apt update && sudo apt install -y cmake g++ wget unzip
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
unzip opencv.zip
unzip opencv_contrib.zip
mkdir -p build && cd build
cmake \
  -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules \
  -DCMAKE_BUILD_TYPE=Release \
  -DOPENCV_ENABLE_NONFREE=ON \
  -DBUILD_opencv_python3=ON \
  -DINSTALL_TESTS=ON \
  -DINSTALL_C_EXAMPLES=ON \
  -DINSTALL_PYTHON_EXAMPLES=ON \
  -DWITH_CUDNN=ON \
  -DOPENCV_DNN_CUDA=ON \
  -DWITH_CUDA=ON \
  -DCUDA_ARCH_BIN=75 \
  -DWITH_CUBLAS=ON \
  -DENABLE_FAST_MATH=ON \
  -DCUDA_FAST_MATH=ON \
  -DWITH_OPENGL=ON \
  -DWITH_GSTREAMER=ON \
  -DOPENCV_GENERATE_PKGCONFIG=ON \
  -DWITH_TBB=ON \
  -DWITH_V4L=ON \
  -DWITH_QT=ON \
  -DWITH_OPENGL=ON \
  -DOPENCV_GENERATE_PKGCONFIG=ON \
  -DOPENCV_PC_FILE_NAME=opencv.pc \
  -DBUILD_EXAMPLES=ON \
  ../opencv-master
cmake --build . -j 18
sudo checkinstall
