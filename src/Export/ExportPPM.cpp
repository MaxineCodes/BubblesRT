#include "Export.h"

#include <iostream>
#include <fstream>

#include "../Datatypes/Colour.h"

// Export internal Image data into a .ppm file.
void exportAsPPM(Image image)
{
	// Create file to write to, overwrites existing file
	std::ofstream outputFile;
	outputFile.open("RenderOutputs/RenderOutput.ppm");
	if (outputFile.is_open())
	{
		std::cout << "Exporting PPM File..." << std::endl;

		// Write to file here
		const int imgWidth = image.getWidth();
		const int imgHeight = image.getHeight();

		// Write header
		outputFile << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";

		// Write pixels
		for (int y = 0; y < imgHeight; y++)
		{
			for (int x = 0; x < imgWidth; x++)
			{
				// Get pixels from the image
				Colour pixelColour = image.getPixelColour(x, y);
				// Cast to int [0-255]
				const int r = static_cast<int>(255.999 * pixelColour.r());
				const int g = static_cast<int>(255.999 * pixelColour.g());
				const int b = static_cast<int>(255.999 * pixelColour.b());
				// Write to file
				outputFile << r << ' ' << g << ' ' << b << '\n';
			}
		}
		std::cout << "Exported PPM file as: " << "RenderOutputs/RenderOutput.ppm" << std::endl;
	}

	// If file couldn't be opened
	else std::cout << "Failed to open PPM file." << std::endl;

	// Close file
	outputFile.close();
}