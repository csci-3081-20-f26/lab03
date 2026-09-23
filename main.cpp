#include <iostream> // Used for io (e.g. cout, cin)
#include <string> // Used for string functions

// Needed for reading images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Needed for writing images
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// The Color class manages color operations using normalized 
// floating point values between 0-1 (instead of unsigned bytes 0-255).
class Color {
public:
  Color(float red, float green,float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  float red() const { return r; }
  float green() const { return g; }
  float blue() const { return b; }
  float alpha() const { return a; }

  Color operator*(const Color& c) const {
    return Color(r*c.r, g*c.g, b*c.b, a*c.a);
  }

private:
  float r, g, b, a;
};

// Updates the red channel only.
Color red(const Color& color) {
  return color*Color(1, 0, 0, 1);
}

// Calculates a red color gradient
Color red_gradient(const Color& color, int x, int width) {
  return Color(1.0*x/width, color.green(), color.blue(), color.alpha());
}

// Sets a pixel value from a color
void set_pixel_color(unsigned char* pixel, const Color& color) {
      pixel[0] = color.red()*255;//255*x/width;
      pixel[1] = color.green()*255;
      pixel[2] = color.blue()*255;
      pixel[3] = color.alpha()*255;
}

Color get_pixel_color(unsigned char* pixel) {
  return Color(
        1.0*pixel[0]/255,
        1.0*pixel[1]/255,
        1.0*pixel[2]/255,
        1.0*pixel[3]/255
      );
}

// Edits an image based on a specified operation
void edit(unsigned char* image, int width, int height, int components, const std::string& operation) {
   // Loop through the image pixels and modify values
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      // Get the pixel as a byte array
      unsigned char* pixel = &image[(y*width + x)*components];

      Color color = get_pixel_color(pixel);

      Color output = color;

      // Perform specified operation
      if (operation == "red") {
        output = red(color);
      }
      else if (operation == "red_gradient") {
        output = red_gradient(color, x, width);
      }

      set_pixel_color(pixel, output);
    }
  }
}

int main(int argc, char**argv) {
  // Confirm there are the correct number of arguments in the command line
  if (argc < 2) {
    std::cout << "Usage: ./image_app <image> <operation>" << std::endl;
    std::cout << "Example: ./image_app data/dog.png red" << std::endl;
    exit(0);
  }

  // Get input from the command line
  std::string input(argv[1]);
  std::string operation(argv[2]);
  std::string output = "output/" + operation + ".png";

#ifndef IMAGE_H_ 

  // Load in an image
  int width, height, components;
  unsigned char *loadedImage = stbi_load(input.c_str(), &width, &height, &components, STBI_rgb_alpha);
  components = 4; // Images may have less components, but we are forcing alpha with STBI_rgb_alpha
  
  // See if image loaded correctly:
  unsigned char testByte = loadedImage[0];

  // Copy the image data into a local image buffer and free the image
  unsigned char image[1228800]; // = Memory is large enough to hold 640x480 images (e.g. statue.png is the largest) with 4 components (RGBA): 640x480*4 = 1228800.
	std::copy(loadedImage, loadedImage + width*height*components, image); // copy allows us to copy one byte array to another
  stbi_image_free(loadedImage);

  // Edit the image based on the operation
  edit(image, width, width, components, operation);

  // Save the output image
  std::cout << "Saving image: " << output << std::endl;
  stbi_write_png(output.c_str(), width, height, components, image, width*4);

#else
  Image image(input);

  #ifdef IMAGE_EDITOR_H_
  // Use the image editor
  ImageEditor editor;
  editor.edit(image, operation);
  #endif

  image.save(output);

#endif
}