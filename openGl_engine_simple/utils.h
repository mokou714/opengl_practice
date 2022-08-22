#pragma once
#include <vector>
#include <map>
#include "deviceCommon.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "glHelper.h"

namespace simple_engine {

	namespace Utils {

		// Very, VERY simple OBJ loader.
		// Here is a short list of features a real function would provide : 
		// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
		// - Animations & bones (includes bones weights)
		// - Multiple UVs
		// - All attributes should be optional, not "forced"
		// - More stable. Change a line in the OBJ file and it crashes.
		// - More secure. Change another line and you can inject code.
		// - Loading from memory, stream, etc

		extern bool loadOBJ(
			const char* path,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals
		);

		// Returns true iif v1 can be considered equal to v2
		inline bool is_near(float v1, float v2) {
			return fabs(v1 - v2) < 0.01f;
		}

		// Searches through all already-exported vertices
		// for a similar one.
		// Similar = same position + same UVs + same normal
		extern bool getSimilarVertexIndex(
			glm::vec3& in_vertex,
			glm::vec2& in_uv,
			glm::vec3& in_normal,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals,
			unsigned short& result
		);

		extern void indexVBO_slow(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals
		);

		struct PackedVertex {
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;
			bool operator<(const PackedVertex that) const;
		};

		extern bool getSimilarVertexIndex_fast(
			PackedVertex& packed,
			std::map<PackedVertex, unsigned short>& VertexToOutIndex,
			unsigned short& result
		);

		extern void indexVBO(
			std::vector<glm::vec3>&& in_vertices,
			std::vector<glm::vec2>&& in_uvs,
			std::vector<glm::vec3>&& in_normals,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals
		);

		extern void indexVBO_TBN(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,
			std::vector<glm::vec3>& in_tangents,
			std::vector<glm::vec3>& in_bitangents,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals,
			std::vector<glm::vec3>& out_tangents,
			std::vector<glm::vec3>& out_bitangents
		);


		// Load a .BMP file using our custom loader
		GLuint loadBMP_custom(const char* imagepath);

		//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
		//// or do it yourself (just like loadBMP_custom and loadDDS)
		//// Load a .TGA file using GLFW's own loader
		//GLuint loadTGA_glfw(const char * imagepath);

		// Load a .DDS file using GLFW's own loader
		GLuint loadDDS(const char* imagepath);
		GLuint createGLTexture(const char*);
		GLuint createCubemap(std::vector<const char*> files);
	}
}
