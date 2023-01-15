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

// The raycasting shader renders on the "m_vertexBufferQuad",
// which is just a sqare. It's basically the 2D texture.
layout(location = 0) in vec3 vertex;

// I think this binds to the 'texCoord' variable in the Fragment shader.
out vec2 texCoord;

void main()
{
	gl_Position = vec4(vertex, 1.0);

	// What should this one do? 
	// It doesn't apply the camera transform, that's the job of "cube.glsl".

	// I think it just maps the vertec coordinates to the texture coordinates.
	texCoord = vertex.xy;
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
layout(location = 10) uniform int MAX_STEPS = 10; //1024;



in vec2 texCoord;
out vec4 fragColor;

vec4 trace_ray(vec2 texCoordNormalized) 
{
	// end position minus start position gives the ray direction.
	vec4 start = texture(frontFaces, texCoordNormalized);
	vec4 end = texture(backFaces, texCoordNormalized);
	vec4 direction = end - start;
	// Divide that into the individual steps
	vec4 step = direction / MAX_STEPS;

	bool was_hit = false;
	vec4 last_point = start;
	vec4 last_density = vec4(0.0);
	vec4 current_point = start;
	vec4 current_density = vec4(0.0);

	for (int i = 0; i < MAX_STEPS; i++)
	{
		last_point = current_point;
		last_density = current_density;
		// Doing `+= step` is slightly faster than `i * step`, at the cost of accumulating rounding errors.
		//current_point = start + i * step;
		current_point += step;
		
		// Get the density at the current ray position.
		current_density = texture(volume, current_point.xyz);
		
		// The volume contains vec4, but only the x component seems to be used.
		// TODO: Verify that.
		if (current_density.x > iso) {
			was_hit = true;
			break;
		}
	}

	// # Interpolate between the last two steps.
	// 
	// We want to only go a fraction of `step` from `last_point` to `current_point`, not the whole step.
	// That fraction is determined by where `iso` is inbetween the two.
	// 
	// Example: `iso` is 0.1, `last_density` is 0.09, `current_density` is 0.12. Then the interpolated point
	// is a third of the way between the two, meaning that `fraction` is 0.3333.
	float fraction = length(iso - last_density) / length(current_density - last_density);
	fraction = clamp(fraction, 0, 1); // Prevents visual noise.
	vec4 first_hit = last_point + fraction * step;

	if (was_hit) {
		return vec4(first_hit.xyz, 1.0); // Position of the first hit
	} else {
		return vec4(0.0); // black
	}
}

void main()
{
	// the `texture()` call wants the coordinates to be from 0 to 1, not -1 to 1.
	vec2 texCoordNormalized = (texCoord + 1.0) / 2.0;

	switch(renderingMode)
	{
		case 0: //render front faces
		{
			fragColor = texture(frontFaces, texCoordNormalized);
			return;
		}
		case 1: //render back faces
		{
			fragColor = texture(backFaces, texCoordNormalized);
			return;
		}
		case 2: //render volume (positions)
		{
			fragColor = trace_ray(texCoordNormalized);
			return;
		}
		case 3: //render volume (shaded)
		{
			fragColor = vec4(1,1,0,1);
			return;
		}
	}
}

