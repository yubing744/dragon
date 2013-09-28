#include "dg_transform.h"


DGTransform::DGTransform(void) {
	this->position = DGVector3::zero;
	this->rotation = DGQuaternion::identity;
	this->scale = DGVector3::one;

	this->localPosition = DGVector3::zero;
	this->localRotation = DGQuaternion::identity;
	this->localScale = DGVector3::one;
}


DGTransform::~DGTransform(void){

}

void DGTransform::translate(const DGVector3& translation, DGSpace relativeTo){
	if (DGSpace::World == relativeTo) {
		this->position.x += translation.x;
		this->position.y += translation.y;
		this->position.z += translation.z;
	} else if (DGSpace::Self == relativeTo) {
		this->localPosition.x += translation.x;
		this->localPosition.y += translation.y;
		this->localPosition.z += translation.z;
	}
}

void DGTransform::translate(const DGVector3& translation){
	this->translate(translation, DGSpace::Self);
}

void DGTransform::rotate(DGfloat xAngle, DGfloat yAngle, DGfloat zAngle, DGSpace relativeTo){
	if (DGSpace::World == relativeTo) {
		this->rotation.x += xAngle;
		this->rotation.y += yAngle;
		this->rotation.z += zAngle;
	} else if (DGSpace::Self == relativeTo) {
		this->localRotation.x += xAngle;
		this->localRotation.y += yAngle;
		this->localRotation.z += zAngle;
	}
}

void DGTransform::rotate(DGfloat xAngle, DGfloat yAngle, DGfloat zAngle){
	this->rotate(xAngle, yAngle, zAngle, DGSpace::Self);
}

void DGTransform::rotate(const DGVector3& eulerAngles, DGSpace relativeTo){
	this->rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z, relativeTo);
}

void DGTransform::rotate(const DGVector3& eulerAngles){
	this->rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z, DGSpace::Self);
}

