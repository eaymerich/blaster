#version 100
precision mediump float;

uniform sampler2D uTextureUnit;

varying vec2 vTextureCoordinate;

void main() {
    gl_FragColor = texture2D(uTextureUnit, vTextureCoordinate);
}
