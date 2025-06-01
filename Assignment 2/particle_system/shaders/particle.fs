#version 300 es
precision mediump float;

in vec4 vColor;
in float vLifetime;
out vec4 FragColor;

void main() {
    vec4 color = vColor;
    color.a *= vLifetime;
    FragColor = color;
}