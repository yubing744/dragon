/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/

#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <ppltasks.h>
#include <ppl.h>

#include <com/dragon3d/output/graphics/renderer/DirectX11Renderer.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>

#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;



namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// 在此行中设置断点，以捕获 Win32 API 错误。
			throw Platform::Exception::CreateException(hr);
		}
	}

	// 从二进制文件中执行异步读取操作的函数。
	inline Concurrency::task<Platform::Array<byte>^> ReadDataAsync(Platform::String^ filename)
	{
		using namespace Windows::Storage;
		using namespace Concurrency;
		
		auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
		
		return create_task(folder->GetFileAsync(filename)).then([] (StorageFile^ file) 
		{
			return file->OpenReadAsync();
		}).then([] (Streams::IRandomAccessStreamWithContentType^ stream)
		{
			unsigned int bufferSize = static_cast<unsigned int>(stream->Size);
			auto fileBuffer = ref new Streams::Buffer(bufferSize);
			return stream->ReadAsync(fileBuffer, bufferSize, Streams::InputStreamOptions::None);
		}).then([] (Streams::IBuffer^ fileBuffer) -> Platform::Array<byte>^ 
		{
			auto fileData = ref new Platform::Array<byte>(fileBuffer->Length);
			Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(fileData);
			return fileData;
		});
	}
}

// 为 3D 呈现初始化 DirectX API 的帮助器类。
ref class Direct3DBase abstract
{
internal:
	Direct3DBase();

public:
	virtual void Initialize(Windows::UI::Core::CoreWindow^ window);
	virtual void HandleDeviceLost();
	virtual void CreateDeviceResources();
	virtual void CreateWindowSizeDependentResources();
	virtual void UpdateForWindowSizeChange();
	virtual void ReleaseResourcesForSuspending();
	virtual void Render() = 0;
	virtual void Present();
	virtual float ConvertDipsToPixels(float dips);

public:
	// 用于提起内部的  ID3D11Device1 和 ID3D11DeviceContext1 等
	virtual void ExtractNeedeNativeData(Platform::IntPtr dataPtr);

protected private:
	// Direct3D 对象。
	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	// 缓存的呈现器属性。
	D3D_FEATURE_LEVEL m_featureLevel;
	Windows::Foundation::Size m_renderTargetSize;
	Windows::Foundation::Rect m_windowBounds;
	Platform::Agile<Windows::UI::Core::CoreWindow> m_window;
};


// -----------------------------------------------------------------

struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

struct VertexPositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

// 此类呈现简单的旋转立方体。
ref class SampleRenderer sealed : public Direct3DBase
{
public:
	SampleRenderer();

	// Direct3DBase 方法。
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	
	// 更新时间相关对象的方法。
	void Update(float timeTotal, float timeDelta);

public:
	// 用于提起内部的  ID3D11Device1 和 ID3D11DeviceContext1 等
	virtual void ExtractNeedeNativeData(Platform::IntPtr dataPtr) override;

	virtual bool isLoadingComplete(){return this->m_loadingComplete; }

private:
	bool m_loadingComplete;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	uint32 m_indexCount;
	ModelViewProjectionConstantBuffer m_constantBufferData;

	void* dataPtr;
};


// 构造函数。
Direct3DBase::Direct3DBase()
{
}

// 初始化运行所需的 Direct3D 资源。
void Direct3DBase::Initialize(CoreWindow^ window)
{
	m_window = window;
	
	CreateDeviceResources();
	CreateWindowSizeDependentResources();
}

// 重新创建所有设备资源并将其设置回当前状态。
void Direct3DBase::HandleDeviceLost()
{
	// 重置这些成员变量，以确保 UpdateForWindowSizeChange 重新创建所有资源。
	m_windowBounds.Width = 0;
	m_windowBounds.Height = 0;
	m_swapChain = nullptr;

	CreateDeviceResources();
	UpdateForWindowSizeChange();
}

// 以下是依赖设备的资源。
void Direct3DBase::CreateDeviceResources()
{
	// 此标志为与 API 默认设置具有不同颜色渠道顺序的图面
	// 添加支持。要与 Direct2D 兼容，必须满足此要求。
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	// 如果项目处于调试生成过程中，请通过带有此标志的 SDK 层启用调试。
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 此数组定义此应用程序将支持的 DirectX 硬件功能级别组。
	// 请注意，应保留顺序。
	// 请不要忘记在应用程序的说明中声明其所需的
	// 最低功能级别。除非另行说明，否则假定所有应用程序均支持 9.1。
	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};

	// 创建 Direct3D 11 API 设备对象和对应的上下文。
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr, // 指定 nullptr 以使用默认适配器。
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags, // 设置调试和 Direct2D 兼容性标志。
			featureLevels, // 此应用程序可以支持的功能级别的列表。
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION, // 始终将这设置为 D3D11_SDK_VERSION。
			&device, // 返回创建的 Direct3D 设备。
			&m_featureLevel, // 返回所创建设备的功能级别。
			&context // 返回设备的即时上下文。
			)
		);

	// 获取 Direct3D 11.1 API 设备和上下文接口。
	DX::ThrowIfFailed(
		device.As(&m_d3dDevice)
		);

	DX::ThrowIfFailed(
		context.As(&m_d3dContext)
		);
}

// 分配在依赖于窗口大小的所有内存资源。
void Direct3DBase::CreateWindowSizeDependentResources()
{
	m_windowBounds = m_window->Bounds;

	// 计算必要的交换链并呈现目标大小(以像素为单位)。
	m_renderTargetSize.Width = ConvertDipsToPixels(m_windowBounds.Width);
	m_renderTargetSize.Height = ConvertDipsToPixels(m_windowBounds.Height);

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
	swapChainDesc.Width = static_cast<UINT>(m_renderTargetSize.Width); // 匹配窗口的大小。
	swapChainDesc.Height = static_cast<UINT>(m_renderTargetSize.Height);
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // 这是最常用的交换链格式。
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1; // 请不要使用多采样。
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1; // 在手机上，仅支持单缓冲。
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH; // 在手机上，仅允许拉伸和纵横比拉伸缩放。
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 在手机上，不支持交换效果。
	swapChainDesc.Flags = 0;

	ComPtr<IDXGIDevice1> dxgiDevice;
	DX::ThrowIfFailed(
		m_d3dDevice.As(&dxgiDevice)
		);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	DX::ThrowIfFailed(
		dxgiDevice->GetAdapter(&dxgiAdapter)
		);

	ComPtr<IDXGIFactory2> dxgiFactory;
	DX::ThrowIfFailed(
		dxgiAdapter->GetParent(
			__uuidof(IDXGIFactory2), 
			&dxgiFactory
			)
		);

	Windows::UI::Core::CoreWindow^ window = m_window.Get();
	DX::ThrowIfFailed(
		dxgiFactory->CreateSwapChainForCoreWindow(
			m_d3dDevice.Get(),
			reinterpret_cast<IUnknown*>(window),
			&swapChainDesc,
			nullptr, // 在所有显示中都允许。
			&m_swapChain
			)
		);
		
	// 确保 DXGI 不会一次对多个帧排队。这样既可以减小延迟，
	// 又可以确保应用程序将只在每个 VSync 之后呈现，从而最大程度地降低功率消耗。
	DX::ThrowIfFailed(
		dxgiDevice->SetMaximumFrameLatency(1)
		);

	// 创建交换链后台缓冲区的呈现目标视图。
	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			&backBuffer
			)
		);

	DX::ThrowIfFailed(
		m_d3dDevice->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			&m_renderTargetView
			)
		);

	// 创建深度模具视图。
	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		static_cast<UINT>(m_renderTargetSize.Width),
		static_cast<UINT>(m_renderTargetSize.Height),
		1,
		1,
		D3D11_BIND_DEPTH_STENCIL
		);

	ComPtr<ID3D11Texture2D> depthStencil;
	DX::ThrowIfFailed(
		m_d3dDevice->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&depthStencil
			)
		);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	DX::ThrowIfFailed(
		m_d3dDevice->CreateDepthStencilView(
			depthStencil.Get(),
			&depthStencilViewDesc,
			&m_depthStencilView
			)
		);

	// 设置用于确定整个窗口的呈现视区。
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		m_renderTargetSize.Width,
		m_renderTargetSize.Height
		);

	m_d3dContext->RSSetViewports(1, &viewport);
}

// 在 SizeChanged 事件的事件处理程序中调用此方法。
void Direct3DBase::UpdateForWindowSizeChange()
{
	if (m_window->Bounds.Width  != m_windowBounds.Width ||
		m_window->Bounds.Height != m_windowBounds.Height)
	{
		ID3D11RenderTargetView* nullViews[] = {nullptr};
		m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
		m_renderTargetView = nullptr;
		m_depthStencilView = nullptr;
		m_d3dContext->Flush();
		CreateWindowSizeDependentResources();
	}
}

void Direct3DBase::ReleaseResourcesForSuspending()
{
	// 手机应用程序在内存受约束的环境中运行，因此当输入
	// 后台，最好释放占用大量内存的对象，该对象将会
	// 可在重新激活后轻松还原。交换链和后缓冲区是不错的选择
	// 此处，因为它们使用了大量内存，并且可以快速重新初始化。
	m_swapChain = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilView = nullptr;
}

// 用于将最终图像传递给显示器的方法。
void Direct3DBase::Present()
{
	// 第一个参数指示 DXGI 进行阻止直到 VSync，这使应用程序
	// 在下一个 VSync 前进入休眠。这将确保我们不会浪费任何周期呈现将
	// 从不会在屏幕上显示的帧。
	HRESULT hr = m_swapChain->Present(1, 0);

	// 放弃呈现目标的内容。
	// 这是仅在完全覆盖现有内容时
	// 有效的操作。如果使用已更新或滚动矩形，则应将本调用删除。
	m_d3dContext->DiscardView(m_renderTargetView.Get());

	// 放弃深度模具的内容。
	m_d3dContext->DiscardView(m_depthStencilView.Get());

	// 如果通过断开连接或进行驱动程序升级的方法删除了设备，则必须
	// 必须重新创建所有设备资源。
	if (hr == DXGI_ERROR_DEVICE_REMOVED)
	{
		HandleDeviceLost();
	}
	else
	{
		DX::ThrowIfFailed(hr);
	}
}

// 用于将以与设备无关的像素(DIP)表示的长度转换为以物理像素表示的长度的方法。
float Direct3DBase::ConvertDipsToPixels(float dips)
{
	static const float dipsPerInch = 96.0f;
	return floor(dips * DisplayProperties::LogicalDpi / dipsPerInch + 0.5f); // 舍入到最接近的整数。
}


SampleRenderer::SampleRenderer() :
	m_loadingComplete(false),
	m_indexCount(0)
{
}

void SampleRenderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();

	auto loadVSTask = DX::ReadDataAsync("SimpleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync("SimplePixelShader.cso");

	auto createVSTask = loadVSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			m_d3dDevice->CreateVertexShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				&m_vertexShader
				)
			);

		const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DX::ThrowIfFailed(
			m_d3dDevice->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				fileData->Data,
				fileData->Length,
				&m_inputLayout
				)
			);
	});

	auto createPSTask = loadPSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			m_d3dDevice->CreatePixelShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				&m_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&m_constantBuffer
				)
			);
	});

	auto createCubeTask = (createPSTask && createVSTask).then([this] () {
		VertexPositionColor cubeVertices[] = 
		{
			{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
			{XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
			{XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
			{XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
			{XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
			{XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
			{XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
			{XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&m_vertexBuffer
				)
			);

		unsigned short cubeIndices[] = 
		{
			0,2,1, // -x
			1,2,3,

			4,5,6, // +x
			5,7,6,

			0,1,5, // -y
			0,5,4,

			2,6,7, // +y
			2,7,3,

			0,4,6, // -z
			0,6,2,

			1,3,7, // +z
			1,7,5,
		};

		m_indexCount = ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = {0};
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&m_indexBuffer
				)
			);
	});

	createCubeTask.then([this] () {
		this->ExtractNeedeNativeData(Platform::IntPtr(this->dataPtr));

		m_loadingComplete = true;
	});
}

void SampleRenderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();

	float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;
	if (aspectRatio < 1.0f)
	{
		fovAngleY /= aspectRatio;
	}

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(
			XMMatrixPerspectiveFovRH(
				fovAngleY,
				aspectRatio,
				0.01f,
				100.0f
				)
			)
		);
}

void SampleRenderer::Update(float timeTotal, float timeDelta)
{
	(void) timeDelta; // 未使用的参数。

	XMVECTOR eye = XMVectorSet(0.0f, 0.7f, 1.5f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, -0.1f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(timeTotal * XM_PIDIV4)));
}

void SampleRenderer::Render()
{
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
	m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(),
		midnightBlue
		);

	m_d3dContext->ClearDepthStencilView(
		m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	// 仅在加载时绘制多维数据集(加载为异步过程)。
	if (!m_loadingComplete)
	{
		return;
	}

	m_d3dContext->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		m_depthStencilView.Get()
		);

	m_d3dContext->UpdateSubresource(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0
		);

	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	m_d3dContext->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	m_d3dContext->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT,
		0
		);

	m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_d3dContext->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	m_d3dContext->VSSetConstantBuffers(
		0,
		1,
		m_constantBuffer.GetAddressOf()
		);

	m_d3dContext->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	m_d3dContext->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}


//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------


static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::renderer::DirectX11Renderer#wp8", INFO);

/**
 *  渲染器本地数据
 */
typedef struct {
	SampleRenderer^ render; // 示例渲染器
	int renderTargetWidth; // 渲染目标宽度
	int renderTargetHeight; // 渲染目标高度

	Microsoft::WRL::ComPtr<ID3D11Device1> d3dDevice; // 渲染设备
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dContext; // 渲染上下文

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain; // 交换缓冲链
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView; // 目标渲染视图
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView; // 不清楚

	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer; // 常量缓存区
	ModelViewProjectionConstantBuffer constantBufferData; // 常量缓存区数据

    // -------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader; // 顶点着色器
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader; // 像素着色器

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout; // 顶点格式

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer; // 顶点数据
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer; // 索引数据
	uint32 indexCount;
} NativeData;


void Direct3DBase::ExtractNeedeNativeData(Platform::IntPtr dataPtr) {
	NativeData* data = reinterpret_cast<NativeData*>(dataPtr.ToInt32());

	data->d3dDevice = this->m_d3dDevice;
	data->d3dContext = this->m_d3dContext;

	data->swapChain = this->m_swapChain;
	data->renderTargetView = this->m_renderTargetView;
	data->depthStencilView = this->m_depthStencilView;

	data->renderTargetWidth = this->m_renderTargetSize.Width;
	data->renderTargetHeight = this->m_renderTargetSize.Height;
}

void SampleRenderer::ExtractNeedeNativeData(Platform::IntPtr dataPtr) {
	Direct3DBase::ExtractNeedeNativeData(dataPtr);

	NativeData* data = reinterpret_cast<NativeData*>(dataPtr.ToInt32());

	data->constantBuffer = this->m_constantBuffer;
	data->constantBufferData = this->m_constantBufferData;

	data->inputLayout = this->m_inputLayout;
	data->vertexShader = this->m_vertexShader;
	data->pixelShader = this->m_pixelShader;

	data->vertexBuffer = this->m_vertexBuffer;
	data->indexBuffer = this->m_indexBuffer;
	data->indexCount = this->m_indexCount;

	this->dataPtr = data;
}



void DirectX11Renderer::init() {
	logger->info("init");

	NativeData* data = new NativeData();

	SampleRenderer^ render = ref new SampleRenderer();
	render->Initialize(CoreWindow::GetForCurrentThread());
	render->ExtractNeedeNativeData(Platform::IntPtr(data));


	// model view projecttion buffer
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);

	DX::ThrowIfFailed(
		data->d3dDevice->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&data->constantBuffer
			)
		);

	this->graphicsDevice->width = data->renderTargetWidth;
	this->graphicsDevice->height = data->renderTargetHeight;

	data->render = render;
	this->nativeData = data;
}

void DirectX11Renderer::clearBuffer() {
	NativeData* data = (NativeData*)this->nativeData;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dContext = data->d3dContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = data->renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = data->depthStencilView;

	Color c("#474747");
	const float midnightBlue[] = {c.r, c.g, c.b, 1.000f };

	d3dContext->ClearRenderTargetView(
		renderTargetView.Get(),
		midnightBlue
		);

	d3dContext->ClearDepthStencilView(
		depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);
}

void DirectX11Renderer::setViewport(int x, int y, int width, int height) {
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dContext = data->d3dContext;

    CD3D11_VIEWPORT viewport(x, y, width, height);

	d3dContext->RSSetViewports(1, &viewport);
}

void DirectX11Renderer::drawSample() {
	//logger->info("drawSample");

	NativeData* data = (NativeData*)this->nativeData;
	SampleRenderer^ render = data->render;

	static float abc = 0.0f;
	abc += 0.1f;

	//render->Update(abc, 0.1f);
	//render->Render();
}

/**
 * 根据相机配置更新矩阵
 */
void DirectX11RendererSetupCamera(NativeData* data, Camera* camera, ModelViewProjectionConstantBuffer& constantBufferData) {
	/*
	// 设置用于确定整个窗口的呈现视区。
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		m_renderTargetSize.Width,
		m_renderTargetSize.Height
		);

	m_d3dContext->RSSetViewports(1, &viewport);

	float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;
	if (aspectRatio < 1.0f)
	{
		fovAngleY /= aspectRatio;
	}

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(
			XMMatrixPerspectiveFovRH(
				fovAngleY,
				aspectRatio,
				0.01f,
				100.0f
				)
			)
		);
	*/

	
	/*
	XMVECTOR eye = XMVectorSet(0.0f, 0.7f, 1.5f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, -0.1f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX viewMatrix2 = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));
	XMStoreFloat4x4(&data->constantBufferData.view, viewMatrix2);
	*/

	/*
	Vector3 eye1(0.0f, 0.7f, 1.5f);
    Vector3 center1(0.0f, -0.1f, 0.0f);
    Vector3 up1(0.0f, 1.0f, 0.0f);

    Matrix4x4 viewMatrix1 = Matrix4x4::lookAt(eye1, center1, up1).transpose();

	memcpy(&data->constantBufferData.view, &viewMatrix1.m[0][0], sizeof(Matrix4x4));
	*/


	Microsoft::WRL::ComPtr<ID3D11Device1> d3dDevice = data->d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dContext = data->d3dContext;

    // setup camera
    if (camera != null) {
    	// set viewport
        com::dragon3d::util::math::Rect viewport = camera->getViewPortRect();
        CD3D11_VIEWPORT viewport(viewport.x, viewport.y, viewport.width, viewport.height);

		d3dContext->RSSetViewports(1, &viewport);

		// set view
		Vector3 eye = camera->transform->getPosition();
        Vector3 center = eye.add(Vector3::FORWARD);
        Vector3 up = Vector3::UP;
        Matrix4x4 viewMatrix = Matrix4x4::lookAt(eye, center, up).transpose(); // 需要转置，原因未知

 		memcpy(&constantBufferData.view, &viewMatrix.m[0][0], sizeof(Matrix4x4));

        // projection
		Matrix4x4 projMatrix = Matrix4x4::IDENTITY;

        if (!camera->orthographic) {
            projMatrix = projMatrix.multiply(Matrix4x4::perspective(camera->fieldOfView, camera->aspect, camera->nearClipPlane, camera->farClipPlane));
        } else {
            projMatrix = projMatrix.multiply(Matrix4x4::ortho(-camera->aspect, camera->aspect, -camera->aspect, camera->aspect, camera->nearClipPlane, camera->farClipPlane));
        }

        // 需要转置，原因未知
        projMatrix = projMatrix.transpose();

        memcpy(&constantBufferData.projection, &projMatrix.m[0][0], sizeof(Matrix4x4));
    }
}

/**
 * 根据网格矩阵变换更新模型矩阵
 */
void DirectX11RendererTransformMesh(NativeData* data, const Matrix4x4& matrix, ModelViewProjectionConstantBuffer& constantBufferData) {
	Matrix4x4 modelMatrix = matrix.transpose();
	memcpy(&constantBufferData.model, &modelMatrix.m[0][0], sizeof(Matrix4x4));
}

void DirectX11Renderer::drawLine(const Vector3& startV, const Vector3& endV, const Color& color, Camera* camera) {
	NativeData* data = (NativeData*)this->nativeData;

	Microsoft::WRL::ComPtr<ID3D11Device1> d3dDevice = data->d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dContext = data->d3dContext;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = data->renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = data->depthStencilView;

	// 仅在加载时绘制多维数据集(加载为异步过程)。
	if (!data->render->isLoadingComplete()){
		logger->info("waiting for load ok!");
		return;
	}

	//logger->info("draw mesh!");

	// 设置渲染视图
	d3dContext->OMSetRenderTargets(
		1,
		renderTargetView.GetAddressOf(),
		depthStencilView.Get()
		);

	// 指定当前渲染使用的顶点和像素着色器
	d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	d3dContext->IASetInputLayout(data->inputLayout.Get());

	d3dContext->VSSetShader(
		data->vertexShader.Get(),
		nullptr,
		0
		);

	d3dContext->PSSetShader(
		data->pixelShader.Get(),
		nullptr,
		0
		);

	// ----------------------------------------------

	// 更新 ModelViewProjection 矩阵数据
	// 更新 constantBufferData 数据 显卡的 constantBuffer
	
	// 根据相机的配置修改投影矩阵
	ModelViewProjectionConstantBuffer constantBufferData;

	DirectX11RendererSetupCamera(data, camera, constantBufferData);

	Matrix4x4 modelMatrix = Matrix4x4::IDENTITY;
	memcpy(&constantBufferData.model, &modelMatrix.m[0][0], sizeof(Matrix4x4));

	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = data->constantBuffer;

	d3dContext->UpdateSubresource(
		constantBuffer.Get(),
		0,
		NULL,
		&constantBufferData,
		0,
		0
		);

	d3dContext->VSSetConstantBuffers(
		0,
		1,
		data->constantBuffer.GetAddressOf()
		);


	// draw Line
	VertexPositionColor lineVertices[] = {
		{XMFLOAT3(startV.x, startV.y, startV.z), XMFLOAT3(color.r, color.g, color.b)},
		{XMFLOAT3(endV.x, endV.y,  endV.z), XMFLOAT3(color.r, color.g, color.b)}
	};

	D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
	vertexBufferData.pSysMem = lineVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(lineVertices), D3D11_BIND_VERTEX_BUFFER);

	DX::ThrowIfFailed(
		d3dDevice->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&data->vertexBuffer
			)
		);


	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	d3dContext->IASetVertexBuffers(
		0,
		1,
		data->vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);


	d3dContext->Draw(2, 0);
}

void DirectX11Renderer::drawMesh(Mesh* mesh, const Matrix4x4& matrix, Material* material, Camera* camera) {
	NativeData* data = (NativeData*)this->nativeData;

	Microsoft::WRL::ComPtr<ID3D11Device1> d3dDevice = data->d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dContext = data->d3dContext;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = data->renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = data->depthStencilView;

	// 仅在加载时绘制多维数据集(加载为异步过程)。
	if (!data->render->isLoadingComplete()){
		logger->info("waiting for load ok!");
		return;
	}

	//logger->info("draw mesh!");

	// 设置渲染视图
	d3dContext->OMSetRenderTargets(
		1,
		renderTargetView.GetAddressOf(),
		depthStencilView.Get()
		);

	// 指定当前渲染使用的顶点和像素着色器
	d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3dContext->IASetInputLayout(data->inputLayout.Get());

	d3dContext->VSSetShader(
		data->vertexShader.Get(),
		nullptr,
		0
		);

	d3dContext->PSSetShader(
		data->pixelShader.Get(),
		nullptr,
		0
		);

	// ----------------------------------------------

	// 更新 ModelViewProjection 矩阵数据
	// 更新 constantBufferData 数据 显卡的 constantBuffer
	
	// 根据相机的配置修改投影矩阵
	ModelViewProjectionConstantBuffer constantBufferData;

	DirectX11RendererSetupCamera(data, camera, constantBufferData);
	DirectX11RendererTransformMesh(data, matrix, constantBufferData);

	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = data->constantBuffer;

	d3dContext->UpdateSubresource(
		constantBuffer.Get(),
		0,
		NULL,
		&constantBufferData,
		0,
		0
		);

	d3dContext->VSSetConstantBuffers(
		0,
		1,
		data->constantBuffer.GetAddressOf()
		);


	Color drawColor = Color::BLACK;

  	// setup material
    if (material != null) {
        // setup color
        Color color = material->color;
        drawColor = color;

        // setup texture
        Texture* mainTexture = material->mainTexture;

        if (mainTexture != null) {
            //GLuint textureID = mainTexture->getNativeTextureID();

            
            //if (textureID == 0) {
            //    OpenGLRendererInitTexture(mainTexture);
            //} else {
            //    glBindTexture(GL_TEXTURE_2D, mainTexture->nativeTextureID);
            //}
            
        }
    }

	// 设置渲染的顶点数据
    if (mesh->vertices) {
        int vertexCount = mesh->vertexCount;
	    VertexPositionColor* cubeVertices = new VertexPositionColor[vertexCount];

	    for (int i=0; i<vertexCount; i++) {
	    	Vector3 vertex = mesh->vertices[i];
			cubeVertices[i].pos = XMFLOAT3(vertex.x, vertex.y, vertex.z);
			cubeVertices[i].color = XMFLOAT3(drawColor.r, drawColor.g, drawColor.b);;
	    }


		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColor) * vertexCount, D3D11_BIND_VERTEX_BUFFER);

		DX::ThrowIfFailed(
			d3dDevice->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&data->vertexBuffer
				)
			);


		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;
		d3dContext->IASetVertexBuffers(
			0,
			1,
			data->vertexBuffer.GetAddressOf(),
			&stride,
			&offset
			);
    }

	// 根据索引数据绘制

	if (mesh->triangleIndexCount > 0 && mesh->triangleIndexs) {
        unsigned short* cubeIndices = mesh->triangleIndexs;

		D3D11_SUBRESOURCE_DATA indexBufferData = {0};
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned short) * mesh->triangleIndexCount, D3D11_BIND_INDEX_BUFFER);

		DX::ThrowIfFailed(
			d3dDevice->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&data->indexBuffer
				)
			);

		d3dContext->IASetIndexBuffer(
			data->indexBuffer.Get(),
			DXGI_FORMAT_R16_UINT,
			0
			);

		d3dContext->DrawIndexed(
			mesh->triangleIndexCount,
			0,
			0
			);
    }

	

	// ---------------------------------------------------------------
	/*
	static float abc = 0.0f;
	abc += 0.01f;

	XMVECTOR eye = XMVectorSet(0.0f, 0.7f, 1.5f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, -0.1f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&data->constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
	XMStoreFloat4x4(&data->constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(abc * XM_PIDIV4)));
	

	data->d3dContext->OMSetRenderTargets(
		1,
		data->renderTargetView.GetAddressOf(),
		data->depthStencilView.Get()
		);

	data->d3dContext->UpdateSubresource(
		data->constantBuffer.Get(),
		0,
		NULL,
		&data->constantBufferData,
		0,
		0
		);

	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	data->d3dContext->IASetVertexBuffers(
		0,
		1,
		data->vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	data->d3dContext->IASetIndexBuffer(
		data->indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT,
		0
		);

	data->d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	data->d3dContext->IASetInputLayout(data->inputLayout.Get());

	data->d3dContext->VSSetShader(
		data->vertexShader.Get(),
		nullptr,
		0
		);

	data->d3dContext->VSSetConstantBuffers(
		0,
		1,
		data->constantBuffer.GetAddressOf()
		);

	data->d3dContext->PSSetShader(
		data->pixelShader.Get(),
		nullptr,
		0
		);

	data->d3dContext->DrawIndexed(
		data->indexCount,
		0,
		0
		);
	*/
}

void DirectX11Renderer::flushBuffer() {
    //logger->info("flush buffer");

    NativeData* data = (NativeData*)this->nativeData;
	SampleRenderer^ render = data->render;

	render->Present(); // 此调用将同步为显示帧速率。
}

// include commons
#include "../../DirectX11Renderer.cc"

