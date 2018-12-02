#version 130

uniform sampler2D texture;
uniform sampler2D lookup;

uniform float decay;

const float TILE_SIZE = 32;
const float NUM_TILES = 64;

void main()
{
	vec2 position = gl_TexCoord[0].xy;

	vec4 pixel = texture2D(texture, position);

	if (pixel.a == 0)
	{
		discard;
	}

	vec2 tileSize = vec2(1.0f / NUM_TILES);

	vec2 p = 1.0f - position;
	vec2 i = floor(p * NUM_TILES) / NUM_TILES;
	vec2 f = ((p - i) / tileSize);
	vec2 m = texture2D(lookup, f).rg * 255.0f;

	float index = m.x + (TILE_SIZE * m.y);

	if ((decay * (TILE_SIZE * TILE_SIZE)) <= index)
	{
		gl_FragColor = vec4(pixel.rgb, 0.2);
	}
	else
	{
		gl_FragColor = pixel;
	}
}
