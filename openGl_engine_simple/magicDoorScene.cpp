#include "magicDoorScene.h"
#include "skybox.h"
#include "plane.h"
#include "noColorMat.h"
#include "cubeObj.h"
#include "PipelineStateObject.h"

using namespace simple_engine;

MagicDoorScene::MagicDoorScene(std::string name, Camera* camera) :
	Scene(name, camera), m_stencil_door(nullptr), world_type(0), world_z_inversed(false)
{
}

bool MagicDoorScene::init() 
{
	if (!Scene::init())
		return false;

	mainCamera->setRotationX(0.0f);
	mainCamera->setPositionY(0.0f);
	mainCamera->setPositionZ(15.f);
	
	m_stencil_door = new GameObject("magic door");
	m_stencil_door->setRotationX(glm::radians(90.f));
	m_stencil_door->setPositionZ(0.0f);
	m_stencil_door->addMesh(Plane());
	m_stencil_door->setMaterial(NoColorMat());
	m_stencil_door->setScale(3.0f);
	m_gameObjects.push_back(m_stencil_door);

	//������pipeline ����alwaysͨ��ģ����� ͨ�����Ժ��refֵд��ģ��
	PipelineStateObject pipeline_state;
	pipeline_state.stencil_test_enable = true;
	pipeline_state.stencil_func = DepthStencilOption::FUNC_ALWAYS;
	pipeline_state.stencil_op_passed = DepthStencilOption::OP_STENCIL_REPLACE;
	pipeline_state.culling_enable = false;
	m_stencil_door->getMaterial().setPipelineState(pipeline_state);
	
	//��պ�ͨ�����Բ��ı�ģ��ֵ
	pipeline_state.stencil_op_passed = DepthStencilOption::OP_STENCIL_KEEP;
	Skybox* skybox_1 = new Skybox("world1", SKYBOX_TYPE::POLLUTED_EARTH);
	Skybox* skybox_2 = new Skybox("world2", SKYBOX_TYPE::ECOSYSTEM);
	m_skyboxs.push_back(skybox_1);
	m_skyboxs.push_back(skybox_2);


	pipeline_state.stencil_op_passed = DepthStencilOption::OP_STENCIL_KEEP;
	//��պ�1 ģ�溯����not equal ��ģ����������ĵط�����
	pipeline_state.stencil_func = DepthStencilOption::FUNC_NOT_EQUAL;
	pipeline_state.depth_test_enable = false;
	skybox_1->getMaterial().setPipelineState(pipeline_state);
	
	//��պ�2 ģ�溯����equal ��ģ�������ڻ���
	//��Ϊ������պ��ص� ��պ�2����ȶԱȺ�����gl_always ��������ͨ����ģ����Ե�δͨ����Ȳ��Ա�����
	pipeline_state.stencil_func = DepthStencilOption::FUNC_EQUAL;
	pipeline_state.depth_test_enable = false;
	skybox_2->getMaterial().setPipelineState(pipeline_state);

	GameObject* box = new CubeObj("box");
	m_gameObjects.push_back(box);
	PipelineStateObject box_state = box->getMaterial().getPipelineState();
	box_state.depth_func = DepthStencilOption::FUNC_GREATER;
	box_state.stencil_test_enable = true;
	box_state.stencil_func = DepthStencilOption::FUNC_EQUAL;
	box->getMaterial().setPipelineState(box_state);

	return true;
}

void MagicDoorScene::render()
{
	if (!inited) {
		CONSOLE_PRINTF("ERROR! render scene before initializing.") 
		return;
	}
	assert(m_skyboxs.size() == 2);
	auto skybox_1 = m_skyboxs[0];
	auto skybox_2 = m_skyboxs[1];

	m_stencil_door->Draw();
	skybox_1->Draw();
	skybox_2->Draw();

	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); ++itr)
	{
		if ((*itr)->getName() == "box")
			(*itr)->Draw();
	}


}

void MagicDoorScene::logic()
{
	Scene::logic();

	auto camera_pos = mainCamera->getPosition();
	auto door_pos = m_stencil_door->getPosition();
	auto door_side = m_stencil_door->getScale();

	if (camera_pos.x > door_pos.x - door_side && camera_pos.x < door_pos.x + door_side )
	{
		if (camera_pos.y > door_pos.y - door_side  && camera_pos.y < door_pos.y + door_side )
		{	
			//��û��z����ĺ��
			int target_type = world_type;
			if (camera_pos.z < door_pos.z)
			{	
				target_type = world_z_inversed ? 0 : 1;
			}
			else if (camera_pos.z > door_pos.z)
			{
				target_type = world_z_inversed ? 1 : 0;
			}
			if (world_type != target_type)
			{
				world_type = target_type;
				updatePipeline();
			}
			
		}
	}

	world_z_inversed = (camera_pos.z > door_pos.z && world_type == 1) || (camera_pos.z < door_pos.z && world_type == 0);

}

void MagicDoorScene::updatePipeline()
{
	assert(m_skyboxs.size() == 2);
	auto skybox_1 = m_skyboxs[0];
	auto skybox_2 = m_skyboxs[1];

	PipelineStateObject state = skybox_1->getMaterial().getPipelineState();
	state.stencil_func = world_type == 0 ? DepthStencilOption::FUNC_NOT_EQUAL : DepthStencilOption::FUNC_EQUAL;
	skybox_1->getMaterial().setPipelineState(state);
	state.stencil_func = world_type == 1 ? DepthStencilOption::FUNC_NOT_EQUAL : DepthStencilOption::FUNC_EQUAL;
	skybox_2->getMaterial().setPipelineState(state);
}