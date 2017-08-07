#version 100

attribute vec3 aPosition;
attribute vec2 aTextureCoordinate;

varying vec2 vTextureCoordinate;

void main() {
    vTextureCoordinate = aTextureCoordinate;
    gl_Position = vec4(aPosition, 1.0);
}
