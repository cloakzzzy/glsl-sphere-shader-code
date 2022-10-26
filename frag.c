/*

       a                                b                                    c
       ⬇                                ⬇                                    ⬇

(B.x^2 + B.y^2 + B.z^2)t^2 + (2(A.x B.x + A.y B.y + A.z + B.z))t + (A.x^2 + A.y^2 + A.z^2 - r^2) = 0

P = Bt (can figure out any point along a line)

where:

A = ray origin (vec3)
B = ray direction (vec3)
r = radius (float)
t = hit distance (float)
P = point along ray (vec3)

we need to solve for (t)

Quadratic formula:
-b += sqrt((b^2 - 4*a*c) \ 2a)

*/


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 pix = fragCoord/iResolution.xy * 2.0 - 1.0;
    float aspectratio = iResolution.x / iResolution.y;
    pix.x *= aspectratio;

    float radius = 0.5f;
    vec3 rayDirection = vec3(pix.x, pix.y , 1.0f);
    vec3 rayOrigin = vec3(1.f, 0.f, -2.f);
    vec3 spherecol = vec3(0.f,1.f,1.f);
    
    float a = dot(rayDirection, rayDirection);
    float b = 2.0f * dot(rayOrigin, rayDirection);
    float c = dot(rayOrigin,rayOrigin) - radius * radius;
    
    float discriminant = b * b - 4.0f * a * c;
    
    float t0 = -b + (sqrt((discriminant) / 2.0f*a));
    vec3 hitpoint = rayOrigin + rayDirection * t0;
    
    if (discriminant >= 0.f){
        fragColor = vec4(hitpoint , 1.f);
    }
    
    
}
