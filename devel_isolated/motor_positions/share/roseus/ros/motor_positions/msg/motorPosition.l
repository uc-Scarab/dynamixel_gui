;; Auto-generated. Do not edit!


(when (boundp 'motor_positions::motorPosition)
  (if (not (find-package "MOTOR_POSITIONS"))
    (make-package "MOTOR_POSITIONS"))
  (shadow 'motorPosition (find-package "MOTOR_POSITIONS")))
(unless (find-package "MOTOR_POSITIONS::MOTORPOSITION")
  (make-package "MOTOR_POSITIONS::MOTORPOSITION"))

(in-package "ROS")
;;//! \htmlinclude motorPosition.msg.html


(defclass motor_positions::motorPosition
  :super ros::object
  :slots (_motor_id _position ))

(defmethod motor_positions::motorPosition
  (:init
   (&key
    ((:motor_id __motor_id) 0)
    ((:position __position) 0)
    )
   (send-super :init)
   (setq _motor_id (round __motor_id))
   (setq _position (round __position))
   self)
  (:motor_id
   (&optional __motor_id)
   (if __motor_id (setq _motor_id __motor_id)) _motor_id)
  (:position
   (&optional __position)
   (if __position (setq _position __position)) _position)
  (:serialization-length
   ()
   (+
    ;; uint8 _motor_id
    1
    ;; uint16 _position
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _motor_id
       (write-byte _motor_id s)
     ;; uint16 _position
       (write-word _position s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _motor_id
     (setq _motor_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _position
     (setq _position (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get motor_positions::motorPosition :md5sum-) "791e891bae681c33af37a246f28f5485")
(setf (get motor_positions::motorPosition :datatype-) "motor_positions/motorPosition")
(setf (get motor_positions::motorPosition :definition-)
      "uint8  motor_id
uint16 position

")



(provide :motor_positions/motorPosition "791e891bae681c33af37a246f28f5485")


