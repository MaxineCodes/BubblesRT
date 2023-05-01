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
