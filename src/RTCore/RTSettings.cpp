#include "RTSettings.h"

int RTSettings::getWidth()
{
	return m_imageWidth;
}

int RTSettings::getHeight()
{
	return m_imageHeight;
}

float RTSettings::getRenderScale()
{
	return m_renderScale;
}

const int RTSettings::getRayBounceCount()
{
	return m_rayBounceCount;
}

bool RTSettings::getAntialiasing()
{
	return m_antialiasing;
}

bool RTSettings::getNormalDebug()
{
	return m_normalDebug;
}

bool RTSettings::getDepthDebug()
{
	return m_depthDebug;
}

void RTSettings::setImageWidth(int width)
{
	m_imageWidth = width;
}

void RTSettings::setImageHeight(int height)
{
	m_imageHeight = height;
}

void RTSettings::setImageSize(int width, int height)
{
	m_imageWidth = width;
	m_imageHeight = height;
}

void RTSettings::setRenderScale(float scale)
{
	m_renderScale = scale;
}

void RTSettings::setAntiAliasing(bool enabled)
{
	m_antialiasing = enabled;
}

void RTSettings::setNormalDebug(bool enabled)
{
	m_normalDebug = enabled;
}

void RTSettings::setDepthDebug(bool enabled)
{
	m_depthDebug = enabled;
}

void RTSettings::printInfo(const int sampleCount)
{
	std::cout << "====[ RTSettings ]=================" << std::endl;
	if (m_sampleCount > 1)
		std::cout << "Sample Count: " << m_sampleCount << std::endl;
	else
		std::cout << "Sample Count: " << sampleCount << std::endl;

	std::cout << "ImageWidth:   " << m_imageWidth << std::endl;
	std::cout << "ImageHeight:  " << m_imageHeight << std::endl;
	std::cout << "RenderScale:  " << m_renderScale << std::endl;

	std::cout << std::endl;

	if (m_antialiasing)
		 std::cout << "Antialiasing: " << "Enabled" << std::endl;
	else std::cout << "Antialiasing: " << "Disabled" << std::endl;

	if (m_normalDebug)
		 std::cout << "NormalDebug:  " << "Enabled" << std::endl;
	else std::cout << "NormalDebug:  " << "Disabled" << std::endl;

	if (m_depthDebug)
		 std::cout << "DepthDebug:   " << "Enabled" << std::endl;
	else std::cout << "DepthDebug:   " << "Disabled" << std::endl;

	std::cout << "===================================" << std::endl << std::endl;
}
