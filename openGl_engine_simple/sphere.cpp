#include "sphere.h"

using namespace simple_engine;

Sphere::Sphere(float radius, int stacks, int sectors): m_radius(radius), m_stacks(stacks), m_sectors(sectors)
{   
    //reference link: http://www.songho.ca/opengl/gl_sphere.html

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * glm::pi<float>() / m_sectors;
    float stackStep = glm::pi<float>() / m_stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= m_stacks; ++i)
    {
        stackAngle = glm::pi<float>() / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= m_sectors; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            m_vertices.push_back(glm::vec3(x,y,z));

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            m_normals.push_back(glm::vec3(nx, ny, nz));

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / m_sectors;
            t = (float)i / m_stacks;
            m_coords.push_back(glm::vec2(s, t));
        }
    }

    //std::vector<int> lineIndices;
    int k1, k2;
    for (int i = 0; i < m_stacks; ++i)
    {
        k1 = i * (m_sectors + 1);     // beginning of current stack
        k2 = k1 + m_sectors + 1;      // beginning of next stack

        for (int j = 0; j < m_sectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                m_indices.push_back(k1);
                m_indices.push_back(k2);
                m_indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (m_stacks - 1))
            {
                m_indices.push_back(k1 + 1);
                m_indices.push_back(k2);
                m_indices.push_back(k2 + 1);
            }

            // store indices for lines
            // vertical lines for all stacks, k1 => k2
            //lineIndices.push_back(k1);
            //lineIndices.push_back(k2);
            //if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
            //{
            //    lineIndices.push_back(k1);
            //    lineIndices.push_back(k1 + 1);
            //}
        }
    }
}
