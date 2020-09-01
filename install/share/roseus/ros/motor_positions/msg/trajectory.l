;; Auto-generated. Do not edit!


(when (boundp 'motor_positions::trajectory)
  (if (not (find-package "MOTOR_POSITIONS"))
    (make-package "MOTOR_POSITIONS"))
  (shadow 'trajectory (find-package "MOTOR_POSITIONS")))
(unless (find-package "MOTOR_POSITIONS::TRAJECTORY")
  (make-package "MOTOR_POSITIONS::TRAJECTORY"))

(in-package "ROS")
;;//! \htmlinclude trajectory.msg.html


(defclass motor_positions::trajectory
  :super ros::object
  :slots (_q ))

(defmethod motor_positions::trajectory
  (:init
   (&key
    ((:q __q) (let (r) (dotimes (i 0) (push (instance motor_positions::viaPoints :init) r)) r))
    )
   (send-super :init)
   (setq _q __q)
   self)
  (:q
   (&rest __q)
   (if (keywordp (car __q))
       (send* _q __q)
     (progn
       (if __q (setq _q (car __q)))
       _q)))
  (:serialization-length
   ()
   (+
    ;; motor_positions/viaPoints[] _q
    (apply #'+ (send-all _q :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; motor_positions/viaPoints[] _q
     (write-long (length _q) s)
     (dolist (elem _q)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; motor_positions/viaPoints[] _q
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _q (let (r) (dotimes (i n) (push (instance motor_positions::viaPoints :init) r)) r))
     (dolist (elem- _q)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get motor_positions::trajectory :md5sum-) "e22957dcc8eb24a0e55afb89801e2607")
(setf (get motor_positions::trajectory :datatype-) "motor_positions/trajectory")
(setf (get motor_positions::trajectory :definition-)
      "viaPoints[] q

================================================================================
MSG: motor_positions/viaPoints
uint16 motor_1
uint16 motor_2
uint16 motor_3
uint16 motor_4

")



(provide :motor_positions/trajectory "e22957dcc8eb24a0e55afb89801e2607")


