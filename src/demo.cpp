// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"

using namespace std;
using namespace glm;
using namespace agl;

struct Particle {
  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec4 color;
  float size;
  float rot;
  float startTime;
};

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    duckMesh.load("../models/rubberDucky.ply");
    createDuckies(10);
    createConfetti(10);
    renderer.loadShader("simple-texture",
      "../shaders/simple-texture.vs",
      "../shaders/simple-texture.fs");

    Image img;

    renderer.loadTexture("grass", "../textures/grass.png", 0);
    renderer.loadTexture("ducky", "../textures/duck_texture.png", 0);
    renderer.loadTexture("particle", "../textures/star4.png", 0);
    renderer.blendMode(agl::BLEND);
  }

  void createDuckies(int size)
  {
    for (int i = 0; i < size; i++)
    {
      Particle particle;
      particle.color = vec4(1.0f, 0.7f, 0.0f, 1);
      float scale = std::max(1.0f, (size * 0.35f));
      particle.size = (1.0f / scale);
      particle.rot = 0.0f;
      particle.pos = vec3(0.0f, 0.0f, 0.0f);
      particle.vel = vec3(0.0f, 0.0f, 0.0f);
      particle.startTime = ((2 * M_PI) / float(size)) * i;
      mDuckies.push_back(particle);
    }
  }

  void createConfetti(int size)
  {
    for (int i = 0; i < size; i++)
    {
      Particle particle;
      particle.color = vec4(1, 1, 1, 1);
      particle.size = 0.15f;
      particle.rot = ((2 * M_PI) / float(size)) * i;
      particle.pos = vec3(0.0f, 0.0f, 0.0f);
      particle.vel = vec3(0.0f, 0.0f, 0.0f);
      particle.startTime = ((2 * M_PI) / float(size)) * i;
      mParticles.push_back(particle);
    }
  }

  void updateDuckies(float dt)
  {
    for (int i = 0; i < mDuckies.size(); i++)
    {
      float time = elapsedTime();
      mDuckies[i].pos = vec3(
        dizzyPos.x + sin(time + mDuckies[i].startTime), 
        dizzyPos.y + (0.1 * sin((time + mDuckies[i].startTime) * 6.0f)), 
        dizzyPos.z + cos(time + mDuckies[i].startTime)
      ) * dizzyRad;

      mDuckies[i].rot = time + mDuckies[i].startTime;
    }
  }

  void updateConfetti(float dt)
  {
    for (int i = 0; i < mParticles.size(); i++)
    {
      float time = elapsedTime();
      mParticles[i].pos = vec3(
        dizzyPos.x - sin(time + mParticles[i].startTime), 
        dizzyPos.y + (0.1 * sin((time + mParticles[i].startTime) * 6.0f)), 
        dizzyPos.z + cos(time + mParticles[i].startTime)
      ) * dizzyRad;

      mParticles[i].rot = time + mDuckies[i].startTime;
    }
  }

  void drawDuckies()
  {
    // draw
    for (int i = 0; i < mDuckies.size(); i++)
    {
      Particle particle = mDuckies[i];
      renderer.texture("Image", "ducky");
      renderer.push();
      renderer.translate(particle.pos);
      renderer.scale(vec3(1.0f) * particle.size);
      renderer.rotate((particle.rot + M_PI_2), vec3(0.0f, 1.0f, 0.0f));
      renderer.mesh(duckMesh);
      renderer.pop();
    }
  }

  void drawConfetti()
  {
    // draw
    for (int i = 0; i < mParticles.size(); i++)
    {
      Particle particle = mParticles[i];
      renderer.texture("image", "particle");
      renderer.push();
      renderer.rotate(Azimuth, vec3(0.0f, 1.0f, 0.0f));
      renderer.translate(particle.pos);
      renderer.scale(vec3(1.0f) * particle.size);\
      renderer.quad();
      renderer.pop();
    }
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
    renderer.scale(vec3(4.0f, 0.2f, 4.0f));
    renderer.sphere();
    renderer.pop();
    renderer.push();

    updateDuckies(dt());
    drawDuckies();
    updateConfetti(dt());
    drawConfetti();

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

  vec3 dizzyPos = vec3(0.0f, 2.0f, 0.0f);
  float dizzyRad = 1.0f;

  PLYMesh duckMesh;

  std::vector<Particle> mDuckies;
  std::vector<Particle> mParticles;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
