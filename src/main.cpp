#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[]) {
    qRegisterMetaType<std::size_t>("std::size_t");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // set OpenGL version to 4.1
    QSurfaceFormat glFormat;
    glFormat.setDepthBufferSize(24);
    glFormat.setVersion(4, 1);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

    QApplication application(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}
