classdef viaPoints < robotics.ros.Message
    %viaPoints MATLAB implementation of motor_positions/viaPoints
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2020 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'motor_positions/viaPoints' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '62ceb7511df5429669d5680ad1b7fffb' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Dependent)
        Motor1
        Motor2
        Motor3
        Motor4
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Motor1', 'Motor2', 'Motor3', 'Motor4'} % List of non-constant message properties
        ROSPropertyList = {'motor_1', 'motor_2', 'motor_3', 'motor_4'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = viaPoints(msg)
            %viaPoints Construct the message object viaPoints
            import com.mathworks.toolbox.robotics.ros.message.MessageInfo;
            
            % Support default constructor
            if nargin == 0
                obj.JavaMessage = obj.createNewJavaMessage;
                return;
            end
            
            % Construct appropriate empty array
            if isempty(msg)
                obj = obj.empty(0,1);
                return;
            end
            
            % Make scalar construction fast
            if isscalar(msg)
                % Check for correct input class
                if ~MessageInfo.compareTypes(msg(1), obj.MessageType)
                    error(message('robotics:ros:message:NoTypeMatch', obj.MessageType, ...
                        char(MessageInfo.getType(msg(1))) ));
                end
                obj.JavaMessage = msg(1);
                return;
            end
            
            % Check that this is a vector of scalar messages. Since this
            % is an object array, use arrayfun to verify.
            if ~all(arrayfun(@isscalar, msg))
                error(message('robotics:ros:message:MessageArraySizeError'));
            end
            
            % Check that all messages in the array have the correct type
            if ~all(arrayfun(@(x) MessageInfo.compareTypes(x, obj.MessageType), msg))
                error(message('robotics:ros:message:NoTypeMatchArray', obj.MessageType));
            end
            
            % Construct array of objects if necessary
            objType = class(obj);
            for i = 1:length(msg)
                obj(i,1) = feval(objType, msg(i)); %#ok<AGROW>
            end
        end
        
        function motor1 = get.Motor1(obj)
            %get.Motor1 Get the value for property Motor1
            motor1 = typecast(int16(obj.JavaMessage.getMotor1), 'uint16');
        end
        
        function set.Motor1(obj, motor1)
            %set.Motor1 Set the value for property Motor1
            validateattributes(motor1, {'numeric'}, {'nonempty', 'scalar'}, 'viaPoints', 'Motor1');
            
            obj.JavaMessage.setMotor1(motor1);
        end
        
        function motor2 = get.Motor2(obj)
            %get.Motor2 Get the value for property Motor2
            motor2 = typecast(int16(obj.JavaMessage.getMotor2), 'uint16');
        end
        
        function set.Motor2(obj, motor2)
            %set.Motor2 Set the value for property Motor2
            validateattributes(motor2, {'numeric'}, {'nonempty', 'scalar'}, 'viaPoints', 'Motor2');
            
            obj.JavaMessage.setMotor2(motor2);
        end
        
        function motor3 = get.Motor3(obj)
            %get.Motor3 Get the value for property Motor3
            motor3 = typecast(int16(obj.JavaMessage.getMotor3), 'uint16');
        end
        
        function set.Motor3(obj, motor3)
            %set.Motor3 Set the value for property Motor3
            validateattributes(motor3, {'numeric'}, {'nonempty', 'scalar'}, 'viaPoints', 'Motor3');
            
            obj.JavaMessage.setMotor3(motor3);
        end
        
        function motor4 = get.Motor4(obj)
            %get.Motor4 Get the value for property Motor4
            motor4 = typecast(int16(obj.JavaMessage.getMotor4), 'uint16');
        end
        
        function set.Motor4(obj, motor4)
            %set.Motor4 Set the value for property Motor4
            validateattributes(motor4, {'numeric'}, {'nonempty', 'scalar'}, 'viaPoints', 'Motor4');
            
            obj.JavaMessage.setMotor4(motor4);
        end
    end
    
    methods (Access = protected)
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.Motor1 = obj.Motor1;
            cpObj.Motor2 = obj.Motor2;
            cpObj.Motor3 = obj.Motor3;
            cpObj.Motor4 = obj.Motor4;
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Motor1 = strObj.Motor1;
            obj.Motor2 = strObj.Motor2;
            obj.Motor3 = strObj.Motor3;
            obj.Motor4 = strObj.Motor4;
        end
    end
    
    methods (Access = ?robotics.ros.Message)
        function strObj = saveobj(obj)
            %saveobj Implements saving of message to MAT file
            
            % Return an empty element if object array is empty
            if isempty(obj)
                strObj = struct.empty;
                return
            end
            
            strObj.Motor1 = obj.Motor1;
            strObj.Motor2 = obj.Motor2;
            strObj.Motor3 = obj.Motor3;
            strObj.Motor4 = obj.Motor4;
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.motor_positions.viaPoints.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.motor_positions.viaPoints;
            obj.reload(strObj);
        end
    end
end
