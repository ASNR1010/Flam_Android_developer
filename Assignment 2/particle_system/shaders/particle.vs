#version 300 es
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aVelocity;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aLifetime;

uniform float uTime;
uniform vec2 uResolution;

out vec4 vColor;
out float vLifetime;

void main() {
    float age = uTime - aLifetime;
    vec2 position = aPos + aVelocity.xy * age;
    gl_Position = vec4((position / uResolution) * 2.0 - 1.0, 0.0, 1.0);
    gl_PointSize = 10.0;
    vColor = aColor;
    vLifetime = 1.0 - (age / aLifetime);
}