#pragma once
#include <string>
#include <vector>
#include "mesh.h"
#include "material.h"
#include "PipelineStateObject.h"

namespace simple_engine {
	/*
	* 场景中可放置的最基本单位，由子类派生具体实现
	*/
	class GameObject {
	public:
		GameObject(std::string name);
		virtual void Update();
		virtual void Draw();
		void addMesh(Mesh mesh);

		void HandleInputTranslation(const glm::vec3& deltaTranslation);
		void HandleInputRotation(const glm::vec3& deltaRotation);

		std::string getName() { return m_name; };
		glm::vec3 getPosition() { return m_position; }
		glm::quat getRotation() { return m_rotation; }
		float getScale() { return m_scale; }
		glm::mat4 getModelMatrix();
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		glm::mat4 getModelViewMatrix();
		glm::mat4 getModelViewProjectionMatrix();
		glm::vec4 getForward();	//local -z 方向
		glm::vec4 getRight(); //local x 方向
		glm::vec4 getUp(); //local y 方向
		const Mesh& getSubMesh(int index) { return m_meshes[index]; }
		Material& getMaterial() { return m_material; }
		PipelineStateObject getPipelineState() { return m_pipeline_state; }

		void setPositionX(float x) { m_position.x = x; }
		void setPositionY(float y) { m_position.y = y; }
		void setPositionZ(float z) { m_position.z = z; }
		void setPosition(glm::vec3 pos) { m_position = pos; }
		void setScale(float scale) { m_scale = scale; }
		void setRotation(glm::quat rotation) { m_rotation = rotation; }
		void setRotationX(float angle);
		void setRotationY(float angle);
		void setRotationZ(float angle);
		void setMaterial(Material mat) { m_material = mat; }
		void setPipelineState(PipelineStateObject state) { m_pipeline_state = state; }

	protected:
		std::string m_name;
		std::vector<Mesh> m_meshes;
		Material m_material;	// todo 每个mesh对应一种material
		PipelineStateObject m_pipeline_state;
		glm::vec3 m_position;
		glm::quat m_rotation; // x:pitch y:yaw z:roll
		float m_scale;
		glm::vec3 m_inputDeltaTranslation;
		glm::quat m_inputDeltaRotation;

		virtual void limitRotation() {};
		virtual void limitTranslation() {};
	};


}