# SwitchSlide
Like a slide rule, but for Switch.

All I need now is to figure out some scheme to be able to move the cursor and slide independently.

[How to use a slide rule.](https://www.sliderulemuseum.com/SR_Class/OS-ISRM_SlideRuleSeminar.pdf)

~~This might not be too bad if I can figure out how to make rectangles and apply textures with OpenGL.~~
Fuck OpenGL and gpu compute, software render is all I need.
![](https://user-images.githubusercontent.com/36782760/140880806-4bd9d857-4db1-4a09-a6aa-9d42377ae4d1.png)

The scales from top to bottom are:
1. Double Logarithmic (1 to 10 to 100)
2. Folded Single Logarithmic with index at Pi (π to 10, 1 to π)
* Blue line denoting boundary between slide bit and top stator
3. Folded Single Logarithmic with index at Pi (π to 10, 1 to π)
4. Red Inverse Single Logarithmic (10 to 1)
5. Single Logarithmic (1 to 10)
* Blue line denoting boundary between slide and botom stator bit
6. Single Logarithmic (1 to 10)
7. Linear (0 to 1)

There will also be a green cursor that you use to line up calculations
