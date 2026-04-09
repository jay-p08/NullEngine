#version 450 core
out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color; // 색상 조절 변수 추가!

void main() {
    // 텍스처 색상에 u_Color를 곱합니다. (일반 색상 사각형을 그릴 때 유용함)
    FragColor = texture(u_Texture, v_TexCoord) * u_Color; 
}