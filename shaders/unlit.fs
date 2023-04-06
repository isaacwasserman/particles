#version 400

uniform vec3 color;
uniform float alpha;

out vec4 FragColor;

void main()
{
   FragColor = vec4(color, alpha);
}
