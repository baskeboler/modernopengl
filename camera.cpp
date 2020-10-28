#include "camera.h"

void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  front.y = sin(glm::radians(_pitch));
  front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

  _front = glm::normalize(front);

  _right = glm::normalize(glm::cross(_front, _worldUp));
  _up = glm::normalize(glm::cross(_right, _front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : _position{position}, _front{0, 0, -1.f},
      _movementSpeed{SPEED}, _worldUp{up}, _yaw{yaw}, _pitch{pitch},
      _mouseSensitivity{SENSITIVITY}, _zoom{ZOOM} {
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : _position{posX, posY, posZ}, _front{0.0f, 0.0f, -1.0f},
      _movementSpeed{SPEED}, _worldUp{upX, upY, upZ}, _yaw{yaw}, _pitch{pitch},
      _mouseSensitivity{SENSITIVITY}, _zoom{ZOOM} {
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(_position, _position + _front, _up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
  float v = _movementSpeed * deltaTime;
  if (direction == FORWARD)
    _position += _front * v;
  if (direction == BACKWARD)
    _position -= _front * v;
  if (direction == LEFT)
    _position -= _right * v;
  if (direction == RIGHT)
    _position += _right * v;
}

void Camera::processMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
  xoffset *= _mouseSensitivity;
  yoffset *= _mouseSensitivity;

  _yaw += xoffset;
  _pitch += yoffset;

  if (constrainPitch) {
    if (_pitch > 89.0f)
      _pitch = 89.0f;
    if (_pitch < -89.0f)
      _pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
  _zoom -= (float)yoffset;
  if (_zoom < 1.0f)
    _zoom = 1.0f;
  if (_zoom > 45.0f)
    _zoom = 45.0f;
}
