//
// Vertex shader for Gooch shading
//
// Author: Randi Rost
//
// Copyright (c) 2002-2005 3Dlabs Inc. Ltd. 
//
// See 3Dlabs-License.txt for license information
//


varying vec3 normal;
varying vec4 color;
varying vec3 light;
varying vec4 pos;

void main()
{
    //vec3 LightPosition = vec3(gl_ModelViewMatrix*vec4(40.0, 10.0, 40.0, 0.0));
    vec3 LightPosition = vec3(-40.0, 50.0, 40.0);

    vec3 ecPos      = vec3(gl_Vertex);
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec  = normalize(LightPosition - ecPos);
    gl_Position     = ftransform();
    

    color = gl_Color;
    normal = gl_Normal;
    pos = gl_Position;
    light = lightVec;
}
