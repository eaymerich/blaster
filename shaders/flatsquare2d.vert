#version 100
precision highp float;

uniform vec2 uSize;
uniform vec2 uOffset;

attribute vec3 aPosition;

void main() {
    vec3 scaled = aPosition * vec3(uSize, 1.0);
    vec3 offseted = scaled + vec3(uOffset, 0.0);
    gl_Position = vec4(offseted, 1.0);
}
