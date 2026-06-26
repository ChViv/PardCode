#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Mat4x4.h>
#include <vector>

#include <DX3D/Cube.h>

namespace dx3d
{
	// Final means no class can derive from GraphicsEngine class
	class GraphicsEngine final : public Base
	{
	public:
		GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;

		void render(f32 deltaTime, SwapChain& swapChain);

		// DepthTest Method
		std::vector<Cube>* getCubes();
		// Debug things

		Vec3 lerp(const Vec3& a, const Vec3& b, float t);
	private:
		struct alignas(16) ConstantData
		{
			Mat4x4 m_world{};
			Mat4x4 m_view{};
			Mat4x4 m_projection{};
			f32 m_time;
		};
	private:
		void updateConstantData(f32 deltaTime, ConstantData& data, ui32 index);
	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};
		ConstantBufferPtr m_cb{};
		IndexBufferPtr m_ib{};
		// TEMPORARY DEPENDENCY FOR DEBUGGING
		f32 m_time{ 0.0f };
		InputSystemPtr m_inputSystem{};
		f32 rotx{};
		f32 roty{};
		f32 rotz{};

		// DepthTest Members
		std::vector<Cube> cubes;

		// Temporary Camera Object
		Mat4x4 m_TempWorldCam{};
		f32 forward{ -2.0f };
		f32 right{};

		float m_lerp = 0.0f;
	};
}