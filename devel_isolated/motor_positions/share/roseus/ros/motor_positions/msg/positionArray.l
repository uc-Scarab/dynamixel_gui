;; Auto-generated. Do not edit!


(when (boundp 'motor_positions::positionArray)
  (if (not (find-package "MOTOR_POSITIONS"))
    (make-package "MOTOR_POSITIONS"))
  (shadow 'positionArray (find-package "MOTOR_POSITIONS")))
(unless (find-package "MOTOR_POSITIONS::POSITIONARRAY")
  (make-package "MOTOR_POSITIONS::POSITIONARRAY"))

(in-package "ROS")
;;//! \htmlinclude positionArray.msg.html


(defclass motor_positions::positionArray
  :super ros::object
  :slots (_positions ))

(defmethod motor_positions::positionArray
  (:init
   (&key
    ((:positions __positions) (let (r) (dotimes (i 0) (push (instance motor_positions::motorPosition :init) r)) r))
    )
   (send-super :init)
   (setq _positions __positions)
   self)
  (:positions
   (&rest __positions)
   (if (keywordp (car __positions))
       (send* _positions __positions)
     (progn
       (if __positions (setq _positions (car __positions)))
       _positions)))
  (:serialization-length
   ()
   (+
    ;; motor_positions/motorPosition[] _positions
    (apply #'+ (send-all _positions :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; motor_positions/motorPosition[] _positions
     (write-long (length _positions) s)
     (dolist (elem _positions)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; motor_positions/motorPosition[] _positions
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _positions (let (r) (dotimes (i n) (push (instance motor_positions::motorPosition :init) r)) r))
     (dolist (elem- _positions)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get motor_positions::positionArray :md5sum-) "7805484bdfb5d5d980ba4c097f4f9dcf")
(setf (get motor_positions::positionArray :datatype-) "motor_positions/positionArray")
(setf (get motor_positions::positionArray :definition-)
      "motorPosition[] positions

================================================================================
MSG: motor_positions/motorPosition
uint8  motor_id
uint16 position

")



(provide :motor_positions/positionArray "7805484bdfb5d5d980ba4c097f4f9dcf")


