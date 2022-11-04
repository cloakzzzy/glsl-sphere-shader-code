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
(-b += sqrt(b^2 - 4*a*c)) / 2a

rotation:
point.x = (px * cos(deg * RAD)) - (py * sin(deg * RAD)) + cx; 
point.z = (px * sin(deg * RAD)) + (py * cos(deg * RAD)) + cy;

*/

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 pix = fragCoord/iResolution.xy * 2.0 - 1.0;
    float aspectratio = iResolution.x / iResolution.y;
    pix.x *= aspectratio;
    
    const vec3 backcol = vec3(0.f,0.f,0.f);
    
    float RAD = 3.14159f/180.0f;
    
    //float deg = iMouse.x / 5.0f;
    float deg = 0.0f;
    
    vec3 rayOrigin = vec3(0.0f, 1.0f, -2.f);
    
    float radius [] = float[](
    100.f,
    2.f
    );
    //vec3 spherepos [] = vec3[](vec3(3.f,0.f,5.f), vec3(0.0f ,0.0f ,2.0f),vec3( 0.5,0.5,5.f));
    //vec3 spherecol []= vec3[](vec3(0.0f,0.f,1.f), vec3(1.f,0.f,0.f), vec3(0.f,1.f,0.f));
     //                           blue                   red                green
     
    vec3 spherepos [] = vec3[](
    vec3(0.f,-100.f,-2.f),
    vec3(0.f, 2.0f, 4.f)
    );
    
    vec3 spherecol [] = vec3[](
    vec3(1.f, 0.f, 0.f),
    vec3(0.f, 0.f,1.f)
    );
    
    
    vec3 rayDir = vec3(pix.x, pix.y , 1.f);
    
    float a = dot(rayDir, rayDir); //constant
    
    float t [spherepos.length()];
    
    for (int i = 0; i < spherepos.length(); i++)
    {
        //rotation around the xz axis
        //spherepos[i].x = ((spherepos[i].x - rayOrigin.x) * cos(deg * RAD)) - ((spherepos[i].z - rayOrigin.z) * (sin(deg*RAD)) + rayOrigin.x);
        //spherepos[i].z = ((spherepos[i].x - rayOrigin.x) * sin(deg * RAD)) + ((spherepos[i].z - rayOrigin.z) * (cos(deg*RAD)) + rayOrigin.x);
    
  
        float b = 2.0f * dot(rayOrigin - spherepos[i], rayDir);
        float c = dot(rayOrigin - spherepos[i], rayOrigin - spherepos[i]) - radius[i] * radius[i];
        
        float discriminant = b * b - 4.0f * a * c;
        
        if (discriminant >= 0.f)
        {
            t[i] =(-b - sqrt(discriminant)) / (2.0f * a);
        }
        else
        {
            t[i] = 1000000000.0f;
        }
        
    }
    
    int ind = 0;
    float minimum;
    
    bool eq = true;
    
    //only one element 
    if (t.length() == 1 && t[0] != 1000000000.0f && t[0] > 0.f && t[0] > 0.f)
    {
        fragColor = vec4(spherecol[0], 1.f);
        return;
    }
    else if (t.length() == 1 && t[0] == 1000000000.0f)
    {
        fragColor = vec4(backcol, 1.f);
        return;
    }
    
    
    
    //if there are no intersections make it black ( if all values in t array are the same
    for (int i = 0 ; i < t.length(); i++)
    {
         //if values are not the same 'eq' = false and break the loop
         if (t[i] != t[0]) {eq = false; break;}
    }
    
    // if no intersections
    if (eq == true)
    {
        //if no intersection then make the pixel equal to the backcolor
        fragColor = vec4(backcol, 1.f);
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
    
    if (t[ind] > 0.0f)
    {
        fragColor = vec4(vec3(spherecol[ind]), 1.f);
        return;
    }
    
    //fragColor = vec4(backcol,1.f);
    //fragColor = vec4(vec3(rayOrigin * t[ind] - round(rayOrigin * t[ind])), 1.f);
}
