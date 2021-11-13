# SwitchSlide
Like a slide rule, but for Switch.

## Just a very basic edit of switchbrew's [simplegfx example](https://github.com/switchbrew/switch-examples/blob/master/graphics/simplegfx/source/main.c) and [touch-screen example](https://github.com/switchbrew/switch-examples/blob/master/hid/touch-screen/source/main.c).

# [How to use a slide rule.](https://www.sliderulemuseum.com/SR_Class/OS-ISRM_SlideRuleSeminar.pdf)

![](https://user-images.githubusercontent.com/36782760/141604382-1a0f2fd2-ddb3-4785-abec-1b3125e6f2a6.png)

### Issues:
* Slowly sliding your finger horizontally across the screen is kind of jittery and makes lining up your calculation a bit of a pain. To counter this, slide at a normal speed and a steep vertical angle. The vertical component of the slide will effectively just get ignored but the small horizontal component will always be accounted for.
* The scales won't line up perfectly when slid relative to one another because I only lined up the gradations with the nearest pixel. So for example, the 3.4 line would go at x position 1280*log₁₀(3.4) = 680.293, so I just put it at x coordinate 680. They should all be close enough to the true value that the power of estimation will give you accurate enough results.

### Take advantage of the power of iteration to get increasingly accurate results. For example, say you wanted to know 590÷101.
1. Estimate what the answer should be. 590 is about 600 and 101 is about 100, so 590÷101 should be about 6.
2. Use the slide rule to get an answer of about 5.84.
3. 5.84×101 = 589.84. This means our error is (590-589.84)÷101 = 0.16÷101.
4. Use the slide rule to evaluate 0.16÷101 to be about 0.001584.
5. Add the error correction to our first calculation to get 590÷101 = 5.841584.
6. 5.841584×101 = 589.999984. If this still isn't accurate enough for what you're doing, iterate again. In this case though, you could just notice that the next iteration would be a power of 10 times a previous iteration, meaning you've already found the repeating decimal expansion.

## Keybinds:

Button | Function
-------- | --------
Plus (+) | Go back to HBMenu
Touch Screen | Move the slide/hairline.
A | Switch between moving the slide and hairline.
B | Reset the slide position.
X | Reset the hairline position.

The scales from top to bottom are:
1. Double Logarithmic (1 to 10 to 100)
2. Folded Single Logarithmic with index at Pi (π to 10, 10 = 1, 1 to π)
* Blue line denoting boundary between slide bit and top stator
3. Folded Single Logarithmic with index at Pi (π to 10, 10 = 1, 1 to π)
4. Red Inverse Single Logarithmic (10 to 1)
5. Single Logarithmic (1 to 10)
* Blue line denoting boundary between slide and botom stator bit
6. Single Logarithmic (1 to 10)
7. Linear (0 to 1)

Fuck OpenGL and gpu compute, software render is all I need.
