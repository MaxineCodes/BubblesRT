#include "DataNodes.h"

Node Node::getNode(const std::string& name)
{
	return Node();
}

std::string Node::getValue(const std::string& name)
{
	std::cout << "Node::getValue" << std::endl;
	return "";
}

void Node::write(std::ofstream& output)
{

}

void Node::read(std::istream& input)
{

}

Node DataNode::getNode(const std::string& name)
{
	std::cout << "DataNode contains no sub node" << std::endl;
	return Node();
}

std::string DataNode::getValue(std::string key)
{
	std::cout <<"DataNode::getValue" << std::endl;
	return m_value;
}

void DataNode::write(std::ofstream& output)
{

}

void DataNode::read(std::istream& input)
{

}

Node NodeWithChildren::getNode(const std::string& name)
{
	std::cout << "NodeWithChildren::getNode" << std::endl;
	return m_children[name];
}

std::string NodeWithChildren::getValue(const std::string& key)
{
	std::cout << "NodeWithChildren::getValue" << std::endl;
	return m_children[key].getValue(key);
}

void NodeWithChildren::write(std::ofstream& output)
{

}

void NodeWithChildren::read(std::istream& input)
{

}

void VectorNode::write(std::ofstream& output)
{

}

void VectorNode::read(std::istream& input)
{

}
