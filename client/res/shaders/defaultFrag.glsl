uniform sampler2D u_tex;
uniform vec4 u_meshColor;
uniform vec3 u_lightColor;

in vec2 texCoord;
in vec3 surfaceNorm;
in vec3 lightNorm;

out vec4 fragColor;

void main()
{
	float nDotl = dot(surfaceNorm, lightNorm);

	float amb = 0.6;
	float brightness = amb + (1.0 - amb) * nDotl;

	vec3 diffuse = brightness * u_lightColor;

	//fragColor = (model_color * u_texture(u_texture, u_texture_coord));
	//fragColor = vec4(diffuse, 1.0) * u_texture(u_tex, texCoord) * u_meshColor;
	//fragColor = vec4(diffuse, 1.0) * u_meshColor;
	fragColor = vec4(vec3(surfaceNorm) * .5 + .5, 1.0);
	//fragColor = u_meshColor;
}

