// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

struct Particle {
  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec4 color;
  float rot;
  float size;
};

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    createConfetti(500);
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
    limit = 0;
  }

  void createConfetti(int size)
  {
    renderer.loadTexture("particle", "../textures/star4.png", 0);
    for (int i = 0; i < size; i++)
    {
      Particle particle;
      particle.color = vec4(agl::randomUnitCube(), 0.0f);
      particle.size = 0.25f;
      particle.rot = 0.0f;
      particle.pos = agl::randomUnitCube();
      particle.vel = agl::randomUnitCube() * 0.01f;
      mParticles.push_back(particle);
    }
  }

  void updateConfetti()
  {
    // The limit of stars created per frame
    limit = 0;
    Particle curPar;
    for (unsigned int i = 0; i < mParticles.size(); i++)
    {
      curPar = mParticles[i];
      if (curPar.color.w > 0)
      {
        mParticles[i].color.w -= 0.01f;
        mParticles[i].size += 0.001f;
        mParticles[i].rot += 0.01f;
        vec3 movement = (lastPos - position) * 0.7f;
        mParticles[i].pos = curPar.pos + movement + curPar.vel;
      }
      else if (limit < 1)
      {
        mParticles[i].pos = vec3(position.x, position.y, 0.0f);
        mParticles[i].color = vec4(agl::randomUnitCube(), 1.0f);
        mParticles[i].size = 0.25f;
        mParticles[i].rot = 0.0f;
        limit++;
      }
    }
  }

  void drawConfetti()
  {
    renderer.texture("image", "particle");
    for (int i = 0; i < mParticles.size(); i++)
    {
      Particle particle = mParticles[i];
      renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
    }
  }

  void mouseMotion(int x, int y, int dx, int dy) {
  }

  void mouseDown(int button, int mods) {
  }

  void mouseUp(int button, int mods) {
  }

  void scroll(float dx, float dy) {
    eyePos.z += dy;
  }

  void keyUp(int key, int mods) {
  }

  void draw() {
    renderer.beginShader("sprite");
    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

    curFrame = int(elapsedTime() * 30.0f);
    speed = 0.03f;

    position = vec3(cos(curFrame * speed), sin(curFrame * speed), 0.0f);
    renderer.lookAt(eyePos, lookPos, up);
    renderer.sprite(position, vec4(1.0f), 0.25f);
    updateConfetti();
    drawConfetti();
    renderer.endShader();
    lastPos = position;
  }

protected:

  vec3 eyePos = vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  vec3 lastPos = vec3(1, 0, 0);
  vec3 position = vec3(1, 0, 0);
  int curFrame = 0;
  float speed;
  int limit;

  std::vector<Particle> mParticles;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
