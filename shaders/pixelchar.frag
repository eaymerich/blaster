#version 100
precision mediump float;

uniform sampler2D uTextureUnit;

varying vec2 vTextureCoordinate;

void main() {
    vec4 alpha = texture2D(uTextureUnit, vTextureCoordinate);
    gl_FragColor = vec4(alpha.a, alpha.a, alpha.a, 1.0);
}
