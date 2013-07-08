#include "dg_renderer.h"


DGRenderer::DGRenderer(void)
{
}


DGRenderer::~DGRenderer(void)
{
}

void DGRenderer::init(DGGameObject* gameObject, DGContext* ctx){
    DGComponent::init(gameObject, ctx);
}

void DGRenderer::update(DGContext* ctx){
    DGComponent::update(ctx);
}

void DGRenderer::draw(DGContext* ctx){
    DGComponent::draw(ctx);
}

void DGRenderer::destroy(){
    DGComponent::destroy();
}
