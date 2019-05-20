ios{
    CXX_MODULE=qml
    QMAKE_MOC_OPTIONS += -Muri=QmlSql
    CONFIG += static
}

TEMPLATE = lib
TARGET = QmlSql
QT += qml quick sql network
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = QmlSql

# Input
SOURCES += \
    $$PWD/plugin.cpp \
    $$PWD/qmlsqldatabase.cpp \
    $$PWD/qqmlsqlquery.cpp \
    $$PWD/qmlsqlquerymodel.cpp \
    $$PWD/qmlsqlcreatedatabase.cpp \
    qmlsqlconnectionparameters.cpp

HEADERS += \
    $$PWD/plugin.h \
    $$PWD/qmlsqldatabase.h \
    $$PWD/qqmlsqlquery.h \
    $$PWD/qmlsqlquerymodel.h \
    $$PWD/qmlsqlcreatedatabase.h \
    qmlsqlconnectionparameters.h


DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir
