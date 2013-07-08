#include "dg_application.h"

#include "dg_game.h"
#include "dg_engine.h"
#include "dg_mesh_renderer.h"
#include "dg_cuboid.h"
#include "dg_behaviour.h"
#include "dg_script_behaviour.h"
#include "dg_first_person_controller.h"

#include "dg_texture.h"
#include "dg_material.h"

class DGCuboidBehaviour
    :public DGBehaviour {
public:
    DGCuboidBehaviour(){
		this->log = DGPlatform::getCurrent()->getLogger("dg_cuboid_behaviour_lib");
        this->angle = 45.0f;
    };

public:
    virtual void update(DGContext* ctx){
        transform->rotate(ctx->getFrameInterval() * 40.0f, ctx->getFrameInterval() * 40.0f, ctx->getFrameInterval() * 40.0f, DGSpace::World);
		//transform->rotate(0, ctx->getFrameInterval() * 40.0f, 0);
		
		//angle += (ctx->getFrameInterval() * 40.0f);
		//if(angle >= 360.0f) {
		//	angle -= 360.0f;
		//}

		//log->debug(transform->rotation.toString().data());
    };

public:
    DGfloat angle;
	DGLog* log;
};


DGCuboid* cuboid = NULL;
DGFirstPersonController* personController = NULL;
DGTexture* texture = NULL;
DGMaterial* material = NULL;

void DGApplication::startup(DGEngine* engine){

	DGScene* scene = engine->createScene();

	DGFirstPersonController person;

	texture = new DGTexture("Textures/basemap.tga");
	material = new DGMaterial(DGColor::white, texture);

	cuboid = new DGCuboid();
	cuboid->setMaterial(material);

	//Setup Camera
	personController = new DGFirstPersonController();
	scene->addChild(personController);

	//cuboid->setColor(DGColor(0.0f, 1.0f, 0.0f));

    DGGameObject* clue = new DGGameObject();
    clue->addComponent(cuboid);
    clue->addComponent(new DGCuboidBehaviour());
    clue->transform->position = DGVector3(-1, 0.5f, -6.0f);
    scene->addChild(clue);

    DGGameObject* clue2 = new DGGameObject();
    clue2->addComponent(cuboid);
    clue2->addComponent(new DGScriptBehaviour());
    clue2->transform->position = DGVector3(1, 0.5f, -6.0f);
    scene->addChild(clue2);

	// Load Model
	DGModelManager* modelManager = engine->getModelManager();
	DGModel* testModel = modelManager->loadModel("Data/model/tire.3ds");
	testModel->addComponent(new DGCuboidBehaviour());

	testModel->transform->localScale = DGVector3(0.001f, 0.001f, 0.001f);
	testModel->transform->localPosition = DGVector3(0, 1.0f, 1.0f);
	testModel->transform->rotate(-90, 0, 180);

	if (testModel != NULL) {
		scene->addChild(testModel);
	}
}

void DGApplication::end(DGEngine* engine) {
	dgDelete(cuboid);
	dgDelete(personController);
	//dgDelete(texture);
	//dgDelete(material);
}
