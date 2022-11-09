/*

                                                                          
a:
((B.x)^2 + (B.y)^2 + (B.z)^2)t^2 + 
b:
(2(A.x B.x + A.y B.y + A.z B.z))t + 
c:
(A.x^2 + A.y^2 + A.z^2 - r^2) = 0

P = A + Bt (can figure out any point along a line)

where:

A = ray origin (vec3)
B = ray direction (vec3)
r = radius (float)
t = hit distance (float)
P = point along ray (vec3)

we need to solve for (t)

Quadratic formula:
(-b +- sqrt(b^2 - 4*a*c)) / 2a

rotation:
point.x = (px * cos(deg * RAD)) - (py * sin(deg * RAD)) + cx; 
point.z = (px * sin(deg * RAD)) + (py * cos(deg * RAD)) + cy;

rotation around the xz axis:
spherepos[i].x = ((spherepos[i].x - rayOrigin.x) * cos(deg * RAD)) - ((spherepos[i].z - rayOrigin.z) * (sin(deg*RAD)) + rayOrigin.x);
spherepos[i].z = ((spherepos[i].x - rayOrigin.x) * sin(deg * RAD)) + ((spherepos[i].z - rayOrigin.z) * (cos(deg*RAD)) + rayOrigin.x);
    

*/


struct Sphere
{
  float radius;
  vec3 position;
  vec3 colour;
  
};


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{


    vec2 pix = fragCoord/iResolution.xy * 2.0 - 1.0;
    float aspectratio = iResolution.x / iResolution.y;
    pix.x *= aspectratio;
    
    Sphere spheres [] = Sphere[](
        Sphere(2.f, vec3(3.f, 2.f, 7.f), vec3(0.f,0.f,1.f)),// blue
        Sphere(2.f, vec3(5.f, 2.f, 4.f), vec3(0.f, 1.f, 0.f)),//green
        Sphere(1000000.f, vec3(0.f, -1000000.f, -2.f), vec3(0.51, 0.52, 0.53)),//plane
        Sphere(1.f, vec3(-15.f, 8.f, 10.f), vec3(0.85,0.65,0.13))//lightsource
        
    );
    
    const vec3 backcol = vec3(0.f,0.f,0.f);
    
    const float bignum = 10000000000000.0f;
    
    float RAD = 3.14159f/180.0f;
    
    //float deg = iMouse.x / 5.0f;
    float deg = 0.0f;
    
    vec3 rayOrigin = vec3(0.0f, 1.f, -2.f);
    
    
    vec3 rayDir = vec3(pix.x, pix.y ,1.f);
    
    float a = dot(rayDir, rayDir); //constant
    
    float t [spheres.length()];
    bool intersection = false;
    
    for (int i = 0; i < spheres.length(); i++)
    {
        float b = 2.0f * dot(rayOrigin - spheres[i].position, rayDir);
        float c = dot(rayOrigin - spheres[i].position, rayOrigin - spheres[i].position) - spheres[i].radius * spheres[i].radius;
        
        float discriminant = b * b - 4.0f * a * c;
        float t0 =(-b - sqrt(discriminant)) / (2.0f * a);
        
        if (discriminant >= 0.f && t0 >= 0.f )
        { 
            intersection = true;
            t[i] = t0;
        }
        else
        {
            t[i] = bignum;
        }
    
    }
    
    int ind = 0;
    float minimum;
    
    //no intersection
    if (intersection == false)
    {
        fragColor = vec4(backcol,1.f);
        return;
    }
    
    
    //only one element
    
    //intersection
    if (spheres.length() == 1)
    {
        fragColor = vec4(spheres[0].colour, 1.f);
        return;
    }
    
    //finding the smallest value in t array and storing that index in the 'ind' variable
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
    
    //setting the fragColor to that color
    
    fragColor = vec4(vec3(spheres[ind].colour), 1.f);
    
   
    
    
    //fragColor = vec4(vec3(t[ind]- floor(t[ind])),1.f);
    //fragColor = vec4(vec3(rayOrigin + rayDir * t[ind] - floor(rayOrigin + rayDir * t[ind])), 1.f);
}
