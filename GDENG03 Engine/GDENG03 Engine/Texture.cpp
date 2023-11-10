#include "Texture.h"

#include <DirectXTex.h>
#include "AGraphicsEngine.h"
#include "iostream"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif


Texture::Texture(const wchar_t* full_path)
{
	std::wstring file_path = std::experimental::filesystem::absolute(full_path);

	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(file_path.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		std::cout << "Success Step 1" << std::endl;
		std::wcout << L"Successfully loaded texture from '" << file_path.c_str() << std::endl;

		res = DirectX::CreateTexture(AGraphicsEngine::getInstance()->getD3DDevice(), image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		if (SUCCEEDED(res))
		{
			std::cout << "Success Step 2" << std::endl;

			D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
			desc.Format = image_data.GetMetadata().format;
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
			desc.Texture2D.MostDetailedMip = 0;

			res = AGraphicsEngine::getInstance()->getD3DDevice()->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);

		}
		else
		{
			std::cout << "Failed Step 2" << std::endl;
		}
	}
	else
	{
		std::cout << "Failed Step 1" << std::endl;
		std::wcout << L"Failed to load texture from '" << file_path.c_str() << std::endl;
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
	m_shader_res_view->Release();
	m_texture->Release();
}
