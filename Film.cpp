#include "Film.h"
#include "Color.h"
#include "FreeImage.h"

int sceneHeight = 100;
int sceneWidth = 200;

Film::Film(){
  pixelData = vector<vector<Color> >(sceneHeight,
				    vector<Color>(sceneWidth, Color(1,0,1)));
}
Color Film::getPixel(int x, int y){
  return pixelData[y][x];
}
void Film::put(Sample pixel, Color pixelColor){
  pixelData[pixel.y()][pixel.x()] = pixelColor;
}
void Film::output(string path){
  int maxIntensity = 255;
  int bpp = 24;
  RGBQUAD color;
  FreeImage_Initialise();
  FIBITMAP* bitmap = FreeImage_Allocate(sceneWidth,
					sceneHeight,
					bpp);
  for(int h = 0; h < sceneHeight; h++){
    vector<Color> row = pixelData[h];
    for(int w = 0; w < sceneWidth; w++){
      Color pixelColor = row[w];
      color.rgbRed = pixelColor.r() * maxIntensity;
      color.rgbGreen = pixelColor.g() * maxIntensity;
      color.rgbBlue = pixelColor.b() * maxIntensity;
      FreeImage_SetPixelColor(bitmap, w, h, &color);
    }
  }
  if (FreeImage_Save(FIF_PNG, bitmap, path.c_str(), 0)) {
    cout << "Image saved to " << path << endl;
  }
  else {
    cerr << "Couldn't save image to " << path << endl;
    exit(1);
  }

  FreeImage_DeInitialise();
}

