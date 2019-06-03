layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoord;
layout (location = 2) in vec3 a_norm;
#ifdef INSTANCING
layout (location = 3) in mat4 a_matrix;
#endif

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_lightPos;

uniform float u_texRows = 1;
uniform vec2 u_texOffset = {0, 0};

out vec2 texCoord;
out vec3 surfaceNorm;
out vec3 lightNorm;

void main()
{	
	mat4 modelP = u_model;
#ifdef INSTANCING
	modelP = a_matrix;
#endif

	gl_Position = u_projection * u_view * modelP * vec4(a_pos, 1.0f);

	texCoord = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
	texCoord = (texCoord / u_texRows) + u_texOffset;

	vec4 worldPos = modelP * vec4(a_pos, 1.0);

	surfaceNorm = normalize((modelP * vec4(a_norm, 0.0)).xyz);
	lightNorm = normalize(u_lightPos - worldPos.xyz);
}


