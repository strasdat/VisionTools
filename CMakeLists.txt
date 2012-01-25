SET(PROJECT_NAME VisionTools)

PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_VERBOSE_MAKEFILE ON)

IF( NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE Release )
ENDIF()

IF (CMAKE_COMPILER_IS_GNUCXX )
   SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
   SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -g ")

  ADD_DEFINITIONS("-Wall -Werror -Wno-unused-variable
                   -Wno-unused-but-set-variable -Wno-unknown-pragmas ")
ENDIF()


SET (INCLUDE_DIRS "../eigen3.1/"
                  "../opencv2/include/opencv"
                  "../opencv2/include/"
                  "../opencv2/modules/core/include"
                  "../opencv2/modules/imgproc/include"
                  "../opencv2/modules/video/include"
                  "../opencv2/modules/features2d/include"
                  "../opencv2/modules/flann/include"
                  "../opencv2/modules/objdetect/include"
                  "../opencv2/modules/calib3d/include"
                  "../opencv2/modules/ml/include"
                  "../opencv2/modules/highgui/include"
                  "../opencv2/modules/legacy/include"
                  "../opencv2/modules/contrib/include"
                  "../Pangolin/"
                  "../Pangolin/svs_build"
                  "../Sophus/")

LIST(APPEND CMAKE_LIBRARY_PATH ../opencv2/svs_build/lib/
                               ../Pangolin/svs_build/pangolin)

SET (LIB_NAMES GL pangolin glut
               opencv_core opencv_features2d opencv_flann opencv_gpu
               opencv_highgui opencv_imgproc opencv_calib3d)

FOREACH(lib ${LIB_NAMES})
  FIND_LIBRARY(LIB_${lib} ${lib})
  IF (LIB_${lib})
    MESSAGE(STATUS "found library '${lib}': ${LIB_${lib}}")
  ELSE (LIB_${lib})
    MESSAGE(FATAL_ERROR "cannot find library '${lib}' - this will not work ...")
  ENDIF (LIB_${lib})
  LIST(APPEND LIBS ${LIB_${lib}})
ENDFOREACH(lib)

SET (CLASSES  draw2d
              draw3d
              sample
              performance_monitor
              linear_camera)

SET (SOURCE_DIR "visiontools")

SET (SOURCES ${SOURCE_DIR}/gl_data.h
             ${SOURCE_DIR}/abstract_camera.h
             ${SOURCE_DIR}/accessor_macros.h
             ${SOURCE_DIR}/ringbuffer.h
             ${SOURCE_DIR}/stopwatch.h)

FOREACH(class ${CLASSES})
  LIST(APPEND SOURCES ${SOURCE_DIR}/${class}.cpp ${SOURCE_DIR}/${class}.h)
ENDFOREACH(class)

LINK_LIBRARIES (${PROJECT_NAME} ${LIBS})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCES})


