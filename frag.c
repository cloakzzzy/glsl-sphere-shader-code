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

conditions:
if ray hits red sphere
if ray hits blue sphere
if ray hits both blue and red sphere

*/


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 pix = fragCoord/iResolution.xy * 2.0 - 1.0;
    float aspectratio = iResolution.x / iResolution.y;
    pix.x *= aspectratio;
    const vec4 backcol = vec4(0.f,0.f,0.f,0.f);
    
    vec3 spherepos [] = vec3[](vec3(6.f,0.f,10.f), vec3(0.0f ,0.0f ,2.0f));
    vec3 spherecol []= vec3[](vec3(0.f,1.f,1.f), vec3(1.f,0.f,0.f));
    //                            blue                   red
    float t [] = float[](0.f);
    
    float radius = 1.0f;
    vec3 rayDir = vec3(pix.x, pix.y , 1.0f);
    vec3 rayOrigin = vec3(1.f, 1.0f, 0.f);
    /*
    float a = dot(rayDir, rayDir); //constant 
    
    for (int i = 0; i < spherepos.length(); i++)
    {
        float b = 2.0f * dot(rayOrigin - spherepos[i], rayDir); 
        float c = dot(rayOrigin - spherepos[i],rayOrigin - spherepos[i]) - radius * radius;
        
        float discriminant = b * b - 4.0f * a * c;
        
        if (discriminant >= 0.f)
        {
            t[i] = -b - (sqrt((discriminant) / 2.0f*a));
        }
        else
        {
            t[i] = 1000000000.0f;
        }
    }
    
    int ind;
    float minimum;
    
    for (int i = 0; i < t.length(); i++)
    {
    
        if (i == 0)
        {
            minimum = t[i];
        }
        if (t[i] < minimum)
        {
            minimum = t[i];
            ind = i;
        }
    }
  
    
    fragColor = vec4(spherecol[ind], 1.f);
    */
    
    
    float a = dot(rayDir, rayDir); //constant 
    float b = 2.0f * dot(rayOrigin - spherepos[0], rayDir); //differs for each sphere 
    float c = dot(rayOrigin - spherepos[0],rayOrigin - spherepos[0]) - radius * radius; //differs for each sphere
    
    float discriminant = b * b - 4.0f * a * c;
    //float t0 = 10000000.0f;
    float t0;
    float t1;
    
    //blue sphere contact
    if (discriminant >= 0.f)
    {
        
        t0 = -b - (sqrt((discriminant) / 2.0f*a));
        //fragColor = vec4(t0-round(t0));
    }
    else
    {
        t0 = 1000000000.0f;
    }
    
    float b2 = 2.0f * dot(rayOrigin - spherepos[1], rayDir); //differs for each sphere 
    float c2 = dot(rayOrigin - spherepos[1],rayOrigin - spherepos[1]) - radius * radius; //differs for each sphere
    
    float discriminant2 = b2 * b2 - 4.0f * a * c2; 

    //red sphere contact
    if (discriminant2 >= 0.f)
    {
        
        t1 = -b2 - (sqrt((discriminant2) / 2.0f*a));
    }
    else
    {
        t1 = 1000000000.0f;
    }
   
    
    ///if blue is before red
    if (t0 < t1)
    {
        
        fragColor = vec4(spherecol[0], 1.f);   
    }
    //red is before blue
    else if(t0 > t1)
    {
        fragColor = vec4(spherecol[1], 1.f);
    }
    
    
    
    
}
