#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
using namespace std;
using namespace glm;
using namespace Assimp;


//It is a very bad solution but we don't have a event or callback system, so this is the solution for now!
bool ShouldApplication_Close = false;

//Some basic functionality to do debugging!
#define GET_VARIABLE_NAME(Variable) (#Variable)