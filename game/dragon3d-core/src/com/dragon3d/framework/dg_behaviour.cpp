#include "dg_behaviour.h"


DGBehaviour::DGBehaviour(void)
{
}


DGBehaviour::~DGBehaviour(void)
{
}


void DGBehaviour::init(DGGameObject* gameObject, DGContext* ctx){
    DGComponent::init(gameObject, ctx);
    start();
}

void DGBehaviour::start(){

}

void DGBehaviour::update(DGContext* ctx){
    DGComponent::update(ctx);

}

void DGBehaviour::draw(DGContext* ctx){
    DGComponent::draw(ctx);
}

void DGBehaviour::destroy(){
    DGComponent::destroy();
}
