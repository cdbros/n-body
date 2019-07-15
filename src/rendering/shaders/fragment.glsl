R"glsl(

#version 410 core

out vec4 frag_color;
in vec2 vpos;
uniform float radius;

void main() {
    float dis = sqrt(dot(vpos, vpos));
    dis = radius - dis;
    dis = max(dis, 0.0f);
    dis = ceil(dis / radius);
    frag_color = vec4(1.0f, 1.0f, 1.0f, dis);
}

)glsl"
