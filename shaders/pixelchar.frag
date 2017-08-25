#version 100
precision mediump float;

uniform sampler2D uTextureUnit;
uniform vec2 uTextureOffset;
uniform vec4 uForegroundColor;
uniform vec4 uBackgroundColor;

varying vec2 vTextureCoordinate;

void main() {
    vec4 alpha = texture2D(uTextureUnit,
                           (vTextureCoordinate + uTextureOffset));
    gl_FragColor = mix(uBackgroundColor, uForegroundColor, alpha.a);
}
