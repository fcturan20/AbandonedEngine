#pragma once
/*
This header for application uses Turan Engine like Editor or Game.
Engine is a library that allows user to use Engine's Modules (Like RHI, RenderGraph, AI, Physics etc.) and ECS system; create systems depend on them (Like a Game uses ECS).
User can copy these Modules because they are DLLs and include great documentation about themselves on how to add Module to your project!

If you want to use TuranEngine in your project, you have to include other Engine Modules as well. Otherwise, you have to remove them in all engine.
If you want to remove Modules, All Modules are imported in "Core/Engine_Core.h", so this is a good place to start removing.
If you want to import TuranEngine to your project, all you have to do is #include this header as well as Engine's DLL and Non-Removed Modules' DLLs.
*/

#include "Core/Engine_Core.h"