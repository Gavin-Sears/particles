// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    renderer.loadShader("simple-texture",
      "../shaders/simple-texture.vs",
      "../shaders/simple-texture.fs");

    Image img;
    img.load("../textures/tree.png", true);
    treeR = float(float(img.height()) / float(img.width()));
    renderer.loadTexture("tree", img, 0);
    // TODO: Use the width and the height of the image to scale the billboard

    renderer.loadTexture("grass", "../textures/grass.png", 0);
    renderer.blendMode(agl::BLEND);
  }


   void mouseMotion(int x, int y, int dx, int dy) {
      if (MDown)
      {
         // Azimuth and Elevation are updated via mouse
         Azimuth -= dx * 0.05f;
         Elevation += dy * 0.05f;
         

         eyePos = vec3(
            Radius * sin(Azimuth) * cos(Elevation), 
            Radius * sin(Elevation), 
            Radius * cos(Azimuth) * cos(Elevation)
         );
      }
   }

   void mouseDown(int button, int mods) {
      MDown = true;
   }

   void mouseUp(int button, int mods) {
      MDown = false;
   }

   void scroll(float dx, float dy) {
      // Scrolling directly affects radius (zoom)
      Radius += dy * 0.05f;

      eyePos = vec3(
         Radius * sin(Azimuth) * cos(Elevation), 
         Radius * sin(Elevation), 
         Radius * cos(Azimuth) * cos(Elevation)
      );
   }

  void draw() {
    renderer.beginShader("simple-texture");

    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
    renderer.lookAt(eyePos, lookPos, up);

    // draw plane
    renderer.texture("Image", "grass");
    renderer.push();
    renderer.translate(vec3(0.0, -0.5, 0));
    renderer.scale(vec3(2.0f));
    renderer.plane();
    renderer.pop();

    // draw tree
    renderer.texture("Image", "tree");
    renderer.push();
    renderer.rotate(Azimuth, vec3(0, 1.0, 0));
    renderer.scale(vec3(1.0, treeR, 1.0));
    renderer.translate(vec3(0.0, 0.215, 0.0));
    renderer.translate(vec3(-0.5, -0.5, 0));
    renderer.quad(); // vertices span from (0,0,0) to (1,1,0)
    renderer.pop();

    renderer.endShader();
  }

protected:

  vec3 eyePos = vec3(0, 0, 2);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  bool MDown = false;
  float Elevation = 0.0f;
  float Azimuth = 0.0f;
  float Radius = 10.0f;
  float treeR = 0.0;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
