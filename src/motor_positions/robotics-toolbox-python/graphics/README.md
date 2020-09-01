This folder contains the graphics functionality of the toolbox.
Instructions on how to use the graphical section of the toolbox below.
(Pictures to come)

# Scene Controls
3D Controls
 * Pan
   * W -> Forward
   * A -> Left
   * S -> Backward
   * D -> Right
   * SPACE -> Up
   * SHIFT -> Down
 * Spin
   * CTRL + LMB -> Free spin
   * Left -> Left
   * Right -> Right
   * Up -> Up 
   * Down -> Down
   * Q -> Roll Left
   * E -> Roll Right
 * Zoom
   * Scrollwheel
   
2D Controls
 * Pan
   * SHIFT + LMB -> Free pan
   * W -> Up
   * A -> Left
   * S -> Down
   * D -> Right
 * Spin
   * Left -> Left
   * Right -> Right
   * Up -> Up 
   * Down -> Down
   * Q -> Roll Left
   * E -> Roll Right
 * Zoom
   * Scrollwheel
   

# How To
## Importing
To use the graphics, simply import it. For these examples, it is assumed the graphics are imported into the namespace 'gph'.
```python
import graphics as gph
```

## Common Functionality
VPython has its own data types that can be used. Firstly, the `radians()`, and `degrees()` functions convert between radians and degrees.
The `vector` class is also very crucial to the graphics. It can either represent a vector or a 3D point.

For convenience, some functions and variables are provided for easy use. `wrap_to_pi()` takes in an angle, and specification on degrees or radians. It returns the respective angle between -pi and pi.
Three vectors are also supplied for readability to ensure correct axes are used when referencing. `x_axis_vector`, `y_axis_vector`, `z_axis_vector` can be used to get vectors of an object, for example.
```python
# Wrap an angle (deg) to the range [-pi pi]. use "rad" instead of "deg" for radian angles.
gph.wrap_to_pi("deg", 450)
# Obtain the Z vector representation of the robot link
my_link.get_axis_vector(z_axis_vector)
```

## Setting Up The Scene
Any use of VPython objects requires a scene.

To create a scene to draw object to, a canvas must be created. Upon creation, a localhost http server will be opened. 

Different attributes can be supplied to the function for some customisation. The display width, height, title, and caption can be manually input. Lastly, a boolean representing the grid visibility can be set.

Firstly, decide whether a 3D or 2D world is required (even though the 2D is represented in a 3D world, it will have 2D capabilities)
```python
# Create a default canvas (360*640, with grid displayed, no title or caption)
g_canvas = gph.GraphicsCanvas3D()
g_canvas = gph.GraphicsCanvas2D()

# Alternatively create a grid with specified parameters
g_canvas = gph.GraphicsCanvas3D(height=768, width=1024, title="Scene 1", caption="This scene shows...", grid=False)
g_canvas = gph.GraphicsCanvas2D(height=768, width=1024, title="Scene 1", caption="This scene shows...", grid=False)
``` 

The scene has a GUI underneath the canvas. It gives an interface to toggle graphics and visibilities.
The same functionality can be done in code as will be mentioned.

3D options:
 * Toggle the UI mode between Canvas Controls, and a Teachpanel
   * The Teachpanel will have a slider for each joint to rotate between all available angles for that joint
 * Choose which robot to edit
 * Toggle robot/frame visibility
 * Change robot opacity
 * Toggle grid visibility
 * Delete a robot from the scene
 * Clear all robots visuals from the scene
 * Toggle camera lock
 * Toggle grid dynamic/static positioning

2D options:
 * TBA

\
The GraphicsGrid object has functions to toggle grid visibility.
```python
# Turn off the grid display
g_canvas.grid_visibility(False)
```
Now that the scene is created, a robot must be created to be displayed.

At anytime you can clear the scene of all robots (The grid will remain if visible). Note: This will note delete the objects,
they still exist, and can be rendered visible afterwards. However, overwriting/deleting the variables will free the memory.
If an object is overwritten/deleted while still visible, the objects will remain in the scene.

Isolated joint objects will not be cleared. Only robots in the scene.
```python
g_canvas.clear_scene()
```

# 3D Functionality
## Creating Robots
If you want to use the example puma560 robot, simply call the creation function that will return a `GraphicalRobot` object.
It will be displayed in the scene that is provided.
```python
# Import the puma560 models and return a GraphicalRobot object
from roboticstoolbox.models.graphical_puma560 import import_puma_560
puma560 = import_puma_560(g_canvas)
```
Otherwise, robots can be manually created using the `GraphicalRobot` class.
The joints for the robot can be manually or automatically created.
Creation takes in the canvas object to be displayed in, as well as a name for the robot.

The `GraphicalRobot` optionally takes in a `SerialLink` object. If given in the initialiser, no joints have
to be made, they are automatically created. The name clause is also overridden by the name specified in the SerialLink object.

Firstly, create a `GraphicalRobot` object
```python
# Create an empty robot
my_robot = gph.GraphicalRobot(g_canvas, 'My Robot')

# Create a robot based on a SerialLink object.
my_robot = gph.GraphicalRobot(g_canvas, '', seriallink=serial_link_obj)
```
Now we can add joints. The joints added to the robot act like a stack. First joints added will be last to be removed (if called to).

### Automatically
If you wish to automatically add joints, use `append_link()`. Add the joints from base to gripper.
This function takes in three arguments.

Firstly, the type of joint: rotational, prismatic, static, or gripper.
The input is the first letter of the type (case-insensitive). e.g. (rotational = "r" or "R").

Next is the initial pose (SE3 type) of the joint.

The 'structure' of the robot. This variable must either be a `float` representing the joint length, or a `str`
representing a full file path to an STL file.

If a `float` length is given, a custom rectangular object will represent it in the scene. Otherwise if a `str` path is given,
the STL object will be loaded in and used in place of a rectangular joint.

Finally, an optional parameter `axis_through` can be used to specify which (local) axis the robot arm is drawn along
It is of a numpy array type, and defaults to `array([0, 1, 0])` (y-axis).

```python
from numpy import array

# Append a default base joint of length 2.
my_robot.append_link('r', SE3(), 2.0, axis_through=array([0, 1, 0]))

# Append an STL obj rotational joint.
my_robot.append_link('r', SE3(), './path/to/file.stl')
```

### Manually
Manually adding joints consists of creating a Joint object to add to the robot.
The types that can be created are identical to previously mentioned in the Automatic section.

`RotationalJoint`, `PrismaticJoint`, `StaticJoint`, `Gripper` are the class names of the different joints.

To create a joint, each class requires the same variables as the automatic version (minus the joint type string).
Also included must be the scene to display the joint in, similar to importing the Puma560 model.
The `axis_through` parameter is still optional.

Although the creation process is "the same", manually creating a joint lets you more easily update any graphical issues associated with it.
For example, the STL you want to load may not be orientated/positioned correctly (How to fix is mentioned later)

WARNING: The joint must be in the same scene as the robot.

```python
# Create two basic rotational links
link1 = gph.RotationalJoint(SE3(), 1.0, g_canvas, axis_through=array([1, 0, 0]))
link2 = gph.RotationalJoint(SE3(), 1.4, g_canvas)

# Add to the robot
my_robot.append_made_link(link1)
my_robot.append_made_link(link2)
``` 

To remove the end effector joint, use the `detach_link()` function. Acting like a stack, it will pop the latest joint created off the robot.
```python
# Remove the end effector joint
my_robot.detach_link()
```

## Applying Textures / Colours / Opacity
Joints can be coloured, given textures, or both. Using a joint object, calling `set_texture()` will apply the given options.
Textures are given as `str` paths to a local file, or a web hosted image. Colours are input as a list of RGB values.
These values must be normalised from 0 to 1. When both are given, the texture gets colour shifted.
Not supplying a texture will remove any texture already supplied.
Not supplying a colour will set it to white (default).

**WARNING:** If the texture can't be loaded, the object will have no texture
(appear invisible, but not set as invisible).

**WARNING:** If the image has a width or height that is not a power of 2
(that is, not 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, etc.),
the image is stretched to the next larger width or height that is a power of 2.

```python
new_rot = gph.RotationalJoint(SE3(), 1.0, g_canvas)

# Load a sample texture
new_rot.set_texture(texture_link="https://s3.amazonaws.com/glowscript/textures/flower_texture.jpg")

# Green shift the texture
new_rot.set_texture(colour=[0, 0.75, 0],
                    texture_link="https://s3.amazonaws.com/glowscript/textures/flower_texture.jpg")

# Remove the texture and red shift
new_rot.set_texture(colour=[1, 0, 0])

# Remove all details
new_rot.set_texture()
```

Changing the opacity can help show reference frames that are hidden by the robot graphics.
The opacity values must be between 0 and 1 inclusively.
```python
# Change a joint opacity to near invisible
new_rot.set_transparency(0.3)

# Change a robot to near invisible
my_robot.set_transparency(0.3)
```

## Importing an STL object
STL files may not be correctly positioned/oriented when loaded in.
Depending on where the object triangles are configured from the file, the origin of the object may not be where intended.

When loaded in, the origin is set (by default) to (0, 0, 0).

Upon observation (through VPython or 3D editor software), you can find the coordinates of the origin in respect to the world.

A function `set_stl_joint_origin()` is supplied to change the origin.
This method is part of all joint types. It takes two 3D coordinates representing the world coordinates of where the desired origin currently is, and where the desired origin should be.

For example, if an STL object loads in and the origin is below (-z axis) where it should be, and the origin is at the bottom of the object, the following code will translate it up and set the origin.
```python
# Load the mesh in the link
link = gph.RotationalLink(SE3(), './path/to/file.stl', g_canvas)

# Obtain the graphical object to help with coordinates
# May not be necessary if you already know the 3D coordinates
stl_obj = link.get_graphic_object()

# Z origin is below where the current position is. (this e.g. is at bottom of object)
stl_obj_z_origin = stl_obj.pos.z - stl_obj.width / 2

# 3D pos of where the origin is
stl_obj_current_origin_location = vector(stl_obj.pos.x, stl_obj.pos.y, stl_obj_z_origin)

# 3D pos of where the origin should be set in the world
stl_obj_required_origin_location = vector(stl_obj.pos.x, stl_obj.pos.y, 0)

# Move the object to place origin where it should be, and apply the new origin to the object
link.set_stl_joint_origin(stl_obj_current_origin_location, stl_obj_required_origin_location)
```

## Using A GraphicalRobot
The robot class has two functions that handle the display. One function each to toggle the visibility for the joints and reference frames.
```python
# Turn off the robots reference frame displays
my_graphic_robot.set_reference_visibility(False)

# Toggle the robot visibility
my_graphic_robot.set_robot_visibility(not my_graphic_robot.is_shown)
``` 

To update the joint positions, use the `set_joint_poses()` function. It takes in a list of SE3 objects for each of the joints.
There must be 1 pose for each joint, in order from base to gripper (order of appending in creation)
```python
# Set all joint poses to a random configuration
# Assuming 3 joint robot
my_graphical_robot.set_joint_poses([
    SE3().Rand(),
    SE3().Rand(),
    SE3().Rand()
])
```

Alternatively, an `animate` function allows the robot to iterate through given poses to simulate movement.
Given an array of poses (per frame), and a frame rate, the robot will transition through each pose.
```python
my_graphical_robot.animate([
    [pose1, pose2, pose3],  # Frame 1
    [pose1, pose2, pose3],  # Frame 2
    [pose1, pose2, pose3],  # Frame 3
    [pose1, pose2, pose3]], # Frame 4
    4)  # 4 FPS
```

Lastly, a print function `print_joint_poses()` will print out the current poses of all joints.
```python
# Print joint poses
my_graphical_robot.print_joint_poses()
```

# 2D Functionality
## Plotting
Plotting lines in 2D works the same way as it does in MATLAB plotting.
If you are familiar with the plot syntax, you can effectively skip this part.

The `plot()` function takes in lists of axis values, and an optional string for plot options.

If given one axis of data, it will plot along the Y axis, with respect to index on the X axis.
If given two axes of data, it will plot first list (X) by second list (Y).

The string option input is the same as MATLAB's plot options.
The string can contain up to three options (one of each): 
1. Line type
2. Marker type
3. Colour

        
      Colour                Marker Type           Line Type
    b     blue          .     point              -     solid
    g     green         o     circle             :     dotted
    r     red           x     x-mark             -.    dashdot
    c     cyan          +     plus               --    dashed
    m     magenta       *     star             (none)  no line
    y     yellow        s     square
    k     black         d     diamond
    w     white         v     triangle (down)
                        ^     triangle (up)
                        <     triangle (left)
                        >     triangle (right)
                        p     pentagram
                        h     hexagram
                      (none)  no marker

Notes:
* If you do not specify a marker type, plot uses no marker.
* If you do not specify a line style, plot uses a solid line (unless a marker type is given, then no line).
* Options can be in any order

```python
# Plot a list of values in default options
g_canvas.plot([1, 2, 3, 4])

# Plot a list of values in red dashed lines
g_canvas.plot([1, 2, 3, 4], 'r--')  # '--r' is also valid

# Plot a list of values with no line between, and diamond markers in blue
g_canvas.plot([1, 2, 3, 4], 'bd')  # 'db' is also valid

# Plot X by Y, in green, with cross markers, dashdot line, in yellow
g_canvas.plot([3, 5, 2, 7], [6, 2, 8, 4], 'gx-.')  # 'x-.g' (etc) is also valid
```

## 2D Objects
Similar to a robot in the 3D scene, you can create a 2D object to move around the scene.
Currently, only shapes are supported for the 2D object, but future additions will allow STLs.
Object position/graphic update functions to come.

The object initialiser takes in an SE2 pose, the scene to draw in, it's shape and colour.

```python
# Position at (1, 1)
se2 = SE2(x=1, y=1, theta=0)
colour = [0, 0, 0]  # Black
shape = '*'

my_object = gph.Object2D(se2, g_canvas, shape, colour)
```