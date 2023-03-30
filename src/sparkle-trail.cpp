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
  float start;
  float ttl;
  float eol;
};

class Viewer : public Window {
 public:
  Viewer() : Window() {}

  void setup() {
    setWindowSize(1000, 1000);
    position[0] = sin(elapsedTime());
    position[1] = cos(elapsedTime());
    rotation = -1 * atan2(position[1], position[0]);
    createConfetti(200);
    renderer.setDepthTest(false);
    renderer.blendMode(agl::ADD);
  }

  void createConfetti(int size) {
    renderer.loadTexture("particle", "../textures/star4.png", 0);
    for (int i = 0; i < size; i++) {
      Particle particle;
      particle.color = vec4(agl::randomUnitCube(), 1);
      particle.size = 0.25;
      particle.rot = rotation;
      particle.pos = position;
      particle.vel = agl::randomUnitCube();
      float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      particle.start = r1 * 5;
      float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      particle.ttl = r2 * 5;
      particle.eol = elapsedTime() + particle.ttl + particle.start;
      mParticles.push_back(particle);
    }
  }

  void updateConfetti() {
    for (int i = 0; i < mParticles.size(); i++) {
      Particle particle = mParticles[i];
      if(elapsedTime() > particle.eol) {
        particle.color = vec4(agl::randomUnitCube(), 1);
        particle.pos = position;
        particle.rot = rotation;
        particle.size = 0.25;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        particle.ttl = r * 5;
        particle.eol = elapsedTime() + particle.ttl;
        particle.vel = agl::randomUnitCube();
      }
      else if(elapsedTime() < particle.start){
        particle.pos = position;
        particle.rot = rotation;
      }
      else {
        particle.pos += particle.vel * 0.01f;
        particle.rot += 0.05f;
        particle.color.a = -1 * ((elapsedTime() - particle.eol) / particle.ttl);
        particle.size *= 1.001;
      }
      mParticles[i] = particle;
    }
  }

  void drawConfetti() {
    renderer.texture("image", "particle");
    for (int i = 0; i < mParticles.size(); i++) {
      Particle particle = mParticles[i];
      renderer.sprite(particle.pos, particle.color, particle.size,
                      particle.rot);
    }
  }

  void mouseMotion(int x, int y, int dx, int dy) {}

  void mouseDown(int button, int mods) {}

  void mouseUp(int button, int mods) {}

  void scroll(float dx, float dy) { eyePos.z += dy; }

  void keyUp(int key, int mods) {}

  void draw() {
    renderer.beginShader("sprite");
    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
    renderer.lookAt(eyePos, lookPos, up);

    position[0] = sin(2 * elapsedTime());
    position[1] = cos(2 * elapsedTime());
    rotation = -1 * atan2(position[1], position[0]);
    renderer.sprite(position, vec4(1.0f), 0.25f, rotation);

    updateConfetti();
    drawConfetti();

    renderer.endShader();
  }

 protected:
  vec3 eyePos = vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  vec3 position = vec3(1, 0, 0);
  float rotation = 0.0f;
  std::vector<Particle> mParticles;

};

int main(int argc, char** argv) {
  Viewer viewer;
  viewer.run();
  return 0;
}
