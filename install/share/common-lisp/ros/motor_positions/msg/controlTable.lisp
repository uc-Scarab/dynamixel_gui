; Auto-generated. Do not edit!


(cl:in-package motor_positions-msg)


;//! \htmlinclude controlTable.msg.html

(cl:defclass <controlTable> (roslisp-msg-protocol:ros-message)
  ((dest
    :reader dest
    :initarg :dest
    :type cl:fixnum
    :initform 0)
   (command_id
    :reader command_id
    :initarg :command_id
    :type cl:fixnum
    :initform 0)
   (value
    :reader value
    :initarg :value
    :type cl:fixnum
    :initform 0))
)

(cl:defclass controlTable (<controlTable>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <controlTable>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'controlTable)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motor_positions-msg:<controlTable> is deprecated: use motor_positions-msg:controlTable instead.")))

(cl:ensure-generic-function 'dest-val :lambda-list '(m))
(cl:defmethod dest-val ((m <controlTable>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:dest-val is deprecated.  Use motor_positions-msg:dest instead.")
  (dest m))

(cl:ensure-generic-function 'command_id-val :lambda-list '(m))
(cl:defmethod command_id-val ((m <controlTable>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:command_id-val is deprecated.  Use motor_positions-msg:command_id instead.")
  (command_id m))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <controlTable>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:value-val is deprecated.  Use motor_positions-msg:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <controlTable>) ostream)
  "Serializes a message object of type '<controlTable>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dest)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'command_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'value)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'value)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <controlTable>) istream)
  "Deserializes a message object of type '<controlTable>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dest)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'command_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'value)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'value)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<controlTable>)))
  "Returns string type for a message object of type '<controlTable>"
  "motor_positions/controlTable")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'controlTable)))
  "Returns string type for a message object of type 'controlTable"
  "motor_positions/controlTable")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<controlTable>)))
  "Returns md5sum for a message object of type '<controlTable>"
  "31f7917cc26f8f92831d701d115a4e37")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'controlTable)))
  "Returns md5sum for a message object of type 'controlTable"
  "31f7917cc26f8f92831d701d115a4e37")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<controlTable>)))
  "Returns full string definition for message of type '<controlTable>"
  (cl:format cl:nil "uint8 dest       ~%uint8 command_id~%uint16 value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'controlTable)))
  "Returns full string definition for message of type 'controlTable"
  (cl:format cl:nil "uint8 dest       ~%uint8 command_id~%uint16 value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <controlTable>))
  (cl:+ 0
     1
     1
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <controlTable>))
  "Converts a ROS message object to a list"
  (cl:list 'controlTable
    (cl:cons ':dest (dest msg))
    (cl:cons ':command_id (command_id msg))
    (cl:cons ':value (value msg))
))
