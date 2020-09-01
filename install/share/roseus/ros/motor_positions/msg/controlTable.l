;; Auto-generated. Do not edit!


(when (boundp 'motor_positions::controlTable)
  (if (not (find-package "MOTOR_POSITIONS"))
    (make-package "MOTOR_POSITIONS"))
  (shadow 'controlTable (find-package "MOTOR_POSITIONS")))
(unless (find-package "MOTOR_POSITIONS::CONTROLTABLE")
  (make-package "MOTOR_POSITIONS::CONTROLTABLE"))

(in-package "ROS")
;;//! \htmlinclude controlTable.msg.html


(defclass motor_positions::controlTable
  :super ros::object
  :slots (_dest _command_id _value ))

(defmethod motor_positions::controlTable
  (:init
   (&key
    ((:dest __dest) 0)
    ((:command_id __command_id) 0)
    ((:value __value) 0)
    )
   (send-super :init)
   (setq _dest (round __dest))
   (setq _command_id (round __command_id))
   (setq _value (round __value))
   self)
  (:dest
   (&optional __dest)
   (if __dest (setq _dest __dest)) _dest)
  (:command_id
   (&optional __command_id)
   (if __command_id (setq _command_id __command_id)) _command_id)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; uint8 _dest
    1
    ;; uint8 _command_id
    1
    ;; uint16 _value
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _dest
       (write-byte _dest s)
     ;; uint8 _command_id
       (write-byte _command_id s)
     ;; uint16 _value
       (write-word _value s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _dest
     (setq _dest (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _command_id
     (setq _command_id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _value
     (setq _value (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get motor_positions::controlTable :md5sum-) "31f7917cc26f8f92831d701d115a4e37")
(setf (get motor_positions::controlTable :datatype-) "motor_positions/controlTable")
(setf (get motor_positions::controlTable :definition-)
      "uint8 dest       
uint8 command_id
uint16 value

")



(provide :motor_positions/controlTable "31f7917cc26f8f92831d701d115a4e37")


