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
    renderer.loadTexture("tree", img, 0);
    // TODO: Use the width and the height of the image to scale the billboard

    renderer.loadTexture("grass", "../textures/grass.png", 0);
    renderer.blendMode(agl::BLEND);
  }


  void mouseMotion(int x, int y, int dx, int dy) {
      if(left_mousedown && shiftdown){
         radius = std::max(1.0f, radius - dy * 0.1f);
      }
      if(left_mousedown && !shiftdown){
         azimuth = azimuth + dx * 0.01f;
         float maxElevation = 3.14159f / 2.0f - 0.01f;
         elevation = std::min(maxElevation, std::max(-1.0f * maxElevation, elevation + dy * 0.01f));
      }
   }

   void mouseDown(int button, int mods) {
      if(button == GLFW_MOUSE_BUTTON_LEFT){
         left_mousedown = true;
      }
      if(button == GLFW_MOUSE_BUTTON_RIGHT){
         right_mousedown = true;
      }
      if(button == GLFW_MOUSE_BUTTON_MIDDLE){
         right_mousedown = true;
      }
   }

   void mouseUp(int button, int mods) {
      if(button == GLFW_MOUSE_BUTTON_LEFT){
         left_mousedown = false;
      }
      if(button == GLFW_MOUSE_BUTTON_RIGHT){
         right_mousedown = false;
      }
      if(button == GLFW_MOUSE_BUTTON_MIDDLE){
         right_mousedown = false;
      }
   }

   void scroll(float dx, float dy) {
      radius = std::max(1.0f, radius - dy * 0.1f);
   }

   void keyDown(int key, int mods) {
      if(key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT){
         shiftdown = true;
      }
   }

   void keyUp(int key, int mods) {
      if(key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT){
         shiftdown = false;
      }
   }

  void draw() {
    renderer.beginShader("simple-texture");

    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

    vec3 eyePos =  vec3(
        radius * cos(azimuth) * cos(elevation),
        radius * sin(elevation),
        radius * sin(azimuth) * cos(elevation)
    );

    vec3 camZ = normalize(eyePos - lookPos);
    vec3 camX = normalize(cross(vec3(0,1,0), camZ));
    vec3 camY = normalize(cross(camZ, camX));
    up = camY;

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
    renderer.rotate(atan2(eyePos.x, eyePos.z), vec3(0, 1, 0));
    renderer.translate(vec3(-0.5, -0.5, 0));
    renderer.quad(); // vertices span from (0,0,0) to (1,1,0)
    renderer.pop();

    renderer.endShader();
  }

protected:

  vec3 eyePos = vec3(0, 0, 2);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  bool left_mousedown = false;
  bool right_mousedown = false;
  bool shiftdown = false;
  float radius = 2.0f;
  float azimuth = 2.0f;
  float elevation = 0.0f;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
