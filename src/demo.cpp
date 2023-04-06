// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>

#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

struct Keyframe {
  vec3 position;
  vec3 color;
  float alpha;
  float size;
};

class KeyframedParticle {
 public:
  KeyframedParticle() {}

  void setup() {
    position = keyframes[0].position;
    color = keyframes[0].color;
    alpha = keyframes[0].alpha;
    size = keyframes[0].size;
  }

  void update(float elapsedTime) {
    if(!isDead && elapsedTime > times[times.size() - 1]){
      isDead = true;
    }
    if(isDead) return;
    Keyframe k1;
    Keyframe k2;
    float t1;
    float t2;
    int k1_num;
    int k2_num;
    if(elapsedTime < times[0]){
      k1 = keyframes[0];
      k2 = keyframes[0];
      t1 = 0;
      t2 = 1;
      k1_num = 0;
      k2_num = 0;
    }
    else if(elapsedTime > times[times.size() - 1]){
      k1 = keyframes[times.size() - 1];
      k2 = keyframes[times.size() - 1];
      t1 = 1;
      t2 = 2;
      k1_num = times.size() - 1;
      k2_num = times.size() - 1;
    }
    else{
      for(int i = 0; i < times.size(); i++){
        if(elapsedTime > times[i] && elapsedTime < times[i + 1]){
          k1 = keyframes[i];
          k2 = keyframes[i + 1];
          t1 = times[i];
          t2 = times[i + 1];
          k1_num = i;
          k2_num = i + 1;
          break;
        }
      }
    }
    float t = (elapsedTime - t1) / (t2 - t1);
    float ease = 3;
    float eased_t = 1 - pow(1 - t, ease);
    color = k1.color * (1 - eased_t) + k2.color * eased_t;
    alpha = k1.alpha * (1 - eased_t) + k2.alpha * eased_t;
    position = k1.position * (1 - eased_t) + k2.position * eased_t;
    size = k1.size * (1 - eased_t) + k2.size * eased_t;
  }

  vec3 position = vec3(0, 0, 0);
  vec3 color = vec3(255, 255, 255);
  float alpha = 1;
  float size = 1;
  std::vector<float> times;
  std::vector<Keyframe> keyframes;
  bool isDead = false;
};

std::vector<KeyframedParticle> createFireball(float start_time){
  int n_fireball_partices = 100;
  std::vector<KeyframedParticle> fireball_particles;
  Keyframe keyframe1 = Keyframe();
    keyframe1.position = vec3(0, 0, 0);
    keyframe1.color = vec3(1, 1, 1);
    keyframe1.alpha = 0;
    keyframe1.size = 0.15;
  Keyframe keyframe2 = Keyframe();
    keyframe2.position = vec3(0, 0, 0);
    keyframe2.color = vec3(1, 0.6, 0);
    keyframe2.alpha = 1;
    keyframe2.size = 0.35;
  Keyframe keyframe3 = Keyframe();
    keyframe3.position = vec3(0, 0, 0);
    keyframe3.color = vec3(0.5, 0.1, 0);
    keyframe3.alpha = 1;
    keyframe3.size = 0.40;
  Keyframe keyframe4 = Keyframe();
    keyframe4.position = vec3(0, 0, 0);
    keyframe4.color = vec3(0.2, 0, 0);
    keyframe4.alpha = 0;
    keyframe4.size = 0.3;
  for(int i = 0; i < n_fireball_partices; i++){
    KeyframedParticle fireball_particle = KeyframedParticle();
    float random_time_offset = 0.3 * (rand() / (float)RAND_MAX);
    float random_displacement = 0.15 * (rand() / (float)RAND_MAX);
    vec3 random_target_position = normalize(randomUnitSphere()) * (0.5f + random_displacement);
    keyframe2.position = random_target_position;
    keyframe3.position = random_target_position;
    keyframe4.position = random_target_position;
    fireball_particle.times.push_back(start_time + 0 + random_time_offset);
    fireball_particle.times.push_back(start_time + 0.5 + random_time_offset);
    fireball_particle.times.push_back(start_time + 1 + random_time_offset);
    fireball_particle.times.push_back(start_time + 3 + random_time_offset);
    fireball_particle.keyframes.push_back(keyframe1);
    fireball_particle.keyframes.push_back(keyframe2);
    fireball_particle.keyframes.push_back(keyframe3);
    fireball_particle.keyframes.push_back(keyframe4);
    fireball_particle.setup();
    fireball_particles.push_back(fireball_particle);
  }
  return fireball_particles;
}

std::vector<KeyframedParticle> createRing(float start_time){
  int n_ring_partices = 70;
  std::vector<KeyframedParticle> ring_particles;
  Keyframe keyframe1 = Keyframe();
    keyframe1.position = vec3(0, 0, 0);
    keyframe1.color = vec3(1, 1, 1);
    keyframe1.alpha = 0;
    keyframe1.size = 0.15;
  Keyframe keyframe2 = Keyframe();
    keyframe2.position = vec3(0, 0, 0);
    keyframe2.color = vec3(1, 0.6, 0) * 0.75f;
    keyframe2.alpha = 1;
    keyframe2.size = 0.35 * 0.75f;
  Keyframe keyframe3 = Keyframe();
    keyframe3.position = vec3(0, 0, 0);
    keyframe3.color = vec3(0.5, 0.1, 0) * 0.75f;
    keyframe3.alpha = 1;
    keyframe3.size = 0.40 * 0.75f;
  Keyframe keyframe4 = Keyframe();
    keyframe4.position = vec3(0, 0, 0);
    keyframe4.color = vec3(0.2, 0, 0) * 0.75f;
    keyframe4.alpha = 0;
    keyframe4.size = 0.3 * 0.75f;
  for(int i = 0; i < n_ring_partices; i++){
    KeyframedParticle ring_particle = KeyframedParticle();
    float random_time_offset = 0.3 * (rand() / (float)RAND_MAX);
    float random_displacement = 0.15 * (rand() / (float)RAND_MAX);
    vec3 random_target_position = normalize(randomUnitDisk()) * (1.0f + random_displacement);
    random_target_position = vec3(random_target_position.x, 0, random_target_position.y);
    keyframe2.position = random_target_position;
    keyframe3.position = random_target_position * 1.1f;
    keyframe4.position = random_target_position * 1.3f;
    ring_particle.times.push_back(start_time + 0 + random_time_offset);
    ring_particle.times.push_back(start_time + 0.3 + random_time_offset);
    ring_particle.times.push_back(start_time + 0.5 + random_time_offset);
    ring_particle.times.push_back(start_time + 2 + random_time_offset);
    ring_particle.keyframes.push_back(keyframe1);
    ring_particle.keyframes.push_back(keyframe2);
    ring_particle.keyframes.push_back(keyframe3);
    ring_particle.keyframes.push_back(keyframe4);
    ring_particle.setup();
    ring_particles.push_back(ring_particle);
  }
  return ring_particles;
}

std::vector<KeyframedParticle> createDebris(float start_time){
  int n_debris_partices = 10;
  std::vector<KeyframedParticle> debris_particles;
  Keyframe keyframe1 = Keyframe();
    keyframe1.position = vec3(0, 0, 0);
    keyframe1.color = vec3(1, 1, 1);
    keyframe1.alpha = 1;
    keyframe1.size = 0.15;
  Keyframe keyframe2 = Keyframe();
    keyframe2.position = vec3(0, 0, 0);
    keyframe2.color = vec3(1, 0.6, 0) * 0.75f;
    keyframe2.alpha = 1;
    keyframe2.size = 0.35 * 0.75f;
  Keyframe keyframe3 = Keyframe();
    keyframe3.position = vec3(0, 0, 0);
    keyframe3.color = vec3(0.5, 0.1, 0) * 0.75f;
    keyframe3.alpha = 0;
    keyframe3.size = 0.35 * 0.75f;
  for(int i = 0; i < n_debris_partices; i++){
    KeyframedParticle debris_particle = KeyframedParticle();
    float random_time_offset = 0.3 * (rand() / (float)RAND_MAX);
    float random_displacement = 0.15 * (rand() / (float)RAND_MAX);
    vec3 random_target_position = randomUnitSphere();
    random_target_position = vec3(random_target_position.x, abs(random_target_position.y) + 0.2f, random_target_position.z);
    random_target_position = random_target_position * 3.0f;
    keyframe2.position = random_target_position;
    keyframe3.position = vec3(random_target_position.x, random_target_position.y - 0.3, random_target_position.z);
    debris_particle.times.push_back(start_time + 0);
    debris_particle.times.push_back(start_time + 1);
    debris_particle.times.push_back(start_time + 2);
    debris_particle.keyframes.push_back(keyframe1);
    debris_particle.keyframes.push_back(keyframe2);
    debris_particle.keyframes.push_back(keyframe3);
    debris_particle.setup();
    debris_particles.push_back(debris_particle);
  }
  return debris_particles;
}

std::vector<KeyframedParticle> createExplosion(float start_time){
  std::vector<KeyframedParticle> explosion_particles;
  std::vector<KeyframedParticle> fireball_particles = createFireball(start_time);
  std::vector<KeyframedParticle> ring_particles = createRing(start_time);
  std::vector<KeyframedParticle> debris_particles = createDebris(start_time);
  explosion_particles.insert(explosion_particles.end(), fireball_particles.begin(), fireball_particles.end());
  explosion_particles.insert(explosion_particles.end(), ring_particles.begin(), ring_particles.end());
  explosion_particles.insert(explosion_particles.end(), debris_particles.begin(), debris_particles.end());
  return explosion_particles;
}

class Viewer : public Window {
 public:
  Viewer() : Window() {}

  void setup() {
    setWindowSize(1000, 1000);
    renderer.setDepthTest(true);
    renderer.blendMode(agl::BLEND);
    std::vector<KeyframedParticle> explosion = createExplosion(0);
    particles.insert(particles.end(), explosion.begin(), explosion.end());
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
    string shader_name = "unlit";
    renderer.loadShader(shader_name, "../shaders/" + shader_name + ".vs", "../shaders/" + shader_name + ".fs");
    renderer.beginShader(shader_name);
    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

    azimuth += 0.005;

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
    renderer.setUniform("color", vec3(1, 1, 1));
    renderer.setUniform("alpha", 1.0f);

    bool all_dead = true;
    for(int i = 0; i < particles.size(); i++){
      if(!particles[i].isDead){
        all_dead = false;
      }
      particles[i].update(elapsedTime());
      renderer.push();
      renderer.setUniform("color", particles[i].color);
      renderer.setUniform("alpha", particles[i].alpha);
      renderer.translate(particles[i].position);
      renderer.scale(vec3(particles[i].size));
      renderer.sphere();
      renderer.pop();
    }
    if(all_dead){
      particles.clear();
      std::vector<KeyframedParticle> explosion = createExplosion(elapsedTime());
      particles.insert(particles.end(), explosion.begin(), explosion.end());
    }

    // renderer.translate(vec3(0, -0.2, 0));
    // renderer.scale(vec3(100, 1, 100));
    // renderer.setUniform("color", vec3(1, 1, 1));
    // renderer.setUniform("alpha", 1.0f);
    // renderer.plane();

    renderer.endShader();
  }

 protected:
  vec3 eyePos = vec3(0, 0, 3);
  vec3 lookPos = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  std::vector<KeyframedParticle> particles;
  bool left_mousedown = false;
  bool right_mousedown = false;
  bool shiftdown = false;
  float radius = 3.0f;
  float azimuth = 2.0f;
  float elevation = 0.25f;
};

int main(int argc, char** argv) {
  Viewer viewer;
  viewer.run();
  return 0;
}
