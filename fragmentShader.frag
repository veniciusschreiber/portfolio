#version 330 core

in vec3 coresOut;
out vec4 FragColor;


void main(){
FragColor = vec4(coresOut.x, coresOut.y, coresOut.z, 0.0f);}


