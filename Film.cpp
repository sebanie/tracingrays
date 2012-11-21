#include "Film.h"
#include "Color.h"
#include "FreeImage.h"
#include "Scene.h"


Film::Film(int height, int width){
  sceneHeight = height;
  sceneWidth = width;
  pixelData = vector<vector<Color> >(sceneHeight,
				    vector<Color>(sceneWidth, Color(1,0,1)));
  cout << "This is scene height: " << sceneHeight << endl;
}
Color Film::getPixel(int x, int y){
  return pixelData[y][x];
}
void Film::put(Sample pixel, Color pixelColor){
  cout << "yoyo ma man" << endl;
  pixelData[pixel.y()][pixel.x()] = pixelColor;//Color(0, 1, 0);
  cout << "out of your mind" << endl;
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
      color.rgbRed = pixelColor.getR() * maxIntensity;
      color.rgbGreen = pixelColor.getG() * maxIntensity;
      color.rgbBlue = pixelColor.getB() * maxIntensity;
      FreeImage_SetPixelColor(bitmap, w, h, &color);
    }
  }
  if (FreeImage_Save(FIF_PNG, bitmap, path.c_str(), 0)) {
    cout << "Image saved to " << path << endl;
    cout << sceneWidth << endl;
  }
  else {
    cerr << "Couldn't save image to " << path << endl;
    exit(1);
  }

  FreeImage_DeInitialise();
}

