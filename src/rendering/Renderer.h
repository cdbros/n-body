#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <memory>

class Renderer : public QObject, protected QOpenGLFunctions_4_1_Core {
    Q_OBJECT

  public:
    explicit Renderer(QOpenGLWidget *openGLView);

    void initialize();
    void render();
    inline void resize(int width, int height) noexcept { m_viewportSize = QSize(width, height); }

  public slots:
    void renderReady(const GLfloat *objCoords, std::size_t numObjs);

  private:
    QOpenGLWidget *m_openGLView;
    QSize m_viewportSize{};
    std::unique_ptr<QOpenGLShaderProgram> m_program{};

    const GLfloat *m_objCoords = nullptr;
    std::size_t m_numObjs = 0;
    GLfloat m_radius = 0.05f;
    ;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_eab;
    GLuint m_obo;
};

#endif // RENDERER_H
