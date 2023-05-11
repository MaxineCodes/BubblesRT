#include "Deserialiser.h"
#include <algorithm>
#include <sstream>


// Turn a scene file into node objects
NodeWithChildren parseSceneFile(const std::string& scenepath)
{
    std::fstream sceneFile;
    sceneFile.open(scenepath, std::ios::in);

    NodeWithChildren sceneRootNode;
    sceneRootNode.m_nodeName = "scene_root_node";

    std::vector<std::string> segmentsInFile;

    if (!sceneFile.is_open())
        std::cout << "Error parsing scene file: Could not open: " << scenepath << std::endl;


    // Get all segments from the file
    if (sceneFile.is_open())
    {
        segmentsInFile = parseSegmentsFromFile(sceneFile);
        sceneFile.close();
    }

    // Package segments into nodes
    for (int i = 0; i < segmentsInFile.size(); i++)
    {
        NodeWithChildren entityNode = packageFileSegmentToNode(segmentsInFile[i]);
        sceneRootNode.m_children[entityNode.m_nodeName] = entityNode;
    }

    return sceneRootNode;
}


// Parse the file into a vector of segments
std::vector<std::string> parseSegmentsFromFile(std::fstream& sceneFile)
{
    std::vector<std::string> segmentsInFile;

    for (std::string segment, line; std::getline(sceneFile, line); )
    {
        // On newline, push the segment into the vector
        if (line == "")
        {
            segmentsInFile.push_back(segment);
            segment = "";
        }

        // If not newline, expand the segment string
        else
        {
            // If segment exists, add the line with a newline
            if (segment != "")
                segment = segment + "\n" + line;

            // Segment doesn't exist yet, make it line
            else
                segment = line;
        }
    }

    return segmentsInFile;
}


// Package a string segment of the file into nodes
NodeWithChildren packageFileSegmentToNode(const std::string& segment)
{
    NodeWithChildren parentNode;
    std::vector<std::string> linesOfSegment = splitString(segment);

    // Set the parent node name to value of the first line
    parentNode.m_nodeName = linesOfSegment[0];

    // Every data value comes after the first line 
    for (int i = 1; i < linesOfSegment.size(); i++)
    {
        std::vector<std::string> str = splitStringBySpace(linesOfSegment[i]);

        // Store data in a node
        DataNode node(str[1]);
        
        // Put data into the parent node
        parentNode.m_children[str[0]] = node;

    }

    return parentNode;
}


std::vector<std::string> splitString(const std::string& inputString)
{
    std::vector<std::string> outputVector;
    std::string str;
    std::stringstream sstream(inputString);
    while (getline(sstream, str))
        outputVector.push_back(str);
    return outputVector;
}


std::vector<std::string> splitStringByDelimiter(const std::string& inputString, const char& delimiter)
{
    std::vector<std::string> outputVector;
    std::string str;
    std::stringstream sstream(inputString);
    while (getline(sstream, str, delimiter))
        outputVector.push_back(str);
    return outputVector;
}


std::vector<std::string> splitStringBySpace(const std::string& inputString)
{
    return splitStringByDelimiter(inputString, ' ');
}


// Parses entire scene file to a string
std::string parseFileToString(const std::string& scenepath)
{
    // Open file
    std::fstream sceneFile(scenepath, std::ios::in | std::ios::binary);

    if (!sceneFile.is_open())
        std::cout << "Error parsing file to string: Could not open file: " << scenepath << std::endl;

    // Read file contents
    std::string fileAsString
    { 
        std::istreambuf_iterator<char>(sceneFile), 
        std::istreambuf_iterator<char>() 
    };

    // Close file
    sceneFile.close();

    return fileAsString;
}
