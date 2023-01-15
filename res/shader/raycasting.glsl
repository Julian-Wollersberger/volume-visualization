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
// which is just a sqare that covers the whole screen.
layout(location = 0) in vec3 vertex;

// This binds to the 'texCoord' variable in the Fragment shader.
out vec2 texCoord;

// This part of the shader processes each corner of the square.
void main()
{
	// The square is already defined to be at the exact position to cover the whole screen.
	gl_Position = vec4(vertex, 1.0);
	// This maps the vertex coordinates to the 2D texture coordinates.
	texCoord = vertex.xy;
}

-- Fragment

#extension GL_ARB_explicit_attrib_location : enable
#extension GL_ARB_explicit_uniform_location : enable

// "uniform" means that this value is the same in all parallel executions of this shader.

// The transforms to apply to a point to get to camera space. 
// There we know that the camera is always at vec4(0), and we can do the shading calculation.
layout(location = 2) uniform mat4 mvMatrix;
layout(location = 3) uniform mat4 projMatrix;
layout(location = 4) uniform vec3 scale;

// "sampler2D" means its a 2D array of values.
// The frontFaces are the coordinates where the rays should start. 
// backFaces are the coordinates where the rays should end.
layout(location = 5) uniform sampler2D frontFaces;
layout(location = 6) uniform sampler2D backFaces;
// This is the loaded data of the scan.
layout(location = 7) uniform sampler3D volume;

layout(location = 8) uniform int renderingMode;
layout(location = 9) uniform float iso;
// The step size shouldn't be much more than the model resolution, otherwise the gradient gets to pixelated.
layout(location = 10) uniform int MAX_STEPS = 256;
 
 // Interpolated pixel coordinate.
in vec2 texCoord;
// The color that gets drawn.
out vec4 fragColor;

// This struct is needed to return multiple values from `trace_ray().`
struct RayTraceResult {
	vec4 position;
	vec4 step;
	bool was_hit;
};

// Shot a ray through the volume to do the first hit detection.
RayTraceResult trace_ray(vec2 texCoordNormalized) 
{
	// end position minus start position gives the ray direction.
	vec4 start = texture(frontFaces, texCoordNormalized);
	vec4 end = texture(backFaces, texCoordNormalized);
	vec4 direction = end - start;
	// Divide that into the individual steps.
	vec4 step = vec4(direction.xyz / MAX_STEPS, 1.0);

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
	 
	vec4 pos;
	if (was_hit) {
		pos = vec4(first_hit.xyz, 1.0); // Position of the first hit
	} else {
		pos = vec4(0.0); // black otherwise.
	}
	return RayTraceResult(pos, step, was_hit);
}

// The surface gradient is used as the normal vector for shading calculation.
// I'm using `vec3` instead of `vec4` here, because the math is defined in terms of `vec3`.
vec3 surface_gradient_normalized(vec3 pos, float step) 
{
	// This formular for gradient calculation is from the exercise description. 
	// `gradient` is Δf, `step` is 𝜀 and the `texture(volume, pos.xyz)` call is `f(x, y, z)`. 
	// The term `f(x - 𝜀)` is a shorthand for `f(x - 𝜀, y, z)`.
	// The formular divides the result by 2, but since it needs to be normalized anyway, the division can be ommited.
	vec3 gradient = vec3(
		texture(volume, vec3(pos.x - step, pos.y, pos.z)).x - texture(volume, vec3(pos.x + step, pos.y, pos.z)).x,
		texture(volume, vec3(pos.x, pos.y - step, pos.z)).x - texture(volume, vec3(pos.x, pos.y + step, pos.z)).x,
		texture(volume, vec3(pos.x, pos.y, pos.z - step)).x - texture(volume, vec3(pos.x, pos.y, pos.z + step)).x
	);
	// Divide the vector by its length to get a vector of length 1.
	vec3 normal = normalize(gradient);
	return normal;
}

vec4 diffuse_shading(vec3 position, vec3 normal) 
{
	// Adapted from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/

	// Transform the position (which is in model space) into the camera space.
	vec4 position_in_cameraspace = projMatrix * mvMatrix * vec4(position * scale, 1.0);
	vec4 normal_in_cameraspace = normalize(projMatrix * mvMatrix * vec4(normal * scale, 1.0));
	// The camera is always at the origin of the camera space.
	vec3 cam_pos = vec3(0.0, 0.0, 0.0);

	// The light is placed at the camera.
	vec3 light_direction = normalize(position_in_cameraspace.xyz - cam_pos);

	// Cosine of the angle between the normal and the light direction, clamped above 0.
	//  - light is at the vertical of the surface -> 1
	//  - light is perpendicular to the surface -> 0
	//  - light is behind the triangle -> negative -> clamp to 0
	float cos_theta = clamp(dot(normal_in_cameraspace.xyz, light_direction), 0, 1);

	vec4 light_color = vec4(1.0, 1.0, 1.0, 1.0); // light blue 
	// The more the light shines at an angle, the darker it becomes.
	vec4 color = light_color * cos_theta;
	return color;
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
			fragColor = trace_ray(texCoordNormalized).position;
			return;
		}
		case 3: //render volume (shaded)
		{
			RayTraceResult res = trace_ray(texCoordNormalized);
			if (res.was_hit) {
				vec3 normal = surface_gradient_normalized(res.position.xyz, length(res.step.xyz));
				fragColor = diffuse_shading(res.position.xyz, normal);
			} else {
				// In case we didn't hit the volume, we want a background color.
				fragColor = vec4(0.0); // black
			}
			return;
		}
	}
}

