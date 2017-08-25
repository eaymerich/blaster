#version 100

uniform vec2 uScale;
uniform vec3 uPositionOffset;

attribute vec3 aPosition;
attribute vec2 aTextureCoordinate;

varying vec2 vTextureCoordinate;

void main() {
    vTextureCoordinate = aTextureCoordinate;
    vec3 position = vec3(aPosition.xy * uScale, aPosition.z) + uPositionOffset;
    gl_Position = vec4(position, 1.0);
}
