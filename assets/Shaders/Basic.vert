#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform; // 사각형의 위치/회전/크기를 결정!

out vec2 v_TexCoord;

void main() {
    v_TexCoord = aTexCoord;
    // aPos에 u_Transform을 먼저 곱해줍니다.
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
}