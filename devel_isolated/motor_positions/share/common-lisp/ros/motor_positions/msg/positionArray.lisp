; Auto-generated. Do not edit!


(cl:in-package motor_positions-msg)


;//! \htmlinclude positionArray.msg.html

(cl:defclass <positionArray> (roslisp-msg-protocol:ros-message)
  ((positions
    :reader positions
    :initarg :positions
    :type (cl:vector motor_positions-msg:motorPosition)
   :initform (cl:make-array 0 :element-type 'motor_positions-msg:motorPosition :initial-element (cl:make-instance 'motor_positions-msg:motorPosition))))
)

(cl:defclass positionArray (<positionArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <positionArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'positionArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motor_positions-msg:<positionArray> is deprecated: use motor_positions-msg:positionArray instead.")))

(cl:ensure-generic-function 'positions-val :lambda-list '(m))
(cl:defmethod positions-val ((m <positionArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_positions-msg:positions-val is deprecated.  Use motor_positions-msg:positions instead.")
  (positions m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <positionArray>) ostream)
  "Serializes a message object of type '<positionArray>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'positions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'positions))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <positionArray>) istream)
  "Deserializes a message object of type '<positionArray>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'positions) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'positions)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'motor_positions-msg:motorPosition))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<positionArray>)))
  "Returns string type for a message object of type '<positionArray>"
  "motor_positions/positionArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'positionArray)))
  "Returns string type for a message object of type 'positionArray"
  "motor_positions/positionArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<positionArray>)))
  "Returns md5sum for a message object of type '<positionArray>"
  "7805484bdfb5d5d980ba4c097f4f9dcf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'positionArray)))
  "Returns md5sum for a message object of type 'positionArray"
  "7805484bdfb5d5d980ba4c097f4f9dcf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<positionArray>)))
  "Returns full string definition for message of type '<positionArray>"
  (cl:format cl:nil "motorPosition[] positions~%~%================================================================================~%MSG: motor_positions/motorPosition~%uint8  motor_id~%uint16 position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'positionArray)))
  "Returns full string definition for message of type 'positionArray"
  (cl:format cl:nil "motorPosition[] positions~%~%================================================================================~%MSG: motor_positions/motorPosition~%uint8  motor_id~%uint16 position~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <positionArray>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'positions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <positionArray>))
  "Converts a ROS message object to a list"
  (cl:list 'positionArray
    (cl:cons ':positions (positions msg))
))
