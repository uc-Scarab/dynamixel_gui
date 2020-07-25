classdef CustomMsgConsts
    %CustomMsgConsts This class stores all message types
    %   The message types are constant properties, which in turn resolve
    %   to the strings of the actual types.
    
    %   Copyright 2014-2020 The MathWorks, Inc.
    
    properties (Constant)
        motor_positions_controlTable = 'motor_positions/controlTable'
        motor_positions_motorPosition = 'motor_positions/motorPosition'
        motor_positions_positionArray = 'motor_positions/positionArray'
        motor_positions_trajectory = 'motor_positions/trajectory'
        motor_positions_viaPoints = 'motor_positions/viaPoints'
    end
    
    methods (Static, Hidden)
        function messageList = getMessageList
            %getMessageList Generate a cell array with all message types.
            %   The list will be sorted alphabetically.
            
            persistent msgList
            if isempty(msgList)
                msgList = cell(5, 1);
                msgList{1} = 'motor_positions/controlTable';
                msgList{2} = 'motor_positions/motorPosition';
                msgList{3} = 'motor_positions/positionArray';
                msgList{4} = 'motor_positions/trajectory';
                msgList{5} = 'motor_positions/viaPoints';
            end
            
            messageList = msgList;
        end
        
        function serviceList = getServiceList
            %getServiceList Generate a cell array with all service types.
            %   The list will be sorted alphabetically.
            
            persistent svcList
            if isempty(svcList)
                svcList = cell(0, 1);
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            serviceList = svcList;
        end
        
        function actionList = getActionList
            %getActionList Generate a cell array with all action types.
            %   The list will be sorted alphabetically.
            
            persistent actList
            if isempty(actList)
                actList = cell(0, 1);
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            actionList = actList;
        end
    end
end
