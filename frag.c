/*

                                                                          
a:
((B.x)^2 + (B.y)^2 + (B.z)^2)t^2 + 
b:
(2(A.x B.x + A.y B.y + A.z B.z))t + 
c:
(A.x^2 + A.y^2 + A.z^2 - r^2) = 0

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
    const vec4 backcol = vec4(0.f,0.f,0.f,0.f);
    
    vec3 spherepos = vec3(0.0f ,0.0f ,2.0f);
    vec3 spherecol = vec3(0.f,1.f,1.f);
    

    float radius = 1.0f;
    vec3 rayDir = vec3(pix.x, pix.y , 1.0f);
    //campos
    vec3 rayOrigin = vec3(0.f, 0.0f, 0.f);
    
    float a = dot(rayDir, rayDir); //constant 
    float b = 2.0f * dot(rayOrigin - spherepos, rayDir); //differs for each sphere 
    float c = dot(rayOrigin - spherepos,rayOrigin - spherepos) - radius * radius; //differs for each sphere
    
    float discriminant = b * b - 4.0f * a * c;

    
    if (discriminant >= 0.f)
    {
        float t0 = -b - (sqrt((discriminant) / 2.0f*a));

        vec3 hitpoint = rayOrigin + rayDir * t0;

        fragColor = vec4(hitpoint, 1.f);
        
        return;
    }
    fragColor = (backcol);
    
}
