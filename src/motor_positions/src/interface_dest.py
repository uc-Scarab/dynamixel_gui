from enum import Enum, unique, auto
import pdb


class AutoName(Enum):
    def _generate_next_value_(name, start, count, last_values):
        return count


class Dest(AutoName):
    SYSTEM = auto()  # RESERVED
    META = auto()  # RESERVED
    CONFIG_OPT = auto()  # RESERVED
    SENSOR_IMU = auto()
    # Legs RESERVED
    LEG_1 = auto()
    LEG_2 = auto()
    LEG_3 = auto()
    LEG_4 = auto()
    LEG_5 = auto()
    LEG_6 = auto()
    # Leg 1
    JOINT_L1Q1 = auto()
    JOINT_L1Q2 = auto()
    JOINT_L1Q3 = auto()
    JOINT_L1Q4 = auto()
    # Leg 2
    JOINT_L2Q1 = auto()
    JOINT_L2Q2 = auto()
    JOINT_L2Q3 = auto()
    JOINT_L2Q4 = auto()
    # Leg 3
    JOINT_L3Q1 = auto()
    JOINT_L3Q2 = auto()
    JOINT_L3Q3 = auto()
    JOINT_L3Q4 = auto()
    # Leg 4
    JOINT_L4Q1 = auto()
    JOINT_L4Q2 = auto()
    JOINT_L4Q3 = auto()
    JOINT_L4Q4 = auto()
    # Leg 5
    JOINT_L5Q1 = auto()
    JOINT_L5Q2 = auto()
    JOINT_L5Q3 = auto()
    JOINT_L5Q4 = auto()
    # Leg 6
    JOINT_L6Q1 = auto()
    JOINT_L6Q2 = auto()
    JOINT_L6Q3 = auto()
    JOINT_L6Q4 = auto()


if __name__ == "__main__":
