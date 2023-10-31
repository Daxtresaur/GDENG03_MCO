#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"

class PixelShader
{
public:

	PixelShader();
	void release();
	~PixelShader();

	ID3D11PixelShader* getShader();


private:

	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11PixelShader* m_ps;

	friend class GraphicsEngine;
	friend class DeviceContext;
};
