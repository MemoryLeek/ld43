#version 130

uniform sampler2D texture;

uniform float opacity;

void main()
{
	vec2 position = gl_TexCoord[0].xy;

	vec4 pixel = texture2D(texture, position);

	if (pixel.a == 0)
	{
		discard;
	}

	gl_FragColor = vec4(pixel.rgb + (1.0f- opacity) / 2, opacity);
}
