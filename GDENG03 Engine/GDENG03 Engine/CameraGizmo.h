#pragma once
#include "AConstantBuffer.h"
#include "AGizmo.h"
#include "AVertexBuffer.h"

#include "string"
using namespace std;

class CameraGizmo : public AGizmo
{
public:
	CameraGizmo(std::string name, void* shader_byte_code, size_t shader_size);
	~CameraGizmo();


};

