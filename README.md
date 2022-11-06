# HierarchicalTransforms
This program is an example of demonstrating hierarchical transformations in OpenGL.
Below is a figure of the designed robot.

![image](https://user-images.githubusercontent.com/39425103/200183653-a115f39e-4d59-4451-8ad5-11ba9acf6f70.png)

## Testing Environment
* Microsoft Visual Studio 2019 Community Edition

## How to Run

The dependencies are packed in the `Dependencies/` directory, which we include the following libraries:
* [freeglut 3.0.0](https://www.transmissionzero.co.uk/software/freeglut-devel/)
* [glew 2.1.0](https://glew.sourceforge.net/index.html)


Simply open the `HierarchicalTransforms.sln` file in Visual Studio to open the project.
As long as OpenGL is configured on your PC (which is usually installed along with Microsoft Visual Studio), it should run without problems.
Press `<Ctrl> + <F5>` to build without debugging.

## Description
Use the arrow keys `<UP> <DOWN> <LEFT> <RIGHT>` to rotate and move the camera around the robot.


### Running Robot
Press `<F5>` to set the robot to a running posture.

Press `<F6>` to toggle **Running Mode**, which makes the robot sprint.

Press `<F7>` to show or hide the moving ground during running mode.

![gif](https://media.giphy.com/media/MUkQ0SjpPv2DP2UR1o/giphy.gif)
