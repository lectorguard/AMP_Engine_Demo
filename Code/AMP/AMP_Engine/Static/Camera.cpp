// Copyright 2020 Simon Keller. All Rights Reserved.

#include "Camera.h"

glm::mat4 Camera::view = glm::mat4(1.0f);
glm::mat4 Camera::projection = glm::mat4(1.0f);
double Camera::lastTimeModel = -1;
double Camera::lastTimeProjection = -1;