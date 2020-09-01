; Auto-generated. Do not edit!


(cl:in-package motor_positions-msg)


;//! \htmlinclude viaPoints.msg.html

(cl:defclass <viaPoints> (roslisp-msg-protocol:ros-message)
  ((motor_1
    :reader motor_1
    :initarg :motor_1
    :type cl:fixnum
    :initform 0)
   (motor_2
    :reader motor_2
    :initarg :motor_2
    :type cl:fixnum
    :initform 0)
   (motor_3
    :reader motor_3
    :initarg :motor_3
    :type cl:fixnum
    :initform 0)
   (motor_4
    :reader motor_4
    :initarg :motor_4
    :type cl:fixnum
    :initform 0))
)

(cl:defclass viaPoints (<viaPoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <viaPoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'viaPoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motor_positions-msg:<viaPoints> is deprecated: use motor_positions-msg:viaPoints instead.")))

(cl:ensure-generic-function 'motor_1-val :lambda-list '(m))
(cl:defmethod motor_1-val ((m <viaPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:motor_1-val is deprecated.  Use motor_positions-msg:motor_1 instead.")
  (motor_1 m))

(cl:ensure-generic-function 'motor_2-val :lambda-list '(m))
(cl:defmethod motor_2-val ((m <viaPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:motor_2-val is deprecated.  Use motor_positions-msg:motor_2 instead.")
  (motor_2 m))

(cl:ensure-generic-function 'motor_3-val :lambda-list '(m))
(cl:defmethod motor_3-val ((m <viaPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:motor_3-val is deprecated.  Use motor_positions-msg:motor_3 instead.")
  (motor_3 m))

(cl:ensure-generic-function 'motor_4-val :lambda-list '(m))
(cl:defmethod motor_4-val ((m <viaPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:motor_4-val is deprecated.  Use motor_positions-msg:motor_4 instead.")
  (motor_4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <viaPoints>) ostream)
  "Serializes a message object of type '<viaPoints>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_1)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_2)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_3)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_4)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_4)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <viaPoints>) istream)
  "Deserializes a message object of type '<viaPoints>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_1)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_2)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_3)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'motor_4)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'motor_4)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<viaPoints>)))
  "Returns string type for a message object of type '<viaPoints>"
  "motor_positions/viaPoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'viaPoints)))
  "Returns string type for a message object of type 'viaPoints"
  "motor_positions/viaPoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<viaPoints>)))
  "Returns md5sum for a message object of type '<viaPoints>"
  "62ceb7511df5429669d5680ad1b7fffb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'viaPoints)))
  "Returns md5sum for a message object of type 'viaPoints"
  "62ceb7511df5429669d5680ad1b7fffb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<viaPoints>)))
  "Returns full string definition for message of type '<viaPoints>"
  (cl:format cl:nil "uint16 motor_1~%uint16 motor_2~%uint16 motor_3~%uint16 motor_4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'viaPoints)))
  "Returns full string definition for message of type 'viaPoints"
  (cl:format cl:nil "uint16 motor_1~%uint16 motor_2~%uint16 motor_3~%uint16 motor_4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <viaPoints>))
  (cl:+ 0
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <viaPoints>))
  "Converts a ROS message object to a list"
  (cl:list 'viaPoints
    (cl:cons ':motor_1 (motor_1 msg))
    (cl:cons ':motor_2 (motor_2 msg))
    (cl:cons ':motor_3 (motor_3 msg))
    (cl:cons ':motor_4 (motor_4 msg))
))
