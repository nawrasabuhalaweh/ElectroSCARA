import time
import cv2
import serial
import scara_config as sc
import scara_serial as ss
import scara_kinematics as sk
import scara_vision as sv


scara = serial.Serial('COM3', baudrate=250000, timeout=1)
print("Connected to SCARA")
time.sleep(2)

magnet = serial.Serial('COM4', baudrate=9600, timeout=1)
print("Connected to electromagnet")
time.sleep(1)

ss.writeManual(scara, "G91\n")

firstXSteps = sk.getAbsStepsX(200, 300, sc.l1, sc.l2)
firstYSteps = sk.getAbsStepsY(200, 300, sc.l1, sc.l2)

print(firstXSteps)
print(firstYSteps)

ss.writeScara(scara, firstXSteps, firstYSteps, 3000)

cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)

for i in range(30):
    cap.grab()


loopin = True

while loopin:
    for i in range(0, 5):
        cap.grab()

    feed = ss.getFeed(magnet)

    if feed != "":
        feed = int(feed)
    else:
        feed = 2000

    timeFactor = 2500/feed

    [objPosX, objPosY] = sv.readFrame(cap)
    print(f"Object position: [{objPosX:.2f}, {objPosY:.2f}]")

    [nextStepsX, nextStepsY] = sk.getRelSteps(objPosX, objPosY, firstXSteps, firstYSteps, sc.l1, sc.l2)
    print(f"Steps to object: [{nextStepsX:.2f}, {nextStepsY:.2f}]")

    time.sleep(0.5 * timeFactor)

    ss.writeScara(scara, nextStepsX, nextStepsY, 2500)
    time.sleep(1.5 * timeFactor)

    ss.writeMagnet(magnet, True)
    time.sleep(0.3)

    ss.writeScara(scara, -nextStepsX, -nextStepsY, 2500)
    time.sleep(1.5 * timeFactor)
    ss.writeMagnet(magnet, False)

    if (cv2.waitKey(25) & 0xFF) == ord('q'):
        cv2.destroyAllWindows()
        ss.closeDevice(scara)
        ss.closeDevice(magnet)

    cv2.waitKey(1)
