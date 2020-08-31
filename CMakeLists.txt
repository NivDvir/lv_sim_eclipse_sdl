cmake_minimum_required(VERSION 3.10)
project(lvgl)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(tools /home/niv/Downloads/GIT/buildroot-toolchains/output/host/usr)
#set(tools /home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/x86_64/gcc-cross-arm/usr/libexec/arm-oe-linux-gnueabi/gcc/arm-oe-linux-gnueabi/6.4.0)
#set(tools /home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/x86_64/gcc-cross-arm/usr)

set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-cpp)
#set(CMAKE_CXX_LINK_EXECUTABLE ${tools}/bin/armeb-buildroot-linux-gnueabihf-ld)
#set(CMAKE_CXX_LINK_EXECUTABLE /home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/x86_64/binutils-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-ld)
#set(CMAKE_C_LINK_EXECUTABLE ${tools}/ld)
#set(CMAKE_C_LINK_EXECUTABLE /home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/x86_64/binutils-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-ld)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-discarded-qualifiers -Wno-implicit-function-declaration -Wno-unused-value -fPIC -O0 -g3 -fmessage-length=0 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wno-discarded-qualifiers -Wno-implicit-function-declaration -Wno-unused-value -fPIC -O0 -g3 -fmessage-length=0 -ggdb")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(/home/niv/Downloads/GIT/buildroot-toolchains/output/host/usr/arm-buildroot-linux-gnueabihf/sysroot/usr/include)
INCLUDE_DIRECTORIES(/home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/armv7ahf-neon/glibc/usr/include)
INCLUDE_DIRECTORIES(/home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/armv7ahf-neon/linux-libc-headers/usr/include)

file(GLOB_RECURSE INCLUDES "lv_drivers/*.h" "lv_examples/*.h"  "lvgl/*.h"  "./*.h" )
file(GLOB_RECURSE SOURCES  "lv_drivers/*.c" "lv_examples/*.c"  "lvgl/*.c" )

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

# find_package(SDL2 REQUIRED SDL2)
# include_directories(${SDL2_INCLUDE_DIRS})
add_executable(dvir-hello main.c mouse_cursor_icon.c ${SOURCES} ${INCLUDES})
#target_link_libraries(main PRIVATE SDL2)
target_link_libraries(dvir-hello PRIVATE -lpthread)

#add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main)


#lrwxrwxrwx 1 root root 19 אוג  8 05:46 /usr/bin/as -> x86_64-linux-gnu-as*
#
#sudo ln -s /home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/x86_64/binutils-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-as /usr/bin/as
#sudo ln -s /usr/bin/x86_64-linux-gnu-as /usr/bin/as

#lrwxrwxrwx 1 root root 19 אוג  8 05:46 /usr/bin/ld -> x86_64-linux-gnu-ld*
#
#sudo ln -s /home/niv/Desktop/YECHIEL/SC20_Linux/SDK/sc20_linux-master/poky/build/tmp-glibc/sysroots-components/x86_64/binutils-cross-arm/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-ld /usr/bin/ld
#sudo ln -s /usr/bin/x86_64-linux-gnu-ld /usr/bin/ld


#lrwxrwxrwx 1 root root 19 אוג  8 05:46 /usr/bin/ar -> x86_64-linux-gnu-ar
#
#
 