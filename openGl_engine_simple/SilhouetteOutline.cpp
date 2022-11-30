#include "SilhouetteOutline.h"

using namespace simple_engine;

void Tech_Silhouette::Draw(GameObject* obj)
{
	PipelineStateObject& pipelineState = obj->getMaterial().getPipelineState();
	//pipelineState.culling_mode = CullOption::CULL_FACE_FRONT;
	//obj->getMaterial().setUniform1f("back_face_pass", 1.0f);
	//obj->Draw();
	//pipelineState.culling_mode = CullOption::CULL_FACE_BACK;
	//obj->getMaterial().setUniform1f("back_face_pass", 0.0f);
	//obj->Draw();

	obj->getMaterial().setUniform1f("back_face_pass", 0.0f);
	obj->getMaterial().setUniform1f("use_normal2", 0.0f);
	obj->getMaterial().setUniform1f("no_color", 0.0f);
	obj->Draw();
	
	obj->getMaterial().setUniform1f("back_face_pass", 1.0f);
	obj->getMaterial().setUniform1f("use_normal2", 0.0f);
	obj->getMaterial().setUniform1f("no_color", 1.0f);
	obj->Draw();

	obj->getMaterial().setUniform1f("back_face_pass", 1.0f);
	obj->getMaterial().setUniform1f("use_normal2", 1.0f);
	obj->getMaterial().setUniform1f("no_color", 0.0f);
	obj->Draw();

}