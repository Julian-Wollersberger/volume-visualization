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

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	m_rotation = glm::quat(glm::vec3(glm::radians(180.0f), 0, 0));
	m_translation = glm::vec3(0, 0, -3);

	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Near = 0.1f;
	m_Far = 500.0f;
	m_FieldOfView = 60.0f;
	m_Aspect = 4.0f / 3.0f;

	m_ViewMatrix = glm::mat4(1);
	m_ProjectionMatrix = glm::mat4(1);
	
	buildProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
	// rotation
	const glm::mat4 rotationMat = mat4_cast(m_rotation);

	// translation
	const glm::mat4 translationMat = translate(glm::mat4(1), m_translation);

	m_ViewMatrix = translationMat * rotationMat;
	return m_ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return m_ProjectionMatrix;
}

void Camera::buildProjectionMatrix()
{
	if (m_Orthogonal) {
		m_ProjectionMatrix = glm::ortho(-2.0f, 2.0f, 2.0f, -2.0f, m_Near, m_Far);
	}
	else {
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FieldOfView), m_Aspect, m_Near, m_Far);
	}
}

void Camera::updatePos(float x, float y, float z)
{
	m_translation += glm::vec3(x, y, z);
}

void Camera::updateRot(float x, float y, float z)
{
	m_rotation = normalize(glm::quat(glm::vec3(x, y, z)) * m_rotation);
	auto read_me = eulerAngles(m_rotation);
}
