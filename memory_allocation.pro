QT += quick core charts quickcontrols2

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    controller.h \
    hole_model.h \
    memory_allocator.h \
    process_model.h \
    segment.h \
    segment_model.h

SOURCES += \
        controller.cpp \
        hole_model.cpp \
        main.cpp \
        memory_allocator.cpp \
        process_model.cpp \
        segment.cpp \
        segment_model.cpp \
        test.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
