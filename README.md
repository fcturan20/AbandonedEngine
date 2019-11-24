# TuranEngine
A game engine I was working in summer and will continue next summer. First development target is the Renderer and UI, then Game Object and ECS-Fiber Task systems. Only tested for Windows, but I think it is easy to port to other platforms using CMake or Premake. If you want to run the TuranEditor without compiling, open bin/TuranEditor/TuranEditor.exe.

# General Architecture:
TuranAPI: A core functionality library that all other projects should inherit. It has its own libraries too, to allow user to not include an used feature's header. For example, TuranAPI has FileSystem functionality but if you don't want to use this functionality in your applications, if you don't include "API_FileSystem.h" no FileSystem functionality will be included to your application.
GFX_API: A functionality library that all other graphics languages should specify. That means, GFX_API is only an interface to allow applications to have multiple GLs (D3D11, OpenGL, Vulkan etc.). GFX_API will be used to define RenderGraph (Completed render pipeline that includes G-Buffer, Post-Proccessing etc.) in TuranEngine. 
OpenGL3: A GL library that uses OpenGL3 to define GFX_API functionality. 
TuranEngine: A core functionality library that can be used to access all of the Graphics, Physics (not implemented) etc. .
TuranEditor: For now, just a Resource Compiler interface (Content Browser) because I can't connect Game and TuranEditor. 
Game: An empty project, just to remind myself that I want to make a Game Engine.

# Project Features
## TuranAPI functionalities:
1) A FileSystem is created in TuranAPI::File_System namespace. This system uses Flatbuffer infrastructure to allow users to create efficient binary and JSON files. Only binary is supported for now, but when most of the UI is done, it will be supported. 
2) Dear IMGUI is entegrated to the TuranAPI to allow all of the applications to have IMGUI interface. But a GFX_IMGUI has to be provided to render IMGUI, don't forget that.
3) A profiling system is created to profile functions and scopes. This is not finished or debugged and also need a monitor window to visualize the data.
	File System and Flatbuffer functionalities:
1) FileSystem has file I/O operations, binary game resource (Scene, Model, Material Type, Texture etc.) read/write operations and GameComponent system.
2) This class uses Google Flatbuffer API because Flatbuffer is a light-weight, easy to use, no parsing needed data storage API. 
3) If you want to create a project uses TuranAPI and you want to store data in disk, you can use FileList resource type for it, better to look at Write_a_File_toDisk() and Load_Resources_fromFileList() functions in FileSystem class.
4) GameComponent system is in the FileSystem, because we want to store GameComponents for each Scene in our applications.
5) A Material Type is a Shader Program that consist of Vertex and Fragment Shader. Material Type's Uniform List can be used to pass uniform datas to Material_Instances.
6) A Material Instance stores uniform datas to pass to shaders.
7) A Static Model stores meshes that store vertex attributes.
8) A Texture stores texture data and texture's properties (Mipmap Filtering, Wrapping etc)
9) A Scene stores GameComponents to create a world, but world doesn't have a functionality.
	Dear IMGUI entegration:
1) IMGUI will control all over the TuranEditor, so we are giving all of the inputs to IMGUI not to make systems more complex. When we need input data, Dear IMGUI will provide us (i guess).
2) Dear IMGUI is not directly in the hands of users. Dear IMGUI functionality is only in the TuranAPI's DLL. If you want to use IMGUI, you have to use IMGUI class that I defined in the TuranAPI::IMGUI namespace. This class only extends when a functionality is needed.
3) If you want to use any of the IMGUI classes (IMGUI_WINDOW to create a window and define its context or IMGUI_GFX to give GL renderer access to IMGUI), you can include "API_IMGUI.h".

## GFX_API functionalities:
	1) This class is the interface for Application-GPU connections. Window creation, Monitor detection, Renderer creation etc.
	2) Window's are handled by IMGUI for TuranEditor, but you can create your own GLFW window to render independently from IMGUI.
	3) GFX_API has GFX_Renderer* that defines GL API functionality. But this pointer initialized at GFX_API derived class (Like OGL3_SYS in OpenGL3 project).
	4) GFX_Renderer class is the interface for rendering operations (Binding shaders, creating textures, drawing triangles etc).
	5) If you want to render something in your applications that uses a GFX_API derived project (OpenGL 3 project for example), you should add GFX_API and TuranAPI to your project and use a GFX_RenderGraph derived class to define your rendering pipeline. And, you should bind the class to GFX_API to activate rendering operations.

## TuranEditor:
1) TuranAPI's IMGUI is used to create Editor's UI. Editor UI only supports Content Browser properly for now. Other windows are Scene Editor, Properties, dear IMGUI's Demo and Metrics windows.
2) ResourceCompiler folder has classes to import 3rd party resources (.obj, .vert,.frag etc). Then, these classes sends the imported resources to FileSystem to compile data into Flatbuffer-Binary format and store the data in specified folder.


# Not Completed Features: 
1) Camera Component support. Camera can be added to scene, but changes in Properties Window doesn't save to disk. GFX_API doesn't support Camera_Component, rendering won't be affected by Camera. I want to specify which Camera_Component G-Buffer will use to render etc.
2) IMGUI class doesn't have all of the IMGUI's functionalities because I didn't need in the time. But one thing I wish IMGUI will support is creating IMGUI as main window, instead of using at least one GLFW window.
3) GFX_Renderer doesn't have all of the functionalities and any algorithm (sort, merge etc.) to use in a RenderGraph.
4) TuranEngine doesn't have any inputs now, all of the inputs passed to IMGUI. I want to get some inputs (for example: when clicked on Viewport, i want to access mouse and keyboard) from IMGUI.
5) Content Browser opens Property window when an item is clicked on, but I want it to happen on double-click. I also want to use UE4 like Content Browser layout, not a simple list.
6) Shader Editor doesn't have any affect, just a simple window. I want it to work properly.
7) IMGUI has "Lots of End in the same time!" issue sometimes when some tabs attached. IMGUI's or mine fault.
8) Properties window doesn't have much functionality and doesn't show much of the info, I want to add them lots of things.
9) Destruction operations doesn't work properly. For example, A static model resource can be deleted but its GPU resource isn't deleted and also GFXI_Mesh datas may be alive in draw passes. A proper data handling pipeline should be added.
10) Object loading has bugs, only loads Nanosuit as is. I think it is because of my "Merge same material indexed meshes" while importing OBJs.

# Easy-to-Add Features:
1) Material Instance display on a Sphere in Properties Window like UE4
2) Properties Window should allow to specify Component names and Material Instances etc.
3) Input handling for Viewport (Scene View).
4) Support for various data type sliders
5) UI specified colored proccess report for console app

# Big Future Features:
Note: These features are areas where I had never experimented, so please calm if I tell something wrong. I want to work on these in university.
1) Fiber Task and ECS systems (More like ManaEngine's ECS way). Also, Dependency based Gameplay running system.
2) Run-Time language (One of C++ DLL system, Lua, or custom language to compile C++ code) to define GameObjects and Render Passes (I think GFX_Renderer can support it, because it already gives us the functions)
3) Dependency based RenderGraph or fully manuel barrier creation in RenderGraph Editor by nodes.
4) GFX_API derived Software Renderer to do some rendering on CPU (Like software occlusion culling).
5) Visual UI designer for creating UIs for TuranEditor. Something like Android Studio (Create UI in a visual editor and for each functionality, visual editor gives you functions to define). With dear IMGUI support, engine developer can already build nice UIs. But for the people ever used dear IMGUI, a Visual UI designer would be nice (I want to experiment with it, even it's not necessary for no one).
6) CPU and GPU ray casters for Game_Objects. GPU ray casting would be a complicated thing, I don't even think it will happen.
7) Basic physics system for general game requirements, not a fully support (for example: Hydro-Dynamics, Cloth and Soft-Body Dynamics, Destruction Dynamics, Car Dynamics etc.)
8) Loading and playing Animation, creating Procedural Animations.

# After-Release Mega Features:
Note: These features are far from my galaxy to fully support as opposite of others, these are just things if the engine is used by many people, I have friends to work with and also happy with completed Big Future Features list.
1) Networking for Gameplay (Online support for games)
2) Full Physics engine support (PhysX, Bullet or written by me)
3) Source Control
4) Unit Testing Framework (I don't even know what it is, just heard about it)
