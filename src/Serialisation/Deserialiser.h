/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Deserialiser.h
//
//	Description:
//	 Blabla.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "DataNodes.h"


class fileData
{

};


// Turn a scene file into node objects
extern NodeWithChildren parseSceneFile(const std::string& scenepath);

// Parse the file into a vector of string segments
extern std::vector<std::string> parseSegmentsFromFile(std::fstream& sceneFile);

// Package string segments into nodes
extern NodeWithChildren packageFileSegmentToNode(const std::string& segment);

extern std::vector<std::string> splitString(const std::string& inputString);
extern std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const char& delimiter);
extern std::vector<std::string> splitStringBySpace(const std::string& inputString);
extern std::string parseFileToString(const std::string& scenepath);



//static std::string 
