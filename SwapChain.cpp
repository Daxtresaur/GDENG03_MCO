#include "SwapChain.h"

#include <iostream>

#include "GraphicsEngine.h"
#include "Utilities.h"

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1; // Make sure to set this to 1. 
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	//Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);
	
	if (FAILED(hr))
	{
		return false;
	}

	//Get the back buffer color and create its render target view
	//--------------------------------
	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		return false;
	}

	m_render_target_view = nullptr;
	hr = device->CreateRenderTargetView(buffer, NULL, &m_render_target_view);
	if (FAILED(hr))
	{
		return false;
	}
	buffer->Release();

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;

	buffer = nullptr;
	HRESULT depthTexHr = device->CreateTexture2D(&texDesc, NULL, &buffer);
	Utilities::PrintHResult("SwapChain Depth Stencil Texture Creation: ", depthTexHr);

	HRESULT depthStencilHr = device->CreateDepthStencilView(buffer, NULL, &this->m_depth_stencil_view);
	Utilities::PrintHResult("SwapChain Depth Stencil View Creation: ", depthStencilHr);
	buffer->Release();

	return true;
}

bool SwapChain::present(bool vsync)
{
	HRESULT res = m_swap_chain->Present(vsync, NULL);
	if (FAILED(res))
		return false;

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

ID3D11RenderTargetView* SwapChain::getRenderTargetView()
{
	return m_render_target_view;
}

ID3D11DepthStencilView* SwapChain::getDepthStencilView()
{
	return m_depth_stencil_view;
}

SwapChain::~SwapChain()
{
}