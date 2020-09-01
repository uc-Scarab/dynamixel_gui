
(cl:in-package :asdf)

(defsystem "motor_positions-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "controlTable" :depends-on ("_package_controlTable"))
    (:file "_package_controlTable" :depends-on ("_package"))
    (:file "motorPosition" :depends-on ("_package_motorPosition"))
    (:file "_package_motorPosition" :depends-on ("_package"))
    (:file "positionArray" :depends-on ("_package_positionArray"))
    (:file "_package_positionArray" :depends-on ("_package"))
    (:file "trajectory" :depends-on ("_package_trajectory"))
    (:file "_package_trajectory" :depends-on ("_package"))
    (:file "viaPoints" :depends-on ("_package_viaPoints"))
    (:file "_package_viaPoints" :depends-on ("_package"))
  ))