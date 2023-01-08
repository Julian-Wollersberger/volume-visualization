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

#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QFileSystemWatcher>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>

#include "Camera.h"
#include "Volume.h"

class MainWindow;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent, MainWindow *mainWindow);
	~GLWidget();

	Camera m_camera;
	int m_renderingMode;
	float m_iso = 0.1f;

public slots:
	void cleanup();
	void volumeTextureLoaded(Volume *volume);

signals:

protected:

	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

protected slots:

	void paintGL() Q_DECL_OVERRIDE;
	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void fileChanged(const QString &path);
	void addFilesToWatcher();
	void handleLoggedMessage(const QOpenGLDebugMessage& msg);

private:

	std::string shaderDir = "./res/shader/";
	

	void initglsw();
	void loadShaders();
	bool compileShaders(std::string name, QOpenGLShaderProgram* shader);

	QOpenGLShaderProgram *m_programCube;
	QOpenGLShaderProgram *m_programRaycasting;

	QOpenGLVertexArrayObject m_vaoCube;
	QOpenGLVertexArrayObject m_vaoQuad;
	
	QOpenGLBuffer m_vertexBuffer;
	QOpenGLBuffer m_indexBuffer;
	QOpenGLBuffer m_texCoordBuffer;

	QOpenGLBuffer m_vertexBufferQuad;
	QOpenGLBuffer m_indexBufferQuad;

	QOpenGLTexture *m_VolumeTexture;

	QOpenGLDebugLogger *m_logger;
	
	QOpenGLFramebufferObject *m_FBO_frontFaces;
	QOpenGLFramebufferObject *m_FBO_backFaces;

	QFileSystemWatcher *m_fileWatcher;

	QPoint m_lastPos;

	MainWindow *m_MainWindow;

	glm::vec3 scale = glm::vec3(1);
};


