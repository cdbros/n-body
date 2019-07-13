R"glsl(

#version 410 core

out vec4 frag_color;
in vec2 vpos;

void main() {
    float dis = sqrt(dot(vpos, vpos));
    dis = 0.5f - dis;
    dis = max(dis, 0.0f);
    dis = ceil(dis / 0.5f);
    frag_color = vec4(1.0f, 1.0f, 1.0f, dis);
}

)glsl"
