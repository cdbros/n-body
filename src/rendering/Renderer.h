#pragma once

#include <QObject>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <engine/Engine.h>
#include <memory>

class Renderer : public QObject, protected QOpenGLFunctions_4_1_Core {
    Q_OBJECT

  public:
    explicit Renderer(QOpenGLWidget *openGLView);

    void initialize();
    void render();
    inline void resize(int width, int height) noexcept {}

  public slots:
    void updateParams(RendererInterface params);
    void renderReady();

  private:
    QOpenGLWidget *m_openGLView;
    std::unique_ptr<QOpenGLShaderProgram> m_program{};

    RendererInterface m_engineParams{};

    GLfloat m_radius = 0.02f;
    GLfloat m_zoom = 1.0f;
    GLfloat m_camX = 0.0f;
    GLfloat m_camY = 0.0f;

    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_eab{};
    GLuint m_obo{};
    GLuint m_rbo{};
};
