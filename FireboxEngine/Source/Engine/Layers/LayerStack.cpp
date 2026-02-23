#include "LayerStack.h"

Firebox::LayerStack::LayerStack()
{
	m_LayerInsert = m_Layers.begin();
}

Firebox::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		delete layer;
	}
}

void Firebox::LayerStack::PushLayer(Layer* layer)
{
	m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void Firebox::LayerStack::PushOverlay(Layer* overlay)
{
	
}

void Firebox::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
		m_LayerInsert--;
	}
}

void Firebox::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
	}
}
