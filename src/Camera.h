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

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 

class Camera
{
public:

	Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	
	void buildProjectionMatrix();

	void updatePos(float x, float y, float z);
	void updateRot(float x, float y, float z);

	void setAspect(float aspect) { m_Aspect = aspect; buildProjectionMatrix(); }
	void setOrthogonal(bool orthogonal) { m_Orthogonal = orthogonal; buildProjectionMatrix(); }
	void setFOV(float fov) { m_FieldOfView = fov; buildProjectionMatrix(); }
	void setNear(float near_) { m_Near = near_; buildProjectionMatrix(); }
	void setFar(float far_) { m_Far = far_; buildProjectionMatrix(); }
	
	glm::vec3 getPos() { return -m_translation * m_rotation; }

private:
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	glm::vec3 m_Up;
	float m_FieldOfView;
	float m_Aspect;
	float m_Near;
	float m_Far;
	bool m_Orthogonal = false;

	glm::vec3	m_translation;
	glm::quat	m_rotation;
};