#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>	
#include <DX3D/Graphics/IndexBuffer.h>	
#include "DX3D/Input/InputSystem.h"
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vertex.h>
#include <fstream>
#include <string>
#include <ranges>
#include <random>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc) : Base(desc.base)
{
	m_graphicsDevice = std::make_shared< GraphicsDevice>(GraphicsDeviceDesc{ m_logger });

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	// Original
	/*constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("Failed to open shader file");
	std::string shaderFileData
	{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
	};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();*/

	// VertexShader
	constexpr char vShaderFilePath[] = "DX3D/Assets/Shaders/BasicVertexShader.hlsl";
	std::ifstream vShaderStream(vShaderFilePath);
	if (!vShaderStream) DX3DLogThrowError("Failed to open vertex shader file");
	std::string vShaderFileData
	{
		std::istreambuf_iterator<char>(vShaderStream),
		std::istreambuf_iterator<char>()
	};

	auto vShaderSourceCode = vShaderFileData.c_str();
	auto vShaderSourceCodeSize = vShaderFileData.length();

	// PixelShader
	constexpr char pShaderFilePath[] = "DX3D/Assets/Shaders/BasicPixelShader.hlsl";
	std::ifstream pShaderStream(pShaderFilePath);
	if (!pShaderStream) DX3DLogThrowError("Failed to open pixel shader file");
	std::string pShaderFileData
	{
		std::istreambuf_iterator<char>(pShaderStream),
		std::istreambuf_iterator<char>()
	};

	auto pShaderSourceCode = pShaderFileData.c_str();
	auto pShaderSourceCodeSize = pShaderFileData.length();

	auto vs = device.compileShader({ vShaderFilePath, vShaderSourceCode, vShaderSourceCodeSize, "main", ShaderType::VertexShader });
	auto ps = device.compileShader({ pShaderFilePath, pShaderSourceCode, pShaderSourceCodeSize, "main", ShaderType::PixelShader });
	auto vsSig = device.createVertexShaderSignature({ vs });

	// Graphics Pipeline
	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	f32 cubeSize = 0.25f;
	Vec4 orange(0.99f, 0.16f, 0.01f, 1.0f);
	Vec4 mikublue(0.03f, 0.74f, 0.68f, 1.0f);
	Vec4 ourple(0.34f, 0.0f, 0.94f, 1.0f);
	Vec4 black(0.0f, 0.0f, 0.0f, 1.0f);
	Vertex vertexList[] =
	{
		// Front
		{{-cubeSize,-cubeSize,-cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{-cubeSize, cubeSize,-cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{ cubeSize, cubeSize,-cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{ cubeSize,-cubeSize,-cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},

		// Back Face
		{{ cubeSize,-cubeSize, cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{ cubeSize, cubeSize, cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{-cubeSize, cubeSize, cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{-cubeSize,-cubeSize, cubeSize}, {1.0f, 1.0f, 1.0f, 1.0f}}
	};

	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex) });

	// Index Buffer
	ui32 indexList[] =
	{
		// Front Side
		0,1,2,
		2,3,0,
		// Back Side
		4,5,6,
		6,7,4,
		// Top Side
		1,6,5,
		5,2,1,
		// Bottom Side
		7,0,3,
		3,4,7,
		// Left Side
		3,2,5,
		5,4,3,
		// Right Side
		7,6,1,
		1,0,7
	};
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });

	// Constant Buffer
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });

	// TEMPORARY DEPENDECY FOR DEBUGGING
	m_inputSystem = desc.inputSystem;
	m_TempWorldCam = Mat4x4::translation(Vec3(0.0f, 0.0f, -2.0f));

	//cubes.push_back(Cube(
	//	Vec3(0.0f, 0.9f, 0.0f),
	//	Vec3(1.0f, 1.0f, 1.0f)
	//));

	//cubes.push_back(Cube(
	//	Vec3(-1.5f, 2.0f, 0.0f),
	//	Vec3(1.0f, 1.0f, 1.0f)
	//));

	//cubes.push_back(Cube(
	//	Vec3(-1.5f, 3.0f, -2.0f),
	//	Vec3(1.0f, 1.0f, 1.0f)
	//));
	////plane 
	//cubes.push_back(Cube(
	//	Vec3(0.0f, 3.4f, -4.0f),
	//	Vec3(20.0f, 0.01f, 20.0f)
	//));

	/*std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_real_distribution<float> pos(-5.0f, 5.0f);

	for (int i = 0; i < 50; i++)
	{
		cubes.emplace_back(
			Vec3(pos(rand), pos(rand), pos(rand)),
			Vec3(1.0f, 1.0f, 1.0f)
		);
	}*/


}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

dx3d::GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void GraphicsEngine::render(f32 deltaTime, SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.0549, 0.07, 0.109, 1 });
	context.setGraphicsPipelineState(*m_pipeline);

	context.setViewportSize(swapChain.getSize());

	for (auto i : std::views::iota(0u, cubes.size()))
	{
		auto& vb = *m_vb;
		context.setVertexBuffer(vb);

		auto& ib = *m_ib;
		context.setIndexBuffer(ib);

		// Constant Buffer
		// Get the ConstantBuffer,
		auto& cb = *m_cb;

		// Declare Constant Data
		ConstantData data{};

		/*cubes[i].rotation.x += deltaTime * 0.5f;
		cubes[i].rotation.y += deltaTime;
		cubes[i].rotation.z += deltaTime * 0.25f;*/

		//m_lerp += deltaTime * 0.5f;

		//if (m_lerp > 1.0f)
		//	m_lerp = 1.0f;

		//// from 0,0,0, to 1,1,0
		//Vec3 position;
		//position.x = 0.0f + (1.0f - 0.0f) * m_lerp;
		//position.y = 0.0f + (1.0f - 0.0f) * m_lerp;
		//position.z = 0.0f;

		////from 1 to 0.25
		//Vec3 scale;
		//scale.x = 1.0f + (.25f - 1.0f) * m_lerp;
		//scale.y = 1.0f + (.25f - 1.0f) * m_lerp;
		//scale.z = 1.0f + (.25f - 1.0f) * m_lerp;

		//cubes[i].position = position;
		//cubes[i].scale = scale;

		// Feed Constant data with updated values
		updateConstantData(deltaTime, data, i);
		//DX3DLogInfo((std::to_string(deltaTime)).c_str());

		// Update it with the data, 
		context.updateConstantBuffer(cb, &data);

		// then send it to the vertex and pixel shader
		context.setConstantBuffer(cb);

		context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
		//context.drawTriangleList(vb.getVertexListSize(), 0u);
	}

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();

}

void GraphicsEngine::updateConstantData(f32 deltaTime, ConstantData& data, ui32 index)
{
	// Time
	m_time += deltaTime;
	data.m_time = m_time;

	// World
	Mat4x4 worldMat{};
	worldMat = Mat4x4::identity();
	worldMat = worldMat * Mat4x4::scale(cubes[index].scale);

	/*worldMat = worldMat * Mat4x4::rotateX(cubes[index].rotation.x);
	worldMat = worldMat * Mat4x4::rotateY(cubes[index].rotation.y);
	worldMat = worldMat * Mat4x4::rotateZ(cubes[index].rotation.z);*/

	worldMat = worldMat * Mat4x4::translation(cubes[index].position);
	data.m_world = worldMat;

	// View
	Mat4x4 worldCam{};
	worldCam = Mat4x4::identity();

	m_inputSystem->setCursorLocked(true);
	rotx += m_inputSystem->getMouseDelta().y;
	roty += m_inputSystem->getMouseDelta().x;

	worldCam = worldCam * Mat4x4::rotateX(rotx / 100.0f);
	worldCam = worldCam * Mat4x4::rotateY(roty / 100.0f);
	worldCam = worldCam * Mat4x4::rotateZ(rotz / 100.0f);

	f32 speed = 2.5f;
	if (m_inputSystem->isKeyDown(KeyCode::W)) forward += deltaTime * speed;
	if (m_inputSystem->isKeyDown(KeyCode::S)) forward -= deltaTime * speed;


	Vec3 tempWorldCamPos({ m_TempWorldCam.row(3).x, m_TempWorldCam.row(3).y, m_TempWorldCam.row(3).z });
	Vec3 camForward({ worldCam.row(2).x, worldCam.row(2).y, worldCam.row(2).z });

	Vec3 newPos = tempWorldCamPos + camForward * forward;
	worldCam = worldCam * Mat4x4::translation(newPos);
	worldCam = Mat4x4::inverse(worldCam);

	data.m_view = worldCam;

	// Perspective View
	int WindowDisplayHeight = 400;	
	int WindowDisplayWidth = WindowDisplayHeight * 1.78;	
	data.m_projection = Mat4x4::perspectiveFovLH
	(
		1.57f,
		(f32)WindowDisplayWidth / (f32)WindowDisplayHeight,
		0.1f,
		100.0f
	);
}

std::vector<Cube>* GraphicsEngine::getCubes()
{
	return &cubes;
}
