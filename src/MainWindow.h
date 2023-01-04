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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Volume.h"
#include "GLWidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget *parent = 0);
	~MainWindow() = default;

	void displayTotalGPUMemory(float size);
	void displayUsedGPUMemory(float size);

public slots:
	void openFileAction();
	
protected slots :

	void closeAction();
	void fieldOfViewChanged(int value);
	void perspectiveChanged(int value);
	void renderingModeChanged(int value);
	void isoValueChanged(double value);
	void nearPlaneChanged(double value);
	void farPlaneChanged(double value);
		

private:

	// USER INTERFACE ELEMENTS

	Ui_MainWindow *m_Ui;

	// DATA 
	enum DataType
	{
		VOLUME = 0,
		VECTORFIELD	 = 1,
		MULTIVARIATE = 2
	};

	struct FileType
	{
		QString			filename;
		DataType		type;
	} m_FileType;

	Volume *m_Volume;

	GLWidget *m_glWidget;
};

#endif
