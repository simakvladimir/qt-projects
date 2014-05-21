QWTPLOT3D_PATH = E:/Projects/Qt/src/depot/qt5/qtbase/qwtplot3d-0.2.7
GLU_PATH = C:/MinGW/i686-w64-mingw32

CONFIG(debug,debug|release) {
    DEBUG_SFX = d
} else {
    DEBUG_SFX =
}

INCLUDEPATH += "3rdparty\include" \
               $${QWTPLOT3D_PATH}/include \
               $${GLU_PATH}/include/GL
win32:LIBS += "3rdparty\lib\x86\OpenCL.lib" \
               -L$${QWTPLOT3D_PATH}/lib -lqwtplot$${DEBUG_SFX}3d \
               -L$${GLU_PATH}/lib -lglu32
