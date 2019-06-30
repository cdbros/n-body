#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "sim_view.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  // set OpenGL version to 4.1
  QSurfaceFormat glFormat;
  glFormat.setVersion(4, 1);
  glFormat.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(glFormat);

  QGuiApplication app(argc, argv);

  qmlRegisterType<SimView>("NBody", 1, 0, "SimView");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return QCoreApplication::exec();
}
