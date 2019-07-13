#include "renderer.h"
#include "shaders.h"

#include <iostream>
#include <memory>
#include <cstdlib>




#define gl_check(call) \
    check_err([&]() { return call; }, __LINE__, __FILE__, __func__, #call)

static std::string gl_err_to_string(GLenum err) {
    switch (err) {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE"; case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    default:
        return "UNKNOWN_ERROR";
    }
}

static void check_err(int line, std::string file, std::string func, std::string call) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "OpenGL ERROR: " << err << " -> " << gl_err_to_string(err) << std::endl;
        std::cout << file << ":" << line << " -> " << func << std::endl;
        std::cout << call << std::endl;
        exit(-1);
    }
}

void check_err(int line, std::string file, std::string func, std::string call);

template<typename ret_t>
struct func_caller {
    template<typename func_t>
    static ret_t call(func_t f) { return f(); }
};

template<>
struct func_caller<void> {
    template<typename func_t>
    static int call(func_t f) { f(); return 0; }
};

template<typename func_t>
auto check_err(func_t func_call, int line, std::string file, std::string func, std::string call) {
    auto ret = func_caller<decltype(func_call())>::call(func_call);
    check_err(line, std::move(file), std::move(func), std::move(call));
    return ret;
}





void Renderer::setViewportSize(const QSize &size) noexcept {
    m_viewportSize = size;
}

void Renderer::setWindow(QQuickWindow *window) noexcept { m_window = window; }

void Renderer::init() {
  initializeOpenGLFunctions();

  m_program = std::make_unique<QOpenGLShaderProgram>();

  // create shaders and link
  gl_check(m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource));
  gl_check(m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource));
  gl_check(m_program->link());

  GLfloat vertices[] = {
      -0.5f, -0.5f,
      -0.5f,  0.5f,
       0.5f,  0.5f,
       0.5f, -0.5f,
  };
  GLuint indices[] = {
      0, 1, 2, 2, 3, 0,
  };
  GLfloat offsets[] = {
       0.0f,  0.0f, 0.2f,
       0.5f,  0.5f, 0.1f,
      -0.5f, -0.5f, 0.0f,
  };

  gl_check(glGenVertexArrays(1, &m_vao));
  gl_check(glGenBuffers(1, &m_vbo));
  gl_check(glGenBuffers(1, &m_eab));
  gl_check(glGenBuffers(1, &m_obo));

  gl_check(glBindVertexArray(m_vao));

  gl_check(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
  gl_check(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
  int pos_loc = gl_check(m_program->attributeLocation("pos"));
  gl_check(glVertexAttribPointer(pos_loc, 2, GL_FLOAT, GL_FALSE, 0, 0));
  gl_check(glEnableVertexAttribArray(pos_loc));

  gl_check(glBindBuffer(GL_ARRAY_BUFFER, m_obo));
  gl_check(glBufferData(GL_ARRAY_BUFFER, sizeof(offsets), offsets, GL_STATIC_DRAW));
  int offset_loc = gl_check(m_program->attributeLocation("offset"));
  gl_check(glEnableVertexAttribArray(offset_loc));
  gl_check(glVertexAttribPointer(offset_loc, 3, GL_FLOAT, GL_FALSE, 0, 0));
  gl_check(glVertexAttribDivisor(offset_loc, 1));

  gl_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eab));
  gl_check(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

  int mvp_loc = gl_check(m_program->uniformLocation("mvp"));
  QMatrix4x4 mvp;
  mvp.setToIdentity(); gl_check(m_program->bind());
  gl_check(m_program->setUniformValue("mvp", mvp));
  gl_check(m_program->release());

  gl_check(glBindBuffer(GL_ARRAY_BUFFER, 0));
  gl_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  gl_check(glBindVertexArray(0));
}

void Renderer::render() {
  if (!m_program) {
    init();
  }

  m_program->bind();

  gl_check(glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height()));
  gl_check(glScissor(0, 0, m_viewportSize.width(), m_viewportSize.height()));
  gl_check(glEnable(GL_SCISSOR_TEST));
  gl_check(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
  gl_check(glClear(GL_COLOR_BUFFER_BIT));

  gl_check(glEnable(GL_BLEND));
  gl_check(glEnable(GL_DEPTH_TEST));
  //gl_check(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE));
  gl_check(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  gl_check(glBindVertexArray(m_vao));
  gl_check(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
  gl_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eab));
  gl_check(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 3));

  m_program->release();
  m_window->resetOpenGLState();
}
