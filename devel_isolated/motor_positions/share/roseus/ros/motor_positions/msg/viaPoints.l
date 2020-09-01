;; Auto-generated. Do not edit!


(when (boundp 'motor_positions::viaPoints)
  (if (not (find-package "MOTOR_POSITIONS"))
    (make-package "MOTOR_POSITIONS"))
  (shadow 'viaPoints (find-package "MOTOR_POSITIONS")))
(unless (find-package "MOTOR_POSITIONS::VIAPOINTS")
  (make-package "MOTOR_POSITIONS::VIAPOINTS"))

(in-package "ROS")
;;//! \htmlinclude viaPoints.msg.html


(defclass motor_positions::viaPoints
  :super ros::object
  :slots (_motor_1 _motor_2 _motor_3 _motor_4 ))

(defmethod motor_positions::viaPoints
  (:init
   (&key
    ((:motor_1 __motor_1) 0)
    ((:motor_2 __motor_2) 0)
    ((:motor_3 __motor_3) 0)
    ((:motor_4 __motor_4) 0)
    )
   (send-super :init)
   (setq _motor_1 (round __motor_1))
   (setq _motor_2 (round __motor_2))
   (setq _motor_3 (round __motor_3))
   (setq _motor_4 (round __motor_4))
   self)
  (:motor_1
   (&optional __motor_1)
   (if __motor_1 (setq _motor_1 __motor_1)) _motor_1)
  (:motor_2
   (&optional __motor_2)
   (if __motor_2 (setq _motor_2 __motor_2)) _motor_2)
  (:motor_3
   (&optional __motor_3)
   (if __motor_3 (setq _motor_3 __motor_3)) _motor_3)
  (:motor_4
   (&optional __motor_4)
   (if __motor_4 (setq _motor_4 __motor_4)) _motor_4)
  (:serialization-length
   ()
   (+
    ;; uint16 _motor_1
    2
    ;; uint16 _motor_2
    2
    ;; uint16 _motor_3
    2
    ;; uint16 _motor_4
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _motor_1
       (write-word _motor_1 s)
     ;; uint16 _motor_2
       (write-word _motor_2 s)
     ;; uint16 _motor_3
       (write-word _motor_3 s)
     ;; uint16 _motor_4
       (write-word _motor_4 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _motor_1
     (setq _motor_1 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _motor_2
     (setq _motor_2 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _motor_3
     (setq _motor_3 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _motor_4
     (setq _motor_4 (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get motor_positions::viaPoints :md5sum-) "62ceb7511df5429669d5680ad1b7fffb")
(setf (get motor_positions::viaPoints :datatype-) "motor_positions/viaPoints")
(setf (get motor_positions::viaPoints :definition-)
      "uint16 motor_1
uint16 motor_2
uint16 motor_3
uint16 motor_4

")



(provide :motor_positions/viaPoints "62ceb7511df5429669d5680ad1b7fffb")


