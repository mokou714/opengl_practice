#include "textureWithDepthScene.h"
#include "planeObj.h"
#include "cubeObj.h"
#include "depthTextureMat.h"
#include "displacementTexMat.h"
#include "interiorMappingMat.h"

using namespace simple_engine;

TextureWithDepthScene::TextureWithDepthScene(std::string name, Camera* camera) : Scene(name, camera)
{
	camera->setRotationX(glm::radians(-70.0f));
	camera->setPositionZ(50.0f);
	camera->setPositionY(120.0f);
}

bool TextureWithDepthScene::init()
{
	if (!Scene::init())
		return false;
	
	//GameObject* plane = new PlaneObj("Depth Plane");
	//plane->setScale(50);
	//DepthTextureMat mat = DepthTextureMat();
	////mat.setTextureFile("interior_tex0", "textures/interior/interior_1.jpg");
	//mat.setUniform3f("model_center_pos", plane->getPosition());	// 默认plane为静止不动物体
	//mat.setUniform1f("texture_world_size", plane->getScale() * ((Plane&)(plane->getSubMesh(0))).getSideSize()) ;
	//plane->setMaterial(mat);
	//m_gameObjects.push_back(plane);

	//GameObject* cube = new CubeObj("Building with interior tex");
	//cube->setScale(30);
	//cube->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//InteriorMappingMat mat2 = InteriorMappingMat();
	//float scaled_side_size = cube->getScale() * ((Cube&)(cube->getSubMesh(0))).getSideSize();
	//glm::mat4 model_mat = cube->getModelMatrix();
	//mat2.setTextureFile("interior_tex0", "textures/interior/interior_1.jpg");
	//mat2.setTextureFile("interior_tex1", "textures/interior/interior_2.jpg");
	//mat2.setTextureFile("tex_top", "textures/cubemap/calm_sea/calm_sea_up.jpg");
	//mat2.setTextureFile("tex_down", "textures/cubemap/calm_sea/calm_sea_dn.jpg");
	//mat2.setTextureFile("tex_left", "textures/cubemap/calm_sea/calm_sea_lf.jpg");
	//mat2.setTextureFile("tex_right", "textures/cubemap/calm_sea/calm_sea_rt.jpg");
	//mat2.setTextureFile("tex_back", "textures/cubemap/calm_sea/calm_sea_bk.jpg");
	////Plane = <N, D>, D = -N.P
	//mat2.addBackWall(vec4(0.0f, 0.0f, 1.0f, 1.0f), model_mat);
	//mat2.addBackWall(vec4(0.0f, 0.0f, 1.0f, -1.0f), model_mat);

	//mat2.addCeiling(vec4(0.0f, 1.0f, 0.0f, -1.0f), model_mat);
	//mat2.addCeiling(vec4(0.0f, 1.0f, 0.0f, 0.0f), model_mat);
	//mat2.addCeiling(vec4(0.0f, 1.0f, 0.0f, 1.0f), model_mat);

	//mat2.addSideWall(vec4(1.0f, 0.0f, 0.0f, -1.0f), model_mat);
	//mat2.addSideWall(vec4(1.0f, 0.0f, 0.0f, 0.0f), model_mat);
	//mat2.addSideWall(vec4(1.0f, 0.0f, 0.0f, 1.0f), model_mat);

	//mat2.setUniform1f("side_size", scaled_side_size);
	//mat2.setUniform3f("model_local_x_dir", glm::normalize(glm::vec3((cube->getModelMatrix() * glm::vec4(1.0, 0.0, 0.0, 0.0)))));
	//mat2.setUniform3f("model_local_y_dir", glm::normalize(glm::vec3((cube->getModelMatrix() * glm::vec4(0.0, 1.0, 0.0, 0.0)))));
	//mat2.setUniform3f("model_local_z_dir", glm::normalize(glm::vec3((cube->getModelMatrix() * glm::vec4(0.0, 0.0, 1.0, 0.0)))));
	//mat2.setUniform3f("model_center_pos", glm::vec3(model_mat * glm::vec4(cube->getPosition(),0.0)));
	//cube->setMaterial(mat2);
	//m_gameObjects.push_back(cube);

	GameObject* plane = new PlaneObj("Depth Plane");
	plane->setScale(50);
	DisplacementTexMat mat = DisplacementTexMat();
	float scaled_side_size = plane->getScale() * ((Plane&)(plane->getSubMesh(0))).getSideSize();
	mat.setTextureFile("base_color", "textures/stylized_stone/base.jpg");
	mat.setTextureFile("normal_tex", "textures/stylized_stone/normal.jpg");
	mat.setTextureFile("height_tex", "textures/stylized_stone/height.jpg");
	mat.setUniform3f("light_dir", glm::normalize(glm::vec3(0.1, -1.0, 0.1)));
	plane->setMaterial(mat);
	m_gameObjects.push_back(plane);

	return true;
}