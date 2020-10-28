#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT }; // Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
  void updateCameraVectors();

public:
  glm::vec3 _position;
  glm::vec3 _front;
  glm::vec3 _up;
  glm::vec3 _right;
  glm::vec3 _worldUp;

  float _yaw;
  float _pitch;

  float _movementSpeed;
  float _mouseSensitivity;
  float _zoom;

  Camera(glm::vec3 position = {0.0f, 0.0f, 0.0f},
         glm::vec3 up = {0.0, 1.f, 0.0}, float yaw = YAW, float pitch = PITCH);

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);
  glm::mat4 getViewMatrix();

  void processKeyboard(CameraMovement direction, float deltaTime);
  void processMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);

  void processMouseScroll(float yoffset);
};

#endif // CAMERA_H
