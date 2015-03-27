// Copyright 2014 Lauri Gustafsson
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

#define MARCH_PREC 32

uniform highp float iGlobalTime;
uniform lowp vec2 iResolution;

lowp float rand(highp vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

highp float pallo(highp vec3 pos, highp vec3 coord, highp float r){
    return length(pos - coord) - r;
}

highp float scene(highp vec3 pos){
    return min(
        pallo(pos, vec3(0.0, 0.0, (sin(iGlobalTime / 2.0) * 1.5 + 2.0)), 0.8),
        min(
            pallo(pos, vec3((cos(iGlobalTime / 1.1) * 1.8), (sin(iGlobalTime / 1.1) * 1.8), 1.5), 0.5),
            min(
                pallo(pos, vec3((sin(iGlobalTime / 1.4) * 0.6), (cos(iGlobalTime / 1.4) * 1.2), (sin(iGlobalTime / 1.6) * 1.8 + 1.5)), 0.2),
                pallo(pos, vec3((cos(iGlobalTime / 1.4) * 0.6), (sin(iGlobalTime / 1.4) * 1.2), (cos(iGlobalTime / 1.6) * 1.8 + 1.5)), 0.2)
            )
        )
    );
}

highp float march(highp vec3 dir, highp vec3 cam){
    highp vec3 curPos = cam;
    for(highp int i=0; i<MARCH_PREC; i++){
        highp float dist = scene(curPos);
        curPos += dist * dir;
    }
    return length(curPos - cam);
}

void main()
{

    highp float t = iGlobalTime;
    highp vec2 uv = (gl_FragCoord.xy / iResolution.yy - vec2(0.5, 0.5));
    highp vec3 ray = normalize(vec3(uv.x, uv.y, 1.0));
    highp vec3 cam = vec3(0.0, 0.0, -3.0);
    highp float lum = 0.8 / sqrt(march(ray, cam)) * mod(gl_FragCoord.y, 2.0);
    lowp float noise = (rand(uv + iGlobalTime) * 0.034);
    gl_FragColor = vec4((lum * lum + noise), (lum + noise), (lum * 0.8 + noise), 0.4);     //Cyan
//    vec3 rgbCol = vec3(lum + noise); gl_FragColor = vec4(rgbCol, 1.0);                     //B&W
}
