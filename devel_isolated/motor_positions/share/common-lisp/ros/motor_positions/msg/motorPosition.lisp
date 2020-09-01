; Auto-generated. Do not edit!


(cl:in-package motor_positions-msg)


;//! \htmlinclude motorPosition.msg.html

(cl:defclass <motorPosition> (roslisp-msg-protocol:ros-message)
  ((motor_id
    :reader motor_id
    :initarg :motor_id
    :type cl:fixnum
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type cl:fixnum
    :initform 0))
)

(cl:defclass motorPosition (<motorPosition>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motorPosition>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motorPosition)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motor_positions-msg:<motorPosition> is deprecated: use motor_positions-msg:motorPosition instead.")))

(cl:ensure-generic-function 'motor_id-val :lambda-list '(m))
(cl:defmethod motor_id-val ((m <motorPosition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:motor_id-val is deprecated.  Use motor_positions-msg:motor_id instead.")
  (motor_id m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <motorPosition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:position-val is deprecated.  Use motor_positions-msg:position instead.")
  (position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motorPosition>) ostream)
  "Serializes a message object of type '<motorPosition>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'position)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motorPosition>) istream)
  "Deserializes a message object of type '<motorPosition>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'position)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motorPosition>)))
  "Returns string type for a message object of type '<motorPosition>"
  "motor_positions/motorPosition")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motorPosition)))
  "Returns string type for a message object of type 'motorPosition"
  "motor_positions/motorPosition")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motorPosition>)))
  "Returns md5sum for a message object of type '<motorPosition>"
  "791e891bae681c33af37a246f28f5485")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motorPosition)))
  "Returns md5sum for a message object of type 'motorPosition"
  "791e891bae681c33af37a246f28f5485")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motorPosition>)))
  "Returns full string definition for message of type '<motorPosition>"
  (cl:format cl:nil "uint8  motor_id~%uint16 position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motorPosition)))
  "Returns full string definition for message of type 'motorPosition"
  (cl:format cl:nil "uint8  motor_id~%uint16 position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motorPosition>))
  (cl:+ 0
     1
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motorPosition>))
  "Converts a ROS message object to a list"
  (cl:list 'motorPosition
    (cl:cons ':motor_id (motor_id msg))
    (cl:cons ':position (position msg))
))
