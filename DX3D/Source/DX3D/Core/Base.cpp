#include "DX3D/Core/Base.h"
using namespace dx3d;

Base::Base(const BaseDesc& desc) : m_logger(desc.logger)
{
}

Base::~Base()
{
}

Logger& Base::getLogger() noexcept
{
	return m_logger;
}