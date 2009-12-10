//
// Vertex shader for Gooch shading
//
// Author: Randi Rost
//
// Copyright (c) 2002-2005 3Dlabs Inc. Ltd. 
//
// See 3Dlabs-License.txt for license information

void main()
{
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position     = ftransform() + 1.0 * vec4(tnorm.x, tnorm.y, 0 ,0);
}