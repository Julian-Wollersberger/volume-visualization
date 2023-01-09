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

// I think this binds to the 'texCoord' variable in the Fragment shader.
out vec2 texCoord;

void main()
{
	

	gl_Position.xyz = vertex;
	gl_Position.w = 1.0;

	// What should this one do? 
	// It doesn't apply the camera transform, that's the job of "cube.glsl".

	texCoord = vec2(0,0);
}

-- Fragment

#extension GL_ARB_explicit_uniform_location : enable

// "uniform" means that this value is the same in all parallel executions of this shader.

// "sampler2D" means its a 2D array of (what? vec3? vec4?) values.
// The frontFaces are the (world) coordinates where the rays should start. 
// backFaces are the coordinates where the rays should end.
layout(location = 5) uniform sampler2D frontFaces;
layout(location = 6) uniform sampler2D backFaces;
// This is the data of the scan.
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
			fragColor = vec4(1,0,0,1);
			return;
		}
		case 1: //render back faces
		{
			fragColor = vec4(0,1,0,1);
			return;
		}
		case 2: //render volume (positions)
		{
			fragColor = vec4(0,0,1,1);
			return;
		}
		case 3: //render volume (shaded)
		{
			fragColor = vec4(1,1,0,1);
			return;
		}
	}

	
}


