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

layout(location = 0) in vec3 vertex;

out vec2 texCoord;

void main()
{
	// *your code here*

	gl_Position = vec4(0);
}

-- Fragment

#extension GL_ARB_explicit_uniform_location : enable

layout(location = 5) uniform sampler2D frontFaces;
layout(location = 6) uniform sampler2D backFaces;
layout(location = 7) uniform sampler3D volume;

layout(location = 8) uniform int renderingMode;
layout(location = 9) uniform float iso = 0.1;
layout(location = 10) uniform int MAX_STEPS = 1024;

in vec2 texCoord;
out vec4 fragColor;

void main()
{
	// *your code here*

	switch(renderingMode)
	{
		case 0: //render front faces
		{
			fragColor = vec4(0);
			return;
		}
		case 1: //render back faces
		{
			fragColor = vec4(0);
			return;
		}
		case 2: //render volume (positions)
		{
			fragColor = vec4(0);
			return;
		}
		case 3: //render volume (shaded)
		{
			fragColor = vec4(0);
			return;
		}
	}
}
