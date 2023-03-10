/*
* Visualization 1 - Task 1 Framework
* Copyright (C) University of Passau
*   Faculty of Computer Science and Mathematics
*   Chair of Cognitive sensor systems
* Maintenance:
*   2022, Anja Heim <anja.heim@uni-passau.de>
*	2022, Alexander Gall <alexander.gall@uni-passau.de>
*
*
* All rights reserved.
*
* Acknowledgements:
*   Special thanks to the TU Wien for providing the basic framework:
*       Institute of Visual Computing and Human-Centered Technology
*       Research Unit of Computer Graphics
*/

#include "GLWidget.h"

#include <glsw.h>
#include <glm/gtc/type_ptr.hpp>
#include <QMouseEvent>
#include <QDir>
#include <qopenglwidget.h>
#include <qmessagebox.h>
#include <qopenglframebufferobject.h>
#include <QOpenGLTexture>

#include "MainWindow.h"

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

GLfloat cube_vertices[] = {
	// front
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0,
};

GLfloat tex_coordinates[] = {
	// front
	0.0, 0.0,  1.0,
	1.0, 0.0,  1.0,
	1.0,  1.0,  1.0,
	0.0,  1.0,  1.0,
	// back
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0,  1.0, 0.0,
	0.0,  1.0, 0.0,
};

GLushort cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 0, 3,
	3, 7, 4,
	// left
	4, 5, 1,
	1, 0, 4,
	// right
	3, 2, 6,
	6, 7, 3,
};

GLfloat quad_vertices[] =
{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f
};

GLushort quad_elements[] =
{
	0, 1, 2, 
	0, 2, 3
};

GLWidget::GLWidget(QWidget *parent, MainWindow *mainWindow)
	: QOpenGLWidget(parent),
	m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
	m_indexBuffer(QOpenGLBuffer::IndexBuffer),
	m_vertexBufferQuad(QOpenGLBuffer::VertexBuffer),
	m_indexBufferQuad(QOpenGLBuffer::IndexBuffer)
{
	m_MainWindow = mainWindow;
	m_renderingMode = 0;
	m_VolumeTexture = NULL;
	QSurfaceFormat format;
	// asks for a OpenGL 3.3 debug context using the Core profile
	format.setMajorVersion(3);
	format.setMinorVersion(3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setOption(QSurfaceFormat::DebugContext);

	setFormat(format);

	// watch all shader of the shader folder
	// every time a shader changes it will be recompiled on the fly
	m_fileWatcher = new QFileSystemWatcher(this);
	connect(m_fileWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChanged(const QString&)));

	addFilesToWatcher();

	initglsw(); // initializes the OpenGL Shader Wrangler
}

GLWidget::~GLWidget()
{
	cleanup();
}

// initializes the OpenGL Shader Wrangler
void GLWidget::initglsw()
{
	glswInit();
	glswSetPath(shaderDir.c_str(), ".glsl");
	glswAddDirectiveToken("", "#version 330");
}

// the rendering routing, this function is called for every frame
void GLWidget::paintGL()
{
	// the matrix must be transposed when it is passed from glm to QT!
	QMatrix4x4 modelView = QMatrix4x4(glm::value_ptr(m_camera.getViewMatrix())).transposed();
	QMatrix4x4 projection = QMatrix4x4(glm::value_ptr(m_camera.getProjectionMatrix())).transposed();

	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vaoCube);
	m_programCube->bind();

	m_programCube->setUniformValue(2, modelView);
	m_programCube->setUniformValue(3, projection);
	m_programCube->setUniformValue(4, QVector3D(scale.x, scale.y, scale.z));

	// 1. render front faces to FBO
	/* With the optimizations, this is directly done in the raycasting shader 
	 * and we don't need to run the cube shader anymore. 
	 
	// Bind the front faces buffer to the `fragColor` our variable in the cube shader.
	m_FBO_frontFaces->bind();
	// Reset the OpenGL state.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Don't draw triangles that are behind other triangles. Only draw the front triangles.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 
	
	// Draw to m_FBO_frontFaces.
	// (There are several buffers currently bound: vaoBinder, m_programCube, m_FBO_frontFaces, 
	// and other from the `initializeGL()` function, like the cube vertices.)
	glDrawElements(
		GL_TRIANGLES,                 // mode
		12 * 3 * sizeof(GLushort),    // count
		GL_UNSIGNED_SHORT,            // type
		(void*)0                      // element array buffer offset
	);
	// We're done with the front faces.
	glDisable(GL_CULL_FACE);
	m_FBO_frontFaces->release();
	*/

	// 2. render back faces to FBO
	// I didn't manage to optimize this one away. The math defeated me.
	m_FBO_backFaces->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	// This time only draw the back trianges, not the front ones.
	glCullFace(GL_FRONT); 
	
	// Execute the same shader as with the front faces, but this time
	// to the back faces buffer, and with a different `glCullFace()` mode.
	glDrawElements(
		GL_TRIANGLES,                 // mode
		12 * 3 * sizeof(GLushort),    // count
		GL_UNSIGNED_SHORT,            // type
		(void*)0                      // element array buffer offset
	);
	glDisable(GL_CULL_FACE);
	m_FBO_backFaces->release();

	vaoBinder.release();

	// 3. render the volume

	QOpenGLVertexArrayObject::Binder vaoBinder2(&m_vaoQuad);
	m_programRaycasting->bind();

	// Render to the default framebuffer, which is the screen.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// We don't want to raycast from the back triangles of the cube.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Set the variables in the raycasting shader.
	// The number must match the layout location in the shader.
	m_programRaycasting->setUniformValue(2, modelView);
	m_programRaycasting->setUniformValue(3, projection);
	m_programRaycasting->setUniformValue(4, QVector3D(scale.x, scale.y, scale.z));

	m_programRaycasting->setUniformValue(8, m_renderingMode);
	m_programRaycasting->setUniformValue(9, m_iso);

	m_programRaycasting->setUniformValue(11, height());
	m_programRaycasting->setUniformValue(12, width());
	
	// Bind the frontFaces texture in location 5
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_FBO_frontFaces->texture());
	GLuint frontFaces_location = 5;
	glUniform1i(frontFaces_location, 0);
	
	// Bind the backFaces texture in location 6
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_FBO_backFaces->texture());
	GLuint backFaces_location = 6;
	glUniform1i(backFaces_location, 1);

	// Bind the volume data in location 7
	glActiveTexture(GL_TEXTURE2);
	m_VolumeTexture->bind();
	GLuint volume_location = 7;
	glUniform1i(volume_location, 2);

	// Draw the Cube in the raycasting shader. It was bound in `initializeGL()`.
	// The magic happens in its fragment shader, which does the ray casting.
	glDrawElements(
		GL_TRIANGLES,                // mode
		12 * 3 * sizeof(GLushort),   // count
		GL_UNSIGNED_SHORT,           // type
		(void*)0                     // element array buffer offset
	);

	glDisable(GL_CULL_FACE);
	vaoBinder2.release();
}

void GLWidget::initializeGL()
{
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

	m_logger = new QOpenGLDebugLogger(this);
	m_logger->initialize();
	connect(m_logger, &QOpenGLDebugLogger::messageLogged, this, &GLWidget::handleLoggedMessage, Qt::DirectConnection);

	setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	m_VolumeTexture = new QOpenGLTexture(QOpenGLTexture::Target3D);
	m_VolumeTexture->setFormat(QOpenGLTexture::RGB32F);

	initializeOpenGLFunctions();
	// Default background color is a dark grey.
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	
	glEnable(GL_DEPTH_TEST);

	// create programs
	m_programCube = new QOpenGLShaderProgram();
	m_programRaycasting = new QOpenGLShaderProgram();

	loadShaders();
	
	// create Frame Buffer Object (FBO)
	m_FBO_frontFaces = new QOpenGLFramebufferObject(width(), height());
	m_FBO_backFaces = new QOpenGLFramebufferObject(width(), height());

	if (!m_vaoCube.create()) {
		qDebug() << "error creating vao";
	}

	// bind vertex array object (VAO)
	// the VAO encapsulates all the data that is associated with the vertex processor
	// see: http://ogldev.atspace.co.uk/www/tutorial32/tutorial32.html
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vaoCube);
	
	// Setup our vertex buffer object
	m_vertexBuffer.create();
	m_vertexBuffer.bind();
	// Setup our index buffer object
	m_indexBuffer.create();
	m_indexBuffer.bind();

	// allocate vertices and indices of a cube
	m_vertexBuffer.allocate(cube_vertices, 8 * 3 * sizeof(GLfloat));
	m_indexBuffer.allocate(cube_elements, 12 * 3 * sizeof(GLushort)); 

	m_programCube->enableAttributeArray(0);
	m_programCube->enableAttributeArray(1);

	m_programCube->setAttributeBuffer(
		0,			// Specifies the index of the generic vertex attribute to be modified
		GL_FLOAT,	// Specifies the data type of each component in the array
		0,			// Specifies the byte offset between consecutive generic vertex attributes
		3			// Specifies the number of components per generic vertex attribute
	);


	// Setup our tex coord buffer object
	m_texCoordBuffer.create();
	m_texCoordBuffer.bind();

	m_texCoordBuffer.allocate(tex_coordinates, 8 * 3 * sizeof(GLfloat));
	
	m_programCube->setAttributeBuffer(
		1,			// Specifies the index of the generic vertex attribute to be modified
		GL_FLOAT,	// Specifies the data type of each component in the array
		0,			// Specifies the byte offset between consecutive generic vertex attributes
		3			// Specifies the number of components per generic vertex attribute
	);

	if (!m_vaoQuad.create()) {
		qDebug() << "error creating vao";
	}

	QOpenGLVertexArrayObject::Binder vaoBinder2(&m_vaoQuad);
	
	/* With the optimizations, the Quad is no longer needed.
	m_vertexBufferQuad.create();
	m_vertexBufferQuad.bind();

	m_indexBufferQuad.create();
	m_indexBufferQuad.bind();

	m_vertexBufferQuad.allocate(quad_vertices, 4 * 3 * sizeof(GLfloat));
	m_indexBufferQuad.allocate(quad_elements, 2 * 3 * sizeof(GLushort));
	*/
	
	// Instead of the Quad, the cube is now bound to the raycasting shader.
	m_vertexBuffer.bind();
	m_indexBuffer.bind();

	m_programRaycasting->setAttributeBuffer(
		0,			// Specifies the index of the generic vertex attribute to be modified
		GL_FLOAT,	// Specifies the data type of each component in the array
		0,			// Specifies the byte offset between consecutive generic vertex attributes
		3			// Specifies the number of components per generic vertex attribute
	);

	m_programRaycasting->enableAttributeArray(0);
	
	GLint total_mem_kb = 0;
	glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX,
		&total_mem_kb);

	GLint cur_avail_mem_kb = 0;
	glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX,
		&cur_avail_mem_kb);

	float cur_avail_mem_mb = float(cur_avail_mem_kb) / 1024.0f;
	float total_mem_mb = float(total_mem_kb) / 1024.0f;

	m_MainWindow->displayTotalGPUMemory(total_mem_mb);
	m_MainWindow->displayUsedGPUMemory(total_mem_mb - cur_avail_mem_mb);
}

// this function is called when the volume texture is loaded 
void GLWidget::volumeTextureLoaded(Volume *volume)
{
	float max = std::max(std::max(volume->width(), volume->height()), volume->depth());
	scale = glm::vec3(volume->width(), volume->height(), volume->depth()) / max;
	
	makeCurrent();
	
	delete m_VolumeTexture; //delete if initialized
	m_VolumeTexture = new QOpenGLTexture(QOpenGLTexture::Target3D);
	m_VolumeTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
	m_VolumeTexture->setFormat(QOpenGLTexture::RGB32F);

	m_VolumeTexture->setSize(volume->width(), volume->height(), volume->depth());

	m_VolumeTexture->allocateStorage(QOpenGLTexture::Red, QOpenGLTexture::Float32);
	m_VolumeTexture->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, volume->voxels());
	doneCurrent();
}

void GLWidget::cleanup()
{
	if (m_VolumeTexture == nullptr)
		return;

	glswShutdown();

	makeCurrent();
	
	m_VolumeTexture->destroy();
	m_VolumeTexture = nullptr;
	
	m_FBO_frontFaces->release();
	m_FBO_backFaces->release();
	m_FBO_frontFaces = nullptr;
	m_FBO_backFaces = nullptr;
	
	m_programCube->release();
	m_programRaycasting->release();
	m_programCube = nullptr;
	m_programRaycasting = nullptr;

	delete m_logger;
	delete m_fileWatcher;

	doneCurrent();
}

void GLWidget::fileChanged(const QString &path)
{
	// reboot glsw, otherwise it will use the old cached shader
	glswShutdown();
	initglsw();

	loadShaders();
	addFilesToWatcher();

	update();
}

void GLWidget::addFilesToWatcher()
{
	foreach(QFileInfo file, QDir(shaderDir.c_str()).entryInfoList()) {
		if (file.isFile()) {
			m_fileWatcher->addPath(file.absoluteFilePath());
		}
	}
}

void GLWidget::loadShaders()
{
	qDebug() << "Compiling shader 'cube':";
	compileShaders("cube", m_programCube);
	qDebug() << "Compiling shader 'raycasting':";
	compileShaders("raycasting", m_programRaycasting);
	qDebug() << "Done Compiling.";
}

bool GLWidget::compileShaders(std::string name, QOpenGLShaderProgram* shader)
{
	bool success = true;

	const char* vs = glswGetShader((name + ".Vertex").c_str());
	success = success && vs;
	if (!success) qDebug() << "Error in glswGetShader()";
	QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
	success &= vertexShader->compileSourceCode(vs);
	if (!success) qDebug() << "Error in compileSourceCode()" << vertexShader->log();

	const char* fs = glswGetShader((name + ".Fragment").c_str());
	success = success && fs;
	if (!success) qDebug() << "Error in glswGetShader() 2";
	QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
	success &= fragmentShader->compileSourceCode(fs);
	if (!success) qDebug() << "Error in compileSourceCode() 2" << fragmentShader->log();

	shader->removeAllShaders();
	shader->addShader(vertexShader);
	shader->addShader(fragmentShader);
	shader->link();

	//if (!success) qDebug() << "Error loading & compiling " << name.c_str() << " shader.";

	return success;
}

// this function is called whenever the widget has been resized
void GLWidget::resizeGL(int w, int h)
{
	// when the widget is resized, the aspect ratio of the camera needs to be updated
	m_camera.setAspect(float(w) / h);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();

	QCursor c = cursor();
	c.setShape(Qt::BlankCursor);
	setCursor(c);
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	QCursor c = cursor();
	c.setShape(Qt::ArrowCursor);
	setCursor(c);
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	m_camera.updatePos(0, 0, event->angleDelta().y() / 100.0f);
	update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	float dx = (event->x() - m_lastPos.x()) / 100.0f;
	float dy = (event->y() - m_lastPos.y()) / 100.0f;

	if (event->buttons() & Qt::LeftButton)
	{
		m_camera.updateRot(dy, dx, 0);
	}
	else if (event->buttons() & Qt::RightButton)
	{
		m_camera.updateRot(dy, 0, dx);
	}
	else if (event->buttons() & Qt::MidButton)
	{
		m_camera.updatePos(dx, -dy, 0);
	}

	QCursor c = cursor();
	c.setPos(mapToGlobal(m_lastPos));
	setCursor(c);

	update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
	{
		m_MainWindow->close();
		break;
	}
	default:
	{
		event->ignore();
		break;
	}
	}
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{

}

void GLWidget::handleLoggedMessage(const QOpenGLDebugMessage& msg)
{
	//ignore performance warnings
	if (msg.id() == 131185 || msg.id() == 131218) return;

	qDebug() << "[" << msg.id() << "] " << qPrintable(msg.message());
}