#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Triangle.h>
#include <DX3D/Math/Quad.h>
#include <vector>

#include "DX3D/Math/Mat4x4.h"

namespace dx3d
{
	class GraphicsEngine final : public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevice& getGraphicsDevice() noexcept;

		void render(SwapChain& swapChain);

	private:
		ui32 time{};
		ui32 time_prev{};
		ui32 time_curr{};
		ui32 delta_time{};

		struct alignas(16) ConstantData
		{
			Mat4x4 m_world{};
			Mat4x4 m_view{};
			Mat4x4 m_projection{};
			ui32 m_time;
		};

	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		DeviceContextPtr m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{};
		VertexBufferPtr m_vb{};
		ConstantBufferPtr m_cb{};
		IndexBufferPtr m_ib{};

		void updateConstantData(ConstantData& data);
	};
}