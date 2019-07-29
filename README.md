# TuranEngine
A Game Engine I'm working on at my free-times

# Features:
There are lots of features, but for now I don't have time to write all of them at once!

## Controller Features:
1. Keyboard and Mouse Controller systems that stores input datas. But input datas are taken with GLFW by GFX!
2. Mouse Controller has Mouse Position Recording() that start a recording process for the calling function! This should be used for cases like when right-click is pressed, calculate the start position of cursor!
3. Mouse Controller has Return Position Offset() that returns position offset from last frame to this frame, for the given record! This should be used for cases like while you're clicking right click, get position offset of mouse to change the view direction of Camera!
4. Mouse Controller has Stop Position Offset() that stop recording offset! This should be called when you release right-click not to move Camera!
5. These Position Offset() functions also support cursor mode changing! This is to support when you right-click to move Camera, Input goes to Unlimited Surface mode to allow you to change your cursor position infinitely.
