from vpython import vector, compound, mag, box
from numpy import sign, ceil
from graphics.graphics_text import update_grid_numbers
from graphics.graphics_object2d import Object2D
from spatialmath import SE2


class GraphicsGrid:
    """
    This class holds the current grid displayed in the canvas

    :param scene: The scene in which to add the grid
    :type scene: class:`vpython.canvas`
    """

    def __init__(self, scene):

        # Save the scene the grid is placed in
        self.__scene = scene
        self.__is_3d = True

        self.__relative_cam = True
        self.__num_squares = 10

        # Save the current camera settings
        self.camera_pos = self.__scene.camera.pos
        self.camera_axes = self.__scene.camera.axis
        self.__focal_point = [
            round(self.__scene.center.x),
            round(self.__scene.center.y),
            round(self.__scene.center.z)
        ]

        # Private parameters for indexing in grid_object
        self.__xy_plane_idx = 0
        self.__xz_plane_idx = 1
        self.__yz_plane_idx = 2
        self.__planes_idx = 0
        self.__labels_idx = 1

        # Initialise a grid object
        # grid_object[0] will always be the 3 plane graphics. [XY, XZ, YZ] (alphabetical in order and connection)
        # grid_object[1] will always be the labels. There is always a certain number of indices.
        # Order is [x-plane numbers, "X", y-plane numbers, "Y", z-plane numbers, "Z"]
        self.grid_object = [[], []]
        self.__init_grid()

        # Bind mouse releases to the update_grid function
        self.__scene.bind('mouseup keyup', self.update_grid)

    def __init_grid(self):
        """
        Initialise the grid along the x, y, z axes.
        """
        the_grid = self.__create_grid_objects()
        self.grid_object[self.__planes_idx] = the_grid

        # Update the labels instead of recreating them
        update_grid_numbers(self.__focal_point, self.grid_object[self.__labels_idx], self.__num_squares, self.__scene)

    def __create_grid_objects(self):
        """
        Draw a grid along each 3D plane, that is closest to the camera.

        :return: List of the three drawn axes.
        :rtype: `list`
        """

        # Initial conditions
        xz_lines = []
        xy_lines = []
        yz_lines = []
        camera_axes = self.camera_axes
        # Locate centre of axes
        if self.__relative_cam:
            x_origin, y_origin, z_origin = round(self.__scene.center.x),\
                                           round(self.__scene.center.y),\
                                           round(self.__scene.center.z)
            self.__focal_point = [x_origin, y_origin, z_origin]
        else:
            x_origin, y_origin, z_origin = self.__focal_point[0], \
                                           self.__focal_point[1], \
                                           self.__focal_point[2]

        #   CAMERA AXES |  DISPLAYED GRID | XZ PLANE | XY PLANE | YZ PLANE
        #      x,y,z    |      x,y,z      |   x,z    |    x,y   |    y,z
        #  -------------+-----------------+----------+----------+----------
        #      -,-,-    |      +,+,+      |   +,+    |    +,+   |    +,+
        #      -,-,+    |      +,+,-      |   +,-    |    +,+   |    +,-
        #      -,+,-    |      +,-,+      |   +,+    |    +,-   |    -,+
        #      -,+,+    |      +,-,-      |   +,-    |    +,-   |    -,-
        #      +,-,-    |      -,+,+      |   -,+    |    -,+   |    +,+
        #      +,-,+    |      -,+,-      |   -,-    |    -,+   |    +,-
        #      +,+,-    |      -,-,+      |   -,+    |    -,-   |    -,+
        #      +,+,+    |      -,-,-      |   -,-    |    -,-   |    -,-
        # min = -num_squares or 0, around the default position
        # max = +num_squares or 0, around the default position
        # e.g. at the origin, for negative axes: -10 -> 0, positive axes: 0 -> 10
        min_x_coord = x_origin + int(-(self.__num_squares / 2) + (sign(camera_axes.x) * -1) * (self.__num_squares / 2))
        max_x_coord = x_origin + int((self.__num_squares / 2) + (sign(camera_axes.x) * -1) * (self.__num_squares / 2))

        min_y_coord = y_origin + int(-(self.__num_squares / 2) + (sign(camera_axes.y) * -1) * (self.__num_squares / 2))
        max_y_coord = y_origin + int((self.__num_squares / 2) + (sign(camera_axes.y) * -1) * (self.__num_squares / 2))

        min_z_coord = z_origin + int(-(self.__num_squares / 2) + (sign(camera_axes.z) * -1) * (self.__num_squares / 2))
        max_z_coord = z_origin + int((self.__num_squares / 2) + (sign(camera_axes.z) * -1) * (self.__num_squares / 2))

        # XZ plane
        for x_point in range(min_x_coord, max_x_coord + 1):
            # Draw a line across for each x coord, along the same y-axis, from min to max z coord
            xz_lines.append(create_line(
                vector(x_point, y_origin, min_z_coord),
                vector(x_point, y_origin, max_z_coord),
                self.__scene
            ))
        for z_point in range(min_z_coord, max_z_coord + 1):
            # Draw a line across each z coord, along the same y-axis, from min to max z coord
            xz_lines.append(create_line(
                vector(min_x_coord, y_origin, z_point),
                vector(max_x_coord, y_origin, z_point),
                self.__scene
            ))

        # XY plane
        for x_point in range(min_x_coord, max_x_coord + 1):
            # Draw a line across each x coord, along the same z-axis, from min to max y coord
            xy_lines.append(create_line(
                vector(x_point, min_y_coord, z_origin),
                vector(x_point, max_y_coord, z_origin),
                self.__scene
            ))
        for y_point in range(min_y_coord, max_y_coord + 1):
            # Draw a line across each y coord, along the same z-axis, from min to max x coord
            xy_lines.append(create_line(
                vector(min_x_coord, y_point, z_origin),
                vector(max_x_coord, y_point, z_origin),
                self.__scene
            ))

        # YZ plane
        for y_point in range(min_y_coord, max_y_coord + 1):
            # Draw a line across each y coord, along the same x-axis, from min to max z coord
            yz_lines.append(create_line(
                vector(x_origin, y_point, min_z_coord),
                vector(x_origin, y_point, max_z_coord),
                self.__scene
            ))
        for z_point in range(min_z_coord, max_z_coord + 1):
            # Draw a line across each z coord, along the same x-axis, from min to max y coord
            yz_lines.append(create_line(
                vector(x_origin, min_y_coord, z_point),
                vector(x_origin, max_y_coord, z_point),
                self.__scene
            ))

        # Compound the lines together into respective objects
        xz_plane = compound(xz_lines)
        xy_plane = compound(xy_lines)
        yz_plane = compound(yz_lines)

        # Combine all into one list
        grid = [None, None, None]
        grid[self.__xy_plane_idx] = xy_plane
        grid[self.__xz_plane_idx] = xz_plane
        grid[self.__yz_plane_idx] = yz_plane

        return grid

    def __move_grid_objects(self):
        """
        Reusing the current assets, move the planes to the new origins.
        """
        camera_axes = self.camera_axes
        # Locate centre of axes
        if self.__relative_cam:
            x_origin, y_origin, z_origin = round(self.__scene.center.x), \
                                           round(self.__scene.center.y), \
                                           round(self.__scene.center.z)
            self.__focal_point = [x_origin, y_origin, z_origin]
            # Convert focal point for 2D rendering. Puts focus point in centre of the view
            if not self.__is_3d:
                self.__focal_point = [val - int(self.__num_squares / 2) for val in self.__focal_point]
                x_origin = self.__focal_point[0]
                y_origin = self.__focal_point[1]
                z_origin = 0
                self.__focal_point[2] = z_origin
        else:
            x_origin, y_origin, z_origin = self.__focal_point[0], \
                                           self.__focal_point[1], \
                                           self.__focal_point[2]

        #   CAMERA AXES |  DISPLAYED GRID | XZ PLANE | XY PLANE | YZ PLANE
        #      x,y,z    |      x,y,z      |   x,z    |    x,y   |    y,z
        #  -------------+-----------------+----------+----------+----------
        #      -,-,-    |      +,+,+      |   +,+    |    +,+   |    +,+
        #      -,-,+    |      +,+,-      |   +,-    |    +,+   |    +,-
        #      -,+,-    |      +,-,+      |   +,+    |    +,-   |    -,+
        #      -,+,+    |      +,-,-      |   +,-    |    +,-   |    -,-
        #      +,-,-    |      -,+,+      |   -,+    |    -,+   |    +,+
        #      +,-,+    |      -,+,-      |   -,-    |    -,+   |    +,-
        #      +,+,-    |      -,-,+      |   -,+    |    -,-   |    -,+
        #      +,+,+    |      -,-,-      |   -,-    |    -,-   |    -,-
        # min = -num_squares or 0, around the default position
        # max = +num_squares or 0, around the default position
        # e.g. at the origin, for negative axes: -10 -> 0, positive axes: 0 -> 10
        min_x_coord = x_origin + int(-(self.__num_squares / 2) + (sign(camera_axes.x) * -1) * (self.__num_squares / 2))
        max_x_coord = x_origin + int((self.__num_squares / 2) + (sign(camera_axes.x) * -1) * (self.__num_squares / 2))

        min_y_coord = y_origin + int(-(self.__num_squares / 2) + (sign(camera_axes.y) * -1) * (self.__num_squares / 2))
        max_y_coord = y_origin + int((self.__num_squares / 2) + (sign(camera_axes.y) * -1) * (self.__num_squares / 2))

        min_z_coord = z_origin + int(-(self.__num_squares / 2) + (sign(camera_axes.z) * -1) * (self.__num_squares / 2))
        max_z_coord = z_origin + int((self.__num_squares / 2) + (sign(camera_axes.z) * -1) * (self.__num_squares / 2))

        # Compound origins are in the middle of the bounding boxes. Thus new pos will be between max and min.
        x_middle = (max_x_coord + min_x_coord) / 2
        y_middle = (max_y_coord + min_y_coord) / 2
        z_middle = (max_z_coord + min_z_coord) / 2

        # XY Plane
        if camera_axes.z < 0:
            self.grid_object[self.__planes_idx][self.__xy_plane_idx].pos = vector(x_middle, y_middle, min_z_coord)
        else:
            self.grid_object[self.__planes_idx][self.__xy_plane_idx].pos = vector(x_middle, y_middle, max_z_coord)

        # XZ Plane
        if camera_axes.y < 0:
            self.grid_object[self.__planes_idx][self.__xz_plane_idx].pos = vector(x_middle, min_y_coord, z_middle)
        else:
            self.grid_object[self.__planes_idx][self.__xz_plane_idx].pos = vector(x_middle, max_y_coord, z_middle)

        # YZ Plane
        if camera_axes.x < 0:
            self.grid_object[self.__planes_idx][self.__yz_plane_idx].pos = vector(min_x_coord, y_middle, z_middle)
        else:
            self.grid_object[self.__planes_idx][self.__yz_plane_idx].pos = vector(max_x_coord, y_middle, z_middle)

    def update_grid(self):
        """
        Update the grid axes and numbers if the camera position/rotation has changed.
        """
        # Obtain the new camera settings
        new_camera_pos = self.__scene.camera.pos
        new_camera_axes = self.__scene.camera.axis

        old_camera_pos = self.camera_pos
        old_camera_axes = self.camera_axes

        # If camera is different to previous: update
        if (not new_camera_axes.equals(old_camera_axes)) or (not new_camera_pos.equals(old_camera_pos)):
            # Update old positions
            self.camera_pos = new_camera_pos
            self.camera_axes = new_camera_axes

            # Update grid
            self.__move_grid_objects()
            update_grid_numbers(self.__focal_point,
                                self.grid_object[self.__labels_idx],
                                self.__num_squares,
                                self.__scene)

    def toggle_2d_3d(self):
        """
        Toggle the grid between 2D and 3D options.
        2D - XY Plane
        3D - XY, XZ, YZ Planes
        """
        # Set the new visibility
        self.__is_3d = not self.__is_3d

        # Toggle it for XZ, YZ planes
        self.grid_object[self.__planes_idx][self.__xz_plane_idx].visible = self.__is_3d
        self.grid_object[self.__planes_idx][self.__yz_plane_idx].visible = self.__is_3d

        # Toggle it for Z plane numbers
        # Index start = (num_squares + 1) (11 numbers shown for 10 squares) * 2 axes + 2 letters for axes
        z_label_start = (self.__num_squares + 1) * 2 + 2
        # Index end = end of labels array
        z_label_end = len(self.grid_object[self.__labels_idx])
        # Toggle
        for idx in range(z_label_start, z_label_end):
            self.grid_object[self.__labels_idx][idx].visible = self.__is_3d

        self.update_grid()

    def set_visibility(self, is_visible):
        """
        Set the visibility of the grid

        :param is_visible: Boolean of whether to display the grid
        :type is_visible: `bool`
        """
        # Modify all graphics
        for plane in self.grid_object[self.__planes_idx]:
            plane.visible = is_visible
        for number in self.grid_object[self.__labels_idx]:
            number.visible = is_visible
        # If 3D, changes are made
        # If 2D and setting off, changes are made
        # If 2D and setting on, toggle the 3D graphics (are turned on)
        if self.__is_3d is False and is_visible is True:
            self.toggle_2d_3d()

    def set_relative(self, is_relative):
        """
        Set whether the grid should be locked to (0, 0, 0) or relative to camera focus point

        :param is_relative: Whether the camera is dynamic (True) or static (False)
        :type is_relative: `bool`
        """
        self.__relative_cam = is_relative
        self.update_grid()
        
    # def clear_scene(self):
    #     """
    #     Clear the canvas of all objects (keeping the grid)
    #
    #     Due to how VPython operates, there is no 'deletion' of objects directly.
    #     To 'delete' objects, first they must be rendered invisible.
    #
    #     Then: if a new object with the same variable name is used, the previous memory will be freed.
    #     Or: del variable_name will free its memory.
    #     If the object wasn't invisible, it would remain visible in the scene.
    #
    #     Since the scene doesnt track variable names, the best way to clear the scene is to render all objects invisible,
    #     and have the user assume they are all deleted. However, all objects can be redisplayed by setting the visibility
    #     """
    #     # Save current grid visibility
    #     grid_visibility = self.grid_object[self.__planes_idx][self.__xy_plane_idx].visible
    #
    #     # Set all objects invisible
    #     for scene_object in self.__scene.objects:
    #         scene_object.visible = False
    #
    #     # Set grid visibility to previous
    #     self.set_visibility(grid_visibility)
    #
    #     # Wait for scene to update
    #     self.__scene.waitfor("draw_complete")


def create_line(pos1, pos2, scene, colour=None, thickness=0.01):
    """
    Create a line from position 1 to position 2.

    :param scene: The scene in which to draw the object
    :type scene: class:`vpython.canvas`
    :param pos1: 3D position of one end of the line.
    :type pos1: class:`vpython.vector`
    :param pos2: 3D position of the other end of the line.
    :type pos2: class:`vpython.vector`
    :param colour: RGB list to colour the line to
    :type colour: `list`
    :param thickness: Thickness of the line
    :type thickness: `float`
    :raises ValueError: RGB colour must be normalised between 0->1
    :raises ValueError: Thickness must be greater than 0
    :return: A box resembling a line
    :rtype: class:`vpython.box`
    """
    # Set default colour
    # Stops a warning about mutable parameter
    if colour is None:
        colour = [0, 0, 0]

    if colour[0] > 1.0 or colour[1] > 1.0 or colour[2] > 1.0 or \
       colour[0] < 0.0 or colour[1] < 0.0 or colour[2] < 0.0:
        raise ValueError("RGB values must be normalised between 0 and 1")

    if thickness < 0.0:
        raise ValueError("Thickness must be greater than 0")

    # Length of the line using the magnitude
    line_len = mag(pos2-pos1)

    # Position of the line is the midpoint (centre) between the ends
    position = (pos1 + pos2) / 2

    # Axis direction of the line (to align the box (line) to intersect the two points)
    axis_dir = pos2 - pos1

    # Return a box of thin width and height to resemble a line
    # thickness = 0.01
    return box(canvas=scene,
               pos=position,
               axis=axis_dir,
               length=line_len,
               width=thickness,
               height=thickness,
               color=vector(colour[0], colour[1], colour[2]))


def create_segmented_line(pos1, pos2, scene, segment_len, colour=None, thickness=0.01):
    """
    Create a dashed line from position 1 to position 2.

    :param scene: The scene in which to draw the object
    :type scene: class:`vpython.canvas`
    :param pos1: 3D position of one end of the line.
    :type pos1: class:`vpython.vector`
    :param pos2: 3D position of the other end of the line.
    :type pos2: class:`vpython.vector`
    :param colour: RGB list to colour the line to
    :type colour: `list`
    :param thickness: Thickness of the line
    :type thickness: `float`
    :param segment_len: The length of the segment, and gap between segments
    :type segment_len: `float`
    :raises ValueError: RGB colour must be normalised between 0->1
    :raises ValueError: Thickness must be greater than 0
    :return: A box resembling a line
    :rtype: class:`vpython.box`
    """
    # Set default colour
    # Stops a warning about mutable parameter
    if colour is None:
        colour = [0, 0, 0]

    if colour[0] > 1.0 or colour[1] > 1.0 or colour[2] > 1.0 or \
       colour[0] < 0.0 or colour[1] < 0.0 or colour[2] < 0.0:
        raise ValueError("RGB values must be normalised between 0 and 1")

    if thickness < 0.0:
        raise ValueError("Thickness must be greater than 0")

    # Length of the line using the magnitude
    line_len = mag(pos2-pos1)

    # Axis direction of the line (to align the box (line) to intersect the two points)
    axis_dir = pos2 - pos1
    axis_dir.mag = 1.0

    # Return a compound of boxes of thin width and height to resemble a dashed line
    dash_positions = []
    boxes = []
    pos1 = pos1 + (axis_dir * segment_len/2)  # Translate centre pos to centre of where dashes will originate from

    # Range = number of dashes (vis and invis)
    for idx in range(0,  int(ceil(line_len / (segment_len / axis_dir.mag)))):
        # Add every even point (zeroth, second...) to skip gaps between boxes
        if idx % 2 == 0:
            dash_positions.append(pos1)
        pos1 = (pos1 + axis_dir * segment_len)
        # If the axis between points changes, then the line has surpassed the end point. The line is done
        check_dir = pos2-pos1
        check_dir.mag = 1.0
        if not vectors_approx_equal(axis_dir, check_dir):
            break

    for xyz in dash_positions:
        length = segment_len
        # If the box will surpass the end point
        len_to_end = (pos2-xyz).mag
        if len_to_end < segment_len / 2:
            # Length is equal to dist to the end * 2 (as pos is middle of box)
            length = len_to_end * 2

        boxes.append(
            box(
                canvas=scene,
                pos=xyz,
                axis=axis_dir,
                length=length,
                width=thickness,
                height=thickness,
                color=vector(colour[0], colour[1], colour[2])
            )
        )

    return compound(boxes)


def create_marker(scene, x, y, shape, colour=None):
    """
    Draw the shape at the given position

    :param scene: The scene in which to draw the object
    :type scene: class:`vpython.canvas`
    :param x: The x location to draw the object at
    :type x: `float`
    :param y: The y location to draw the object at
    :type y: `float`
    :param shape: The shape of the object to draw
    :type shape: `str`
    :param colour: The colour of the object
    :type colour: `list`
    :returns: A 2D object that has been drawn
    :rtype: class:`graphics.graphics_object2d.Object2D`
    """
    # Set default colour
    # Stops a warning about mutable parameter
    if colour is None:
        colour = [0, 0, 0]

    # Create an SE2 for the object
    obj_se2 = SE2(x=x, y=y, theta=0)

    # Create the object and return it
    return Object2D(obj_se2, scene, shape, colour)


def vectors_approx_equal(v1, v2):
    """
    Check whether the vectors are approximately equal.
    This is used where there is VERY minor floating point differences that can occur in VPython.

    :param v1: Vector 1
    :type v1: class:`vpython.vector`
    :param v2: Vector 2
    :type v2: class:`vpython.vector`
    :returns: True if vectors are within tolerance
    :rtype: `bool`
    """
    return abs(v1.x - v2.x < 0.001) and abs(v1.y - v2.y < 0.001) and abs(v1.z - v2.z < 0.001)
