//internal includes
#include "common.h"
#include "ShaderProgram.h"

//External dependencies
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <random>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unistd.h>

static const GLsizei WIDTH = 800, HEIGHT = 600; //размеры окна

int initGL()
{
	int res = 0;
	//грузим функции opengl через glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: "   << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: "  << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: "     << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;

	//запрашиваем контекст opengl версии 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow*  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL basic sample", nullptr, nullptr);
  if (window == nullptr)
  {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
	}
	
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  if(initGL() != 0)
      return -1;
	
  //Reset any OpenGL errors which could be present for some reason
  GLenum gl_error = glGetError();
  while (gl_error != GL_NO_ERROR)
      gl_error = glGetError();

  //создание шейдерной программы из двух файлов с исходниками шейдеров
  //используется класс-обертка ShaderProgram
  std::unordered_map<GLenum, std::string> shaders;
  shaders[GL_VERTEX_SHADER]   = "vertex.glsl";
  shaders[GL_FRAGMENT_SHADER] = "fragment.glsl";
  ShaderProgram program(shaders); GL_CHECK_ERRORS;

  glfwSwapInterval(1); // force 60 frames per second
  
  //Создаем и загружаем геометрию поверхности

  //GLuint g_vertexBufferObject;
  //GLuint g_vertexArrayObject;

    glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 10.0f);
    glm::mat4 View       = glm::lookAt(
            glm::vec3(2.0f, 2.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );

  GLuint vaoID[3];
  GLuint vboID[9];


  {
      float triangle[] =
              {
              -0.1f, -0.1f, 0.0f,
              0.1f, -0.1f, 0.0f,
              0.0f, +0.1f, 0.0f
              };

      float triangeСolour[] =
              {
              0.5f, 0.0f, 1.0f,
              0.5f, 0.0f, 1.0f,
              0.5f, 0.0f, 0.5f
              };

      float triangeСolour2[] =
              {
                      0.0f, 1.0f, 1.0f,
                      0.0f, 1.0f, 1.0f,
                      0.5f, 0.0f, 0.5f
              };

      float triangeСolour3[] =
              {
                      0.0f, 0.0f, 0.5f,
                      0.0f, 1.0f, 1.0f,
                      0.0f, 0.0f, 0.5f
              };

      float rectangle[] =
              {
              0.1f,  0.1f, 0.0f,  // Верхний правый угол
              0.1f, -0.1f, 0.0f,  // Нижний правый угол
              -0.1f,  0.1f, 0.0f,  // Верхний левый угол
              // Второй треугольник
              0.1f, -0.1f, 0.0f,  // Нижний правый угол
              -0.1f, -0.1f, 0.0f,  // Нижний левый угол
              -0.1f,  0.1f, 0.0f
              };

      float rectangleСolour[] =
              {
                      0.5f, 0.5f, 0.0f,
                      0.5f, 0.5f, 0.0f,
                      0.5f, 0.5f, 0.0f,
                      0.5f, 0.5f, 0.0f,
                      0.5f, 0.5f, 0.0f,
                      0.5f, 0.5f, 0.0f
              };

      float rectangleСolourNew[] =
              {
                      0.0f, 0.5f, 0.0f,
                      0.0f, 0.5f, 0.0f,
                      0.0f, 0.5f, 0.0f,
                      0.0f, 0.5f, 0.0f,
                      0.0f, 0.5f, 0.0f,
                      0.0f, 0.5f, 0.0f
              };

      float cube[] =
              {
                      -1.0f,-1.0f,-1.0f,
                      -1.0f,-1.0f, 1.0f,
                      -1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f,-1.0f,
                      -1.0f,-1.0f,-1.0f,
                      -1.0f, 1.0f,-1.0f,
                      1.0f,-1.0f, 1.0f,
                      -1.0f,-1.0f,-1.0f,
                      1.0f,-1.0f,-1.0f,
                      1.0f, 1.0f,-1.0f,
                      1.0f,-1.0f,-1.0f,
                      -1.0f,-1.0f,-1.0f,
                      -1.0f,-1.0f,-1.0f,
                      -1.0f, 1.0f, 1.0f,
                      -1.0f, 1.0f,-1.0f,
                      1.0f,-1.0f, 1.0f,
                      -1.0f,-1.0f, 1.0f,
                      -1.0f,-1.0f,-1.0f,
                      -1.0f, 1.0f, 1.0f,
                      -1.0f,-1.0f, 1.0f,
                      1.0f,-1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f,-1.0f,-1.0f,
                      1.0f, 1.0f,-1.0f,
                      1.0f,-1.0f,-1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f,-1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f,-1.0f,
                      -1.0f, 1.0f,-1.0f,
                      1.0f, 1.0f, 1.0f,
                      -1.0f, 1.0f,-1.0f,
                      -1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      -1.0f, 1.0f, 1.0f,
                      1.0f,-1.0f, 1.0f
              };

      float cubeColour[] =
              {
                      0.583f,  0.771f,  0.014f,
                      0.609f,  0.115f,  0.436f,
                      0.327f,  0.483f,  0.844f,
                      0.822f,  0.569f,  0.201f,
                      0.435f,  0.602f,  0.223f,
                      0.310f,  0.747f,  0.185f,
                      0.597f,  0.770f,  0.761f,
                      0.559f,  0.436f,  0.730f,
                      0.359f,  0.583f,  0.152f,
                      0.483f,  0.596f,  0.789f,
                      0.559f,  0.861f,  0.639f,
                      0.195f,  0.548f,  0.859f,
                      0.014f,  0.184f,  0.576f,
                      0.771f,  0.328f,  0.970f,
                      0.406f,  0.615f,  0.116f,
                      0.676f,  0.977f,  0.133f,
                      0.971f,  0.572f,  0.833f,
                      0.140f,  0.616f,  0.489f,
                      0.997f,  0.513f,  0.064f,
                      0.945f,  0.719f,  0.592f,
                      0.543f,  0.021f,  0.978f,
                      0.279f,  0.317f,  0.505f,
                      0.167f,  0.620f,  0.077f,
                      0.347f,  0.857f,  0.137f,
                      0.055f,  0.953f,  0.042f,
                      0.714f,  0.505f,  0.345f,
                      0.783f,  0.290f,  0.734f,
                      0.722f,  0.645f,  0.174f,
                      0.302f,  0.455f,  0.848f,
                      0.225f,  0.587f,  0.040f,
                      0.517f,  0.713f,  0.338f,
                      0.053f,  0.959f,  0.120f,
                      0.393f,  0.621f,  0.362f,
                      0.673f,  0.211f,  0.457f,
                      0.820f,  0.883f,  0.371f,
                      0.982f,  0.099f,  0.879f
              };

      glGenBuffers(9, vboID);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(triangeСolour), triangeСolour, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[3]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleСolour), rectangleСolour, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[4]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[5]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColour), cubeColour, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[6]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleСolourNew), rectangleСolourNew, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[7]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(triangeСolour2), triangeСolour2, GL_STATIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, vboID[8]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(triangeСolour3), triangeСolour3, GL_STATIC_DRAW);


      glGenVertexArrays(3, vaoID);

      glBindVertexArray(vaoID[0]);
      glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);

      glBindVertexArray(vaoID[1]);
      glBindBuffer(GL_ARRAY_BUFFER, vboID[4]);
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, vboID[5]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);

      glBindVertexArray(vaoID[2]);
      glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, vboID[3]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);


      //glBindVertexArray(0);
      //glBindVertexArray(1);
      //glBindVertexArray(2);

  }

  //цикл обработки сообщений и отрисовки сцены каждый кадр
  while (!glfwWindowShouldClose(window))
  {
      time_t begin = time(0);
      glfwPollEvents();

      //очищаем экран каждый кадр
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      GL_CHECK_ERRORS;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      GL_CHECK_ERRORS;

      program.StartUseShader();
      GL_CHECK_ERRORS;


      // очистка и заполнение экрана цветом


      //glViewport  (0, 0, WIDTH, HEIGHT);
      int bufferWidth, bufferHeight;
      glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
      glViewport(0, 0, bufferWidth, bufferHeight);

      glEnable(GL_DEPTH_TEST);
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);

      // 1st triangle, moves horisontally
      glm::mat4 trans(1.0f);
      trans = glm::translate(trans, glm::vec3(sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, -0.5f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 5.0f, glm::vec3(1.0f, 0.0f, 1.0f));

      GLuint transformLoc = glGetUniformLocation(program.GetProgram(), "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 2nd triangle, moves horisontally
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, +0.5f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 3.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[7]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 3rd triangle, moves vertically
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(0.5f, sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 3.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[8]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 4th triangle, moves vertically
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(-0.5f, sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 3.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 5th triangle, moves vertically
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(-0.5f, -sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 3.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[7]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 6rd triangle, moves vertically
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(0.5f, -sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 3.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[8]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 7th triangle, moves horisontally
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(-sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, -0.5f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 5.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // 8th triangle, moves horisontally
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(-sin((GLfloat)glfwGetTime() * 0.3f) * 0.7f, +0.5f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 3.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[0]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[7]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // cube
      trans = glm::mat4(1.0f);
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 5.0f, glm::vec3(1.0f, 0.0f, 1.0f));
      trans = Projection * View * trans;
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[1]); GL_CHECK_ERRORS;
      glDrawArrays(GL_TRIANGLES, 0, 36);

      // 1st rectangle
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(sin((GLfloat)glfwGetTime() * 0.8f) * 0.5f, 0.5f * sin((GLfloat)glfwGetTime() * 0.8f), 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 5.0f, glm::vec3(0.5f, 0.5f, 0.5f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[2]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[3]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 6);

      // 2nd rectangle
      trans = glm::mat4(1.0f);
      trans = glm::translate(trans, glm::vec3(-sin((GLfloat)glfwGetTime() * 0.8f) * 0.5f, -sin((GLfloat)glfwGetTime() * 0.8f)* 0.5f, 0.0f));
      trans = glm::rotate(trans,(GLfloat)glfwGetTime() * 5.0f, glm::vec3(0.5f, 0.5f, 0.5f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
      glBindVertexArray(vaoID[2]); GL_CHECK_ERRORS;
      glBindBuffer(GL_ARRAY_BUFFER, vboID[6]);
      glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, 0);
      glDrawArrays(GL_TRIANGLES, 0, 6);


      program.StopUseShader();

      glfwSwapBuffers(window);

      sleep(0.015 - difftime(time(0), begin));
  }

  //очищаем vboи vao перед закрытием программы
    glDeleteVertexArrays(3, vaoID);
    glDeleteBuffers(7, vboID);

  glfwTerminate();
  return 0;
}
