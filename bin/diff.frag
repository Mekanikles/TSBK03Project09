//
// Fragment shader for Gooch shading
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
    vec3 norm = normalize(normal);
    float diff = max(0.4, dot(light, norm) * 1.5 + 0.3);

    //gl_FragColor = vec4(normal, 1);
    gl_FragColor = vec4(diff * color.xyz, color.w);    
}
