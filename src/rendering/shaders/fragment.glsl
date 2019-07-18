R"glsl(

#version 410 core

in vec2 vpos;
in float vradius;

out vec4 frag_color;

void main() {
    float dis = sqrt(dot(vpos, vpos));
    dis = vradius - dis;
    dis = max(dis, 0.0f);
    dis = ceil(dis / vradius);
    frag_color = vec4(1.0f, 1.0f, 1.0f, dis);
}

)glsl"
