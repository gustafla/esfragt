// Copyright 2014, 2015 Lauri Gustafsson
/*
This file is part of esfragt.

    esfragt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    esfragt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with esfragt, see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef GL_ES
	precision highp float;
#endif

uniform float iGlobalTime;
uniform vec2 iResolution;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.yy - vec2((iResolution.x/iResolution.y)*0.5, 0.5);
    
    float t = 1.0/sqrt(uv.x*uv.x + uv.y*uv.y);
    float u = atan(uv.y, uv.x)+(iGlobalTime*0.2);
    float v = t+(iGlobalTime*1.6);
    
    vec3 col1 = vec3(1.0, 1.0, 1.0);
    vec3 col2 = vec3(1.0, 0.1, 0.1);
    float l = clamp(((sin(u*8.0) * sin(v*8.0))*1000.0), 0.0, 1.0);

    gl_FragColor = vec4((col2*l+(col1*(1.0-l))), 0.33);
}
