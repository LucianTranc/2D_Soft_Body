#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 ourColor;
out vec2 res;
out vec2 centerPos;
out float radius;

uniform mat4 MVP;
uniform vec3 color;
uniform vec2 resolution;
uniform vec2 center;
uniform float uRadius;
void main()
{

    gl_Position = MVP * vec4(aPos, 1.0f);
    ourColor = color;
    res = resolution;
    centerPos = center/resolution;
    radius = uRadius;

}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 res;
in vec2 pos;
in vec2 pointPos;
in vec2 centerPos;
in float radius;

void main()
{
    //position of current pixel
    vec2 st = gl_FragCoord.xy/res.xy;

    float pixelToCenterDistance = 0.0;

    vec2 tC = centerPos-st;
    
    if (res.y > res.x)
    {
        tC.x = tC.x * (res.x/res.y);
    }
    else
    {
        tC.y = tC.y * (res.y/res.x);

    }
    pixelToCenterDistance = sqrt(tC.x*tC.x+tC.y*tC.y);

    float aRadius = 200.0f;

    vec3 color = vec3(1.0);

    if (res.y > res.x)
    {
        if (pixelToCenterDistance > (radius/res.y))
            discard;
        
        color = mix(ourColor.rgb, vec3(0.0), step(radius/res.y, pixelToCenterDistance));
    }
    else
    {
        if (pixelToCenterDistance > (radius/res.x))
            discard;

        color = mix(ourColor.rgb, vec3(0.0), step(radius/res.x, pixelToCenterDistance));
    }

    FragColor = vec4( color, 1.0 );

}