#pragma once
#include "d3d11.h"

class SwapChain
{
public:
	SwapChain();
	//Initialize SWAPCHAIN for a window
	bool init(HWND hwnd, UINT width, UINT height);
	//Release the swap chain
	bool release();
	~SwapChain();

	bool present(bool vsync);

	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();

private:
	IDXGISwapChain* m_swap_chain;

	ID3D11RenderTargetView* m_render_target_view;
	ID3D11DepthStencilView* m_depth_stencil_view;

	friend class DeviceContext;

};

