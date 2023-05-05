import ultralytics
from ultralytics import YOLO
from ultralyticsplus import render_result
import cv2
import serial
import asyncio


HEIGHT = 640
middle_screen = 320
# print("here2")

model = YOLO("models/last.pt")
arduino = serial.Serial('COM5', 9600)

video = "http://192.168.1.23:8080/video" #phone url


# print("here1")
def box_preference(boxes):
    # print(boxes)
    if boxes== None  or len(boxes) == 0:
        return None
    # print("here")
    pref = boxes[0]
    for box in boxes:
        if box[4]>0.4 and box[3] > pref[3]:
            pref = box

    return pref



def sendUDP(result, arduino):
    assert isinstance(result[0], ultralytics.yolo.engine.results.Results)
    # print(type(result[0]))
    boxes = result[0].boxes.boxes
    # print(boxes)
    box = box_preference(boxes)
    # print(box)
    if box!=None:
        # print(box)
        mid = (box[0] + box[2] )/ 2 
        print(mid)
        if mid < middle_screen:
            # arduino.write(b'L')
            # left()
            print("left")
        elif mid > middle_screen:
            # arduino.write(b'R')
            # right()
            print("right")

        elif box[3] < HEIGHT:
            # arduino.write(b'F')
            # forward()
            print("forward")
        
        else:
            # arduino.write(b'F')
            # fill()
            print("fill")
        


# async def solution(frame,arduino):
#     result = model.predict(frame)
#     print(result)
#     # sendUDP(result, arduino)
    


cap = cv2.VideoCapture(video)
print("here")

while True:
    _, frame = cap.read()
    image = frame.copy()
    cv2.imshow("original", frame)
    asyncio.run(solution(frame, arduino))
    # result = model.predict(frame)
    # sendUDP(result=result, arduino= arduino)
    # render = render_result(model=model, image = image, result=result[0])
    cv2.imshow("segmented", image)
    if cv2.waitKey(1) == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()