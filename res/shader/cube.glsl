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
	// This part of the shader processes each corner of the containing cube.
	// The camera movement can only be applied to the final vertex position, 
	// but not to the "frontFaces" part.

	gl_Position = projMatrix * mvMatrix * vec4(vertex * scale, 1.0); 
	//texCoordVar = gl_Position.xyz;
	
	// Move the cube to have one corner at (0|0|0), instead of at (-1|-1|-1).
	// The other corner must stay at (1|1|1), so divide by two.
	texCoordVar = (vertex.xyz + 1.0) / 2.0;
}

-- Fragment

in vec3 texCoordVar;

out vec4 fragColor;

void main()
{
	// *your code here*

	// "Fragment" essentially means "pixel", but maybe at a different resolution.
	// So this shader gives every pixel a value.
	//fragColor = vec4(1, 1, 0, 1);


	// New understanding: 
	// The Vertex shader puts the position into `texCoordVar`
	// and this shader interpolates that and interprets the position as a color.
	// Except that Opacity must be 1.0

	fragColor = vec4(texCoordVar.x, texCoordVar.y, texCoordVar.z, 1.0);
}

