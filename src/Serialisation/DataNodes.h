////////////////////////////////////////////////////////////////////////////////////////////
// 
//	DataNodes.h
//
//	Description:
//	 Datanodes are an intermediary datatype between the file data and
//	 the data used in the program.
// 
// 
//  Node:
//	 Provides a shared interface across all node types.
//	 
//  DataNode:
//	 A node containing a singular string value.
//	 
//  VectorNode:
//	 A node containing a vector of nodes such as DataNodes.
//	 
//  NodeWithChildren:
//	 A node able to contain multiple other nodes
//	 so we can create a hierarchy of data.
// 
// 
//  Example Hierarchy:
// 
//	 NodeWithChildren
//	 |
//	 |- NodeWithChildren
//	 |  |- DataNode
//	 |  '- DataNode
//	 |
//	 '- DataNode
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


class Node
{
public:
	virtual Node getNode(const std::string& name);
	virtual std::string getValue(const std::string& name);
	virtual void write(std::ofstream& output);
	virtual void read(std::istream& input);
};


// Contains one string of data
class DataNode : public Node
{
public:
	std::string m_value;

public:
	DataNode(std::string value) { m_value = value; }
	
	Node getNode(const std::string& name);
	std::string getValue(const std::string key);
	void write(std::ofstream& output);
	void read(std::istream& input);
};


// Contains a vector of data
class VectorNode : public Node
{
public:
	std::vector<Node> m_values;

public:
	void write(std::ofstream& output);
	void read(std::istream& input);
};


class TextureNode : public Node
{
public:
	std::string m_textureString;

public:
	void write(std::ofstream& output);
	void read(std::istream& input);
};


class MeshNode : public Node
{
public:
	std::string m_meshString;

public:
	void write(std::ofstream& output);
	void read(std::istream& input);
};


//
class NodeWithChildren : public Node
{
public:
	std::string m_nodeName;
	std::map<std::string, Node> m_children;

public:
	Node getNode(const std::string& name);
	std::string getValue(const std::string& key);
	void write(std::ofstream& output);
	void read(std::istream& input);
};


//
class RootNode : public Node
{
public:
	std::string m_nodeName;
	std::map<std::string, NodeWithChildren> m_children;

public:
	void write(std::ofstream& output);
	void read(std::istream& input);
};