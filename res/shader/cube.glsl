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

-- Vertex

#extension GL_ARB_explicit_attrib_location : enable
#extension GL_ARB_explicit_uniform_location : enable

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 texCoord;

layout(location = 2) uniform mat4 mvMatrix;
layout(location = 3) uniform mat4 projMatrix;

layout(location = 4) uniform vec3 scale;

out vec3 texCoordVar;


void main()
{
	// *your code here*

	gl_Position = projMatrix * mvMatrix * vec4(vertex * scale, 1); 
}

-- Fragment

in vec3 texCoordVar;

out vec4 fragColor;

void main()
{
	// *your code here*

	fragColor = vec4(0);
}